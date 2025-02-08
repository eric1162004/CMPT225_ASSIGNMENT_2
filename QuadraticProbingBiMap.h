/*
Full name:    Eric Cheung
Student ID:   301125805
Computing-id: hccheung

Copyright Notice:
This code is part of the assignment 2a for CSPT 225, Spring 2025.
Unauthorized copying or distribution is prohibited.

Purpose of this file:
This file implements a modified HashTable class using quadratic probing
to meet the needs of the BiMap class. The hash table supports HashedObj 
insertion, removal, and lookup of key-value pairs.
*/

#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include "QuadraticProbing.cpp"
using namespace std;

/**
 * Returns the smallest prime number greater than or equal to n.
 * Used to determine the size of the hash table.
 * 
 * @param n The minimum size of the hash table.
 * @return A prime number >= n.
 */
int nextPrime(int n);

// QuadraticProbing Hash table class
//
// CONSTRUCTION: an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// bool insert( k , v )       --> Insert key and value
// bool remove( k )           --> Remove entry with key
// bool contains( k )         --> Return true if key is present
// HashedVal getVal( k )      --> Return the value with key
// void makeEmpty( )          --> Remove all items
// int hashCode( string str ) --> Global method to hash strings

template <typename HashedKey, typename HashedVal>
class HashTable
{
public:
    /**
     * Constructor
     *
     * Initializes the hash table with an array of size equal to the smallest prime
     * number greater than or equal to the specified size. If no size is provided,
     * the default size is 101. 
     *
     * @param size The initial size of the hash table (default: 101).
     */
    explicit HashTable(int size = 101) : array(nextPrime(size))
    {
        makeEmpty();
    }

    /**
     * Check if the hash table contains the specified key.
     *
     * @param x The key to check.
     * @return True if the key is present, false otherwise.
     */
    bool contains(const HashedKey &x) const
    {
        // Locate the position of x in array.
        // Return true if x is in the array and is active
        return isActive(findPos(x));
    }

    /**
     * Get the value associated with the specified key.
     *
     * @param x The key to look up.
     * @return The value associated with the key.
     * @throws std::runtime_error If the key is not found in the hash table.
     */
    HashedVal getVal(const HashedKey &x) const
    {
        if (!contains(x))
            throw std::runtime_error("Key not found in hash table.");
        return array[findPos(x)].value;
    }

    /**
     * Remove all key-value pairs from the hash table.
     */
    void makeEmpty()
    {
        for (auto &entry : array)
            entry.info = EMPTY;
        currentSize = 0;
    }

    /**
     * Insert a key-value pair into the hash table.
     *
     * @param x The key to insert.
     * @param y The value to insert.
     * @return True if the pair was successfully inserted, false otherwise.
     */
    bool insert(const HashedKey &x, const HashedVal &y)
    {
        // Insert x as active
        int currentPos = findPos(x);

        // If the position is already occupied by active element,
        // this mean the hash table is full.
        if (isActive(currentPos))
            return false;

        // If the position is not maked as DELETED or ACTIVE,
        // meaning the position is EMPTY and is available to insertion.
        if (array[currentPos].info != DELETED)
            ++currentSize;

        array[currentPos].key = x;
        array[currentPos].value = y;
        array[currentPos].info = ACTIVE;

        // Rehash; see Section 5.5
        if (currentSize > (int)array.size() / 2)
            rehash();

        return true;
    }

    /**
     * Insert a key-value pair into the hash table using move semantics.
     *
     * @param x The key to insert (rvalue reference).
     * @param y The value to insert (rvalue reference).
     * @return True if the pair was successfully inserted, false otherwise.
     */
    bool insert(HashedKey &&x, HashedVal &&y)
    {
        // Insert x as active
        int currentPos = findPos(x);

        // If the position is already occupied by active element,
        // this mean the hash table is full.
        if (isActive(currentPos))
            return false;

        // If the position is not maked as DELETED or ACTIVE,
        // meaning the position is EMPTY and is available to insertion.
        if (array[currentPos].info != DELETED)
            ++currentSize;

        // Use move semantics to avoid expensive copying
        array[currentPos].key = std::move(x);
        array[currentPos].value = std::move(y);
        array[currentPos].info = ACTIVE;

        // Rehash; see Section 5.5
        if (currentSize > (int)array.size() / 2)
            rehash();

        return true;
    }

