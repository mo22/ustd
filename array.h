// array.h - The internal array class
//
// This is the declaration of the internal array
// class used for resource-management
// supports []-indexing, adding elements at the end and
// erasing an elements by index.

#pragma once

#include <cassert>
#include <climits>
#include <stdexcept>

namespace mw {

#define ARRAY_INC_SIZE 16
#define ARRAY_MAX_SIZE UINT_MAX  // 65535 or 4294967295 (mostly)
#define ARRAY_INIT_SIZE 16

template <typename T> class array {
  private:
    T *arr;
    unsigned int maxSize;
    unsigned int startSize;
    unsigned int allocSize;
    unsigned int size;
    unsigned int incSize = ARRAY_INC_SIZE;
    bool shrink = true;

  public:
    array(unsigned int startSize = ARRAY_INIT_SIZE,
          unsigned int maxSize = ARRAY_MAX_SIZE,
          unsigned int incSize = ARRAY_INC_SIZE, bool shrink = true)
        : startSize(startSize), maxSize(maxSize), incSize(incSize),
          shrink(shrink) {
        size = 0;
        if (maxSize < startSize)
            maxSize = startSize;
        allocSize = startSize;
        arr = new T[allocSize];
    }

    ~array() {
        if (arr != nullptr) {
            delete[] arr;
        }
    }

    bool resize(unsigned int newSize) {
        unsigned int mv = newSize;
        if (newSize > maxSize)
            return false;
        if (!shrink) {
            if (newSize <= allocSize)
                return true;
        } else {
            if (newSize < allocSize)
                mv = newSize;
        }
        T *arrn = new T[newSize];
        if (arrn == nullptr)
            return false;
        for (unsigned int i = 0; i < mv; i++) {
            arrn[i] = arr[i];
        }
        delete (arr);
        arr = arrn;
        allocSize = newSize;
        return true;
    }

    bool add(T &ent) {
        if (size >= allocSize) {
            if (incSize == 0)
                return false;
            if (!resize(allocSize + incSize))
                return false;
        }
        arr[size] = ent;
        ++size;
        return true;
    }

    bool erase(unsigned int index) {
        if (index >= size) {
            return false;
        }
        for (int i = index; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }
        --size;
        if (shrink) {
            if ((size < allocSize - incSize) && (allocSize > incSize)) {
                printf("Shink to %d\n", allocSize - incSize);
                resize(allocSize - incSize);
            }
        }
        return true;
    }

    T operator[](unsigned int i) const {
        if (i >= allocSize) {
            if (incSize == 0) {
                assert(i < allocSize);
            }
            if (!resize(allocSize + incSize)) {
                assert(i < allocSize);
            }
        }
        if (i >= size && i <= allocSize)
            size = i + 1;
        if (i >= allocSize)
            i = allocSize - 1;
        return arr[i];
    }

    T &operator[](unsigned int i) {
        if (i >= allocSize) {
            if (incSize == 0) {
                assert(i < allocSize);
            }
            if (!resize(allocSize + incSize)) {
                assert(i < allocSize);
            }
        }
        if (i >= size && i <= allocSize)
            size = i + 1;
        if (i >= allocSize)
            i = allocSize - 1;
        return arr[i];
    }

    bool isEmpty() const {
        if (size == 0)
            return true;
        else
            return false;
    }

    unsigned int length() const {
        return (size);
    }
    unsigned int alloclen() const {
        return (allocSize);
    }
};
}
