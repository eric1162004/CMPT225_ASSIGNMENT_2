/*
Full name:    Eric Cheung
Student ID:   301125805
Computing-id: hccheung

Copyright Notice:
This code is part of the assignment 2a for CSPT 225, Spring 2025.
Unauthorized copying or distribution is prohibited.

Purpose of this file:
This file implements a HashTable class using quadratic probing.
The hash table supports HashedObj insertion, removal, and lookup.
To maintain performance,, the table rehashes itself when the size
reaches a threshold.
*/
#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
using namespace std;

// Return a prime number at least as large as n.
// Used to generate the next hash table size.
// Assumes n > 0.
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
    // Constructor: Initialize a hash table with an array of size
    // that is a prime number >= of a given size.
    // If the size is not provided, it is default to 101.
    explicit HashTable(int size = 101) : array(nextPrime(size))
    {
        // Initialize all HashEntry to EMPTY
        makeEmpty();
    }

    // Check if the hash table contain the HashedObj x
    bool contains(const HashedObj &x) const
    {
        // Locate the position of x in array.
        // Return true if x is in the array and is active
        return isActive(findPos(x));
    }

    // Clear the hash table by marking all HashEntry to EMPTY
    void makeEmpty()
    {
        // Clear the size counter
        currentSize = 0;
        for (auto &entry : array)
            entry.info = EMPTY;
    }

    // Insert an HashedObj x into the hash table
    // bool insert(const HashedObj &x)
    // {
    //     // Insert x as active
    //     int currentPos = findPos(x);

    //     //
    //     if (isActive(currentPos))
    //         return false;

    //     if (array[currentPos].info != DELETED)
    //         ++currentSize;

    //     array[currentPos].element = x;
    //     array[currentPos].info = ACTIVE;

    //     // Rehash; see Section 5.5
    //     if (currentSize > array.size() / 2)
    //         rehash();

    //     return true;
    // }

    // Insert an HashedObj x into the hash table
    // with move semantics
    bool insert(HashedObj &&x)
    {
        // Insert x as active
        int currentPos = findPos(x);

        // If the position is already occupied by active element,
        // this mean the hash table is full. 
        // Remark: this should not happen as the hash table will
        // rehash as it reaches a threshold.
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

    // Remove an HashedObj x from the hash table.
    bool remove(const HashedObj &x)
    {
        int currentPos = findPos(x);
        // The position is either EMPTY or DELETE,
        // meaning x is not in the array. 
        if (!isActive(currentPos))
            return false;

        array[currentPos].info = DELETED;
        return true;
    }

    enum EntryType
    {
        ACTIVE, // The entry is currently occupied by a active element.
        EMPTY,  // The entry is unoccupied.
        DELETED // The entry has been deleted.
    };

private:
    // Hold information about an entry within a hash table
    struct HashEntry
    {
        HashedObj element; // The actual data being stored 
        EntryType info; // EMPTY, OCCUPIED or DELETED

        // Allow constructing an HashEntry without
        // providing a HashedObj. 
        // The element is set to default according to its type.
        HashEntry(const HashedObj &e = HashedObj{}, EntryType i = EMPTY)
            : element{e}, info{i} {}

        // Constructor for the move semantics
        // Transfer resource of a temp obj into a destination object
        // Note: &&e indicates e is a rvalue reference
        HashEntry(HashedObj &&e, EntryType i = EMPTY)
            : element{std::move(e)}, info{i} {}
    };

    vector<HashEntry> array; // Array that holds the HashEntries
    int currentSize; // The current size of the array

    // Return the status of a HashEntry
    bool isActive(int currentPos) const
    {
        return array[currentPos].info == ACTIVE;
    }

    // Find the position for an element x 
    // the array using quadratic probing. 
    // This function either returns the index of x,
    // if x is found, or the index of the first empty position.
    int findPos(const HashedObj &x) const
    {
        int offset = 1; // offset value for hash(x) 
        int currentPos = myhash(x); //  Returns the initial hash index

        // Stop searching if current position is 
        // EMPTY or the element is found. 
        while (array[currentPos].info != EMPTY &&
               array[currentPos].element != x)
        {
            currentPos += offset; // Compute ith probe
            offset += 2;
            // same effect as mod array.size()
            if (currentPos >= array.size())
                currentPos -= array.size();
        }

        return currentPos;
    }

    // Resizes the hash table to a larger size
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

    // Generate an inital hash value of the HashedObj x.
    // Hash value for table = (hash value of HashedObj) mod arraySize
    size_t myhash(const HashedObj &x) const
    {
        // Using static here so the hf is reused accoss all calls
        static hash<HashedObj> hf;

        // Note: hf(x) returns the hash value for x
        return hf(x) % array.size();
    }
};

#endif