    /**
     * Remove the key-value pair with the specified key.
     *
     * @param x The key to remove.
     * @return True if the pair was successfully removed, false otherwise.
     */
    bool remove(const HashedKey &x)
    {
        int currentPos = findPos(x);

        // If the position is either EMPTY or DELETE,
        // this mean x is not in the array.
        if (!isActive(currentPos))
            return false;

        array[currentPos].info = DELETED;
        return true;
    }

    /**
     * Define the status of a hash table entry.
     */
    enum EntryType
    {
        ACTIVE, // The entry is currently occupied by a active element.
        EMPTY,  // The entry is unoccupied.
        DELETED // The entry has been deleted.
    };

private:
    /**
     * Represents an entry in the hash table, storing a key, value, and status.
     */
    struct HashEntry
    {
        HashedKey key;   // The key being stored
        HashedVal value; // The value being stored
        EntryType info;  // EMPTY, OCCUPIED or DELETED

        /**
         * Constructor for HashEntry.
         *
         * @param k The key to store (default: default-constructed HashedKey).
         * @param v The value to store (default: default-constructed HashedVal).
         * @param i The status of the entry (default: EMPTY).
         */
        HashEntry(const HashedKey &k = HashedKey(),
                  const HashedVal &v = HashedVal(),
                  EntryType i = EMPTY)
            : key{k},
              value{v},
              info{i} {}

        /**
         * Move constructor for HashEntry.
         *
         * @param k The key to store (rvalue reference).
         * @param v The value to store (rvalue reference).
         * @param i The status of the entry (default: EMPTY).
         */
        HashEntry(HashedKey &&k,
                  HashedVal &&v,
                  EntryType i = EMPTY)
            : key{std::move(k)},
              value{std::move(v)},
              info{i} {}
    };

    vector<HashEntry> array; // Array that holds the HashEntries
    int currentSize;         // The current size of the array

    /**
     * Check if the entry at the specified position is active.
     *
     * @param currentPos The position to check.
     * @return True if the entry is active, false otherwise.
     */
    bool isActive(int currentPos) const
    {
        return array[currentPos].info == ACTIVE;
    }

    /**
     * Find the position for the specified key using quadratic probing.
     *
     * @param x The key to find.
     * @return The position of the key or the first empty position.
     */
    int findPos(const HashedKey &x) const
    {
        int offset = 1;             // Offset value for hash(x)
        int currentPos = myhash(x); // Returns the initial hash index

        // Stop searching if current position is
        // EMPTY or the element is found.
        while (array[currentPos].info != EMPTY &&
               array[currentPos].key != x)
        {
            currentPos += offset; // Compute ith probe
            offset += 2;
            // same effect as mod array.size()
            if (currentPos >= (int)array.size())
                currentPos -= (int)array.size();
        }

        return currentPos;
    }

    /**
     * Resize the hash table to a larger size and rehash all active entries.
     */
    void rehash()
    {
        vector<HashEntry> oldArray = array;

        // Create new double-sized, empty table
        array.resize(nextPrime(2 * oldArray.size()));
        for (auto &entry : array)
            entry.info = EMPTY;

        // Copy table over
        currentSize = 0;
        for (auto &entry : oldArray)
            if (entry.info == ACTIVE)
                insert(std::move(entry.key), std::move(entry.value));
    }

    /**
     * Generate a hash value for the specified key.
     *
     * @param x The key to hash.
     * @return The hash value for the key.
     */
    size_t myhash(const HashedKey &x) const
    {
        // Using static here so the hf is reused accoss all calls
        static hash<HashedKey> hf;

        // Note: hf(x) returns the hash value for x
        return hf(x) % array.size();
    }
};

#endif
