/*
Full name:    Eric Cheung
Student ID:   301125805
Computing-id: hccheung

Copyright Notice:
This code is part of the assignment 2a for CSPT 225, Spring 2025.
Unauthorized copying or distribution is prohibited.

Purpose of this file:
This file implements a HashTable class using quadratic probing.
The hash table supports HashedObj insertion, removal, and lookup
of key-value pairs.
*/
#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
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
// bool insert( x )       --> Insert x
// bool remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// void makeEmpty( )      --> Remove all items
// int hashCode( string str ) --> Global method to hash strings

template <typename HashedObj>
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
     * Check if the hash table contains the specified Obj.
     *
     * @param x The obj to check.
     * @return True if the obj is present, false otherwise.
     */
    bool contains(const HashedObj &x) const
    {
        return isActive(findPos(x));
    }

    /**
     * Remove all objs from the hash table.
     */
    void makeEmpty()
    {
        currentSize = 0;
        for (auto &entry : array)
            entry.info = EMPTY;
    }

    /**
     * Insert an object into the hash table.
     *
     * @param x The object to insert.
     * @return True if the object was successfully inserted, false otherwise.
     */
    bool insert(const HashedObj &x)
    {
        // Insert x as active
        int currentPos = findPos(x);
        if (isActive(currentPos))
            return false;

        // If the position is already occupied by active element,
        // this mean the hash table is full.
        if (array[currentPos].info != DELETED)
            ++currentSize;

        // If the position is not maked as DELETED or ACTIVE,
        // meaning the position is EMPTY and is available to insertion.
        array[currentPos].element = x;
        array[currentPos].info = ACTIVE;

        // Rehash; see Section 5.5
        if (currentSize > array.size() / 2)
            rehash();

        return true;
    }

    /**
     * Insert an object into the hash table using move semantics.
     *
     * @param x The object to insert (rvalue reference).
     * @return True if the object was successfully inserted, false otherwise.
     */
    bool insert(HashedObj &&x)
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
        array[currentPos] = std::move(x);
        array[currentPos].info = ACTIVE;

        // Rehash; see Section 5.5
        if (currentSize > array.size() / 2)
            rehash();

        return true;
    }

    /**
     * Remove the specified object from the hash table.
     *
     * @param x The object to remove.
     * @return True if the object was successfully removed, false otherwise.
     */
    bool remove(const HashedObj &x)
    {
        int currentPos = findPos(x);
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
     * Represents an entry in the hash table, 
     * storing a key, value, and status.
     */
    struct HashEntry
    {
        HashedObj element;
        EntryType info;

        /**
         * Constructor for HashEntry.
         *
         * @param e The object to store (default: default-constructed HashedObj).
         * @param i The status of the entry (default: EMPTY).
         */
        HashEntry(const HashedObj &e = HashedObj{}, EntryType i = EMPTY)
            : element{e}, info{i} {}

        /**
         * Move constructor for HashEntry.
         *
         * @param e The object to store (rvalue reference).
         * @param i The status of the entry (default: EMPTY).
         */
        HashEntry(HashedObj &&e, EntryType i = EMPTY)
            : element{std::move(e)}, info{i} {}
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
     * @param x The OBJ to find.
     * @return The position of the OBJ or the first empty position.
     */
    int findPos(const HashedObj &x) const
    {
        int offset = 1;             // Offset value for hash(x)
        int currentPos = myhash(x); // Returns the initial hash index

        // Stop searching if current position is
        // EMPTY or the element is found.
        while (array[currentPos].info != EMPTY &&
               array[currentPos].element != x)
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
                insert(std::move(entry.element));
    }

    /**
     * Generate a hash value for the specified obj.
     *
     * @param x The obj to hash.
     * @return The hash value for the obj.
     */
    size_t myhash(const HashedObj &x) const
    {
        // Using static here so the hf is reused accoss all calls
        static hash<HashedKey> hf;

        // Note: hf(x) returns the hash value for x
        return hf(x) % array.size();
    }
};

#endif
