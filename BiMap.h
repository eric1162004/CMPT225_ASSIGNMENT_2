/*
Full name:    Eric Cheung
Student ID:   301125805
Computing-id: hccheung

Copyright Notice:
This code is part of the assignment 2a for CSPT 225, Spring 2025.
Unauthorized copying or distribution is prohibited.

Purpose of this file:
This file contains the code for a BiMap class,
that is a one-to-one map between "keys" and "values".
The main operations are to add a <key,value> pair;
to look up the value associated with a given key;
to look up the key associated with a given value;
and to remove a pair given a key or value.
*/
#ifndef BI_MAP_H
#define BI_MAP_H

#include "QuadraticProbing.h" // Required for HashTable
using namespace std;

// Bijective Map class
//
// CONSTRUCTION: Implemented with two hash tables with Quaddratic Probing.
//
// ******************PUBLIC OPERATIONS*********************
// void makeEmpty()           --> Remove all pairs
// int getSize() const        --> Return the current number of pairs
// bool insert(x, y)          --> Insert pair <x,y>, provided x is not 
//                                the key of a current pair and y is not 
//                                the value of a current pair.
//                                Return true iff <x,y> was inserted.
// bool containsKey(x)        --> Return true if x is the key of a current pair
// bool containsVal(x)        --> Return true if x is the value of a current pair
// bool removeKey(x)          --> Remove the pair with key x if it exists
// bool removeVal(x)          --> Remove the pair with value x if it exists
// const & ValType getVal(x)  --> Return the value associated with key x
// const & KeyType getKey(x)  --> Return the key associated with value x

template <typename KeyType, typename ValType>
class BiMap
{
public:
    /**
     * Constructor
     *
     * Initializes a BiMap with an array size that is the smallest prime number
     * greater than or equal to the specified size. If no size is provided,
     * the default size is 101.
     *
     * @param size The initial size of the hash tables (default: 101).
     */
    explicit BiMap(int size = 101) : keyTable(size),
                                     valTable(size)
    {
        makeEmpty();
    }

    /**
     * Remove all key-value pairs from the map.
     */
    void makeEmpty()
    {
        currentSize = 0;
        keyTable.makeEmpty();
        valTable.makeEmpty();
    }

    /**
     * Get the current number of key-value pairs in the map.
     *
     * @return The number of pairs in the map.
     */
    int getSize() const { return currentSize; }

    /**
     * Insert a new key-value pair into the map.
     *
     * The pair <x, y> is inserted only if x is not already a key in the map
     * and y is not already a value in the map.
     *
     * @param x The key to insert.
     * @param y The value to insert.
     * @return True if the pair was successfully inserted, false otherwise.
     */
    bool insert(const KeyType &x, const ValType &y)
    {
        if (keyTable.contains(x) || valTable.contains(y))
            return false;

        keyTable.insert(x, y);
        valTable.insert(y, x);
        currentSize++;
        return true;
    }

    /**
     * Check if the map contains a specific key.
     *
     * @param x The key to check.
     * @return True if the key exists in the map, false otherwise.
     */
    bool containsKey(const KeyType &x) const
    {
        return keyTable.contains(x);
    }

    /**
     * Check if the map contains a specific value.
     *
     * @param x The value to check.
     * @return True if the value exists in the map, false otherwise.
     */
    bool containsVal(const ValType &x) const
    {
        return valTable.contains(x);
    }

    /**
     * Remove the key-value pair with the specified key.
     *
     * @param x The key of the pair to remove.
     * @return True if the pair was successfully removed, false otherwise.
     */
    bool removeKey(const KeyType &x)
    {
        if (!keyTable.contains(x))
            return false;

        valTable.remove(getVal(x));
        keyTable.remove(x);
        currentSize--;
        return true;
    }

    /**
     * Remove the key-value pair with the specified value.
     *
     * @param x The value of the pair to remove.
     * @return True if the pair was successfully removed, false otherwise.
     */
    bool removeVal(const ValType &x)
    {
        if (!valTable.contains(x))
            return false;

        keyTable.remove(getKey(x));
        valTable.remove(x);
        currentSize--;
        return true;
    }

    /**
     * Get the key associated with a specific value.
     *
     * @param x The value to look up.
     * @return The key associated with the value.
     * @throws std::runtime_error If the value is not found in the map.
     */
    const KeyType getKey(const ValType &x) const
    {
        if (!valTable.contains(x))
            throw std::runtime_error("Value not found in map.");
        return valTable.getVal(x);
    }

    /**
     * Get the value associated with a specific key.
     *
     * @param x The key to look up.
     * @return The value associated with the key.
     * @throws std::runtime_error If the key is not found in the map.
     */
    const ValType getVal(const KeyType &x) const
    {
        if (!keyTable.contains(x))
            throw std::runtime_error("Key not found in map.");
        return keyTable.getVal(x);
    }

private:
    HashTable<KeyType, ValType> keyTable; // To hold map key->value pair
    HashTable<ValType, KeyType> valTable; // To hold map value->key pair
    int currentSize;                      // The current size of the map
};

#endif