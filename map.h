// map.h - ustd queue class

#pragma once
#include "array.h"
#include <iostream>
using std::cout;
using std::endl;

namespace ustd {

#define MAX_MAP_SIZE UINT_MAX

template <class K, class V> class map {
  private:
    unsigned int size;
    unsigned int peakSize;
    unsigned int allocSize;
    unsigned int startSize;
    unsigned int maxSize;
    unsigned int incSize;
    bool shrink;
    V bad;

  public:
    array<K> keys;
    array<V> values;

  public:
    map(unsigned int startSize = ARRAY_INIT_SIZE,
        unsigned int maxSize = ARRAY_MAX_SIZE,
        unsigned int incSize = ARRAY_INC_SIZE, bool shrink = true)
        : startSize(startSize), maxSize(maxSize), incSize(incSize),
          shrink(shrink), keys(array<K>(startSize, maxSize, incSize, shrink)),
          values(array<V>(startSize, maxSize, incSize, shrink)) {
        size = 0;
        allocSize = startSize;
    }

    ~map() {
    }

    V operator[](K key) const {
        for (unsigned int i = 0; i < keys.length(); i++) {
            if (keys[i] == key)
                return values[i];
        }
        assert(false);  // key not found
        memset(&bad, 0, sizeof(bad));
        return bad;
    }

    V &operator[](K key) {
        for (unsigned int i = 0; i < keys.length(); i++) {
            if (keys[i] == key) {
                return values[i];
            }
        }
        int i = keys.add(key);
        if (i == -1) {
            assert(false);  // key not found
            memset(&bad, 0, sizeof(bad));
            return bad;
        }
        if (i >= 0) {
            return values[i];
        }
        assert(false);  // key not found
        memset(&bad, 0, sizeof(bad));
        return bad;
    }

    int find(K key) {
        for (unsigned int i = 0; i < keys.length(); i++) {
            if (keys[i] == key)
                return i;
        }
        return -1;
    }

    int erase(K key) {
        for (unsigned int i = 0; i < keys.length(); i++) {
            if (keys[i] == key) {
                values.erase(i);
                keys.erase(i);
                return i;
            }
        }
        return -1;
    }

    bool isEmpty() {
        if (size == 0)
            return true;
        else
            return false;
    }

    unsigned int length() {
        return (size);
    }

    unsigned int peak() {
        return (peakSize);
    }
};
}
