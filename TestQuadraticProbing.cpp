/*
Full name:    Eric Cheung
Student ID:   301125805
Computing-id: hccheung

Copyright Notice:
This code is part of the assignment 2a for CSPT 225, Spring 2025.
Unauthorized copying or distribution is prohibited.

Purpose of this file:
This file tests the functionality of the HashTable class.
It verify the correctness of the hash table on insertions,
deletions and lookups.
*/
#include <iostream>
#include "QuadraticProbing.h"
using namespace std;

// Simple main
int main()
{
    HashTable<int> h1;
    HashTable<int> h2;

    const int NUMS = 4000; // Number of elements to test
    const int GAP = 37; // Interval between elements
    int i; 

    cout << "Checking... (no more output means success)" << endl;

    // Insert elements into h1
    for (i = GAP; i != 0; i = (i + GAP) % NUMS)
        h1.insert(i);

    // Create a copy of h1
    h2 = h1;

    // Remove all odd numbered elements
    for (i = 1; i < NUMS; i += 2)
        h2.remove(i);

    // Verify all even numbered are still present in the hash table
    for (i = 2; i < NUMS; i += 2)
        if (!h2.contains(i))
            cout << "Contains fails " << i << endl;

    // Verify if all odd numbered elements have been removed
    for (i = 1; i < NUMS; i += 2)
    {
        if (h2.contains(i))
            cout << "OOPS!!! " << i << endl;
    }

    return 0;
}
