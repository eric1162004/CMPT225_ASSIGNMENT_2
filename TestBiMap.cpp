/*
Full name:    Eric Cheung
Student ID:   301125805
Computing-id: hccheung

Copyright Notice:
This code is part of the assignment 2a for CSPT 225, Spring 2025.
Unauthorized copying or distribution is prohibited.

Purpose of this file:
This file tests the functionality of the BiMap class.
It verify the correctness of the BiMap public operations.
Please refer to BiMap.h for operations documantation.
*/
#include <iostream>
#include "BiMap.h"
using namespace std;

// Check if an exception is thrown for getKey
template <typename KeyType, typename ValType>
bool testGetKeyException(BiMap<KeyType, ValType>& bimap, const ValType& val) {
    try {
        bimap.getKey(val);
        return false; // No exception thrown
    } catch (const std::exception& e) {
        return true; // Exception thrown
    }
}

// Check if an exception is thrown for getVal
template <typename KeyType, typename ValType>
bool testGetValException(BiMap<KeyType, ValType>& bimap, const KeyType& key) {
    try {
        bimap.getVal(key);
        return false; // No exception thrown
    } catch (const std::exception& e) {
        return true; // Exception thrown
    }
}

int main() {
    cout << "Checking... (no more output means success)" << endl;

    // Test: getSize() - Should return 0 if the map is empty.
    BiMap<int, int> bm1;
    if (bm1.getSize() != 0)
        cout << "FAIL getSize: should return 0 if the map is empty." << endl;

    // Test: insert(x,y) followed by getSize()
    for (int i = 0; i < 3; i++)
        bm1.insert(i, i + 100);
    if (bm1.getSize() != 3)
        cout << "FAIL Insert/getSize: Map size should increment after insertion." << endl;

    // Test: insert(1,1) followed by insert(1,2)
    BiMap<int, int> bm2;
    bm2.insert(1, 1);
    if (bm2.insert(1, 2))
        cout << "FAIL Insert: Cannot insert duplicate key." << endl;

    // Test: insert(1,1) followed by insert(2,1)
    BiMap<int, int> bm3;
    bm3.insert(1, 1);
    if (bm3.insert(2, 1))
        cout << "FAIL Insert: Cannot insert duplicate value." << endl;

    // Test: containsKey(x), containsVal(x)
    BiMap<int, int> bm4;
    if (bm4.containsKey(1))
        cout << "FAIL containsKey: should return false if key is not in the map." << endl;
    if (bm4.containsVal(2))
        cout << "FAIL containsVal: should return false if value is not in the map." << endl;

    bm4.insert(1, 2);
    if (!bm4.containsKey(1))
        cout << "FAIL containsKey: should return true if key is in the map." << endl;
    if (!bm4.containsVal(2))
        cout << "FAIL containsVal: should return true if value is in the map." << endl;

    // Test: removeKey(x), removeVal(x), getKey(x), getVal(x)
    BiMap<int, int> bm5;
    if (bm5.removeKey(1))
        cout << "FAIL removeKey: should return false if key is not in the map." << endl;
    if (bm5.removeVal(2))
        cout << "FAIL removeVal: should return false if value is not in the map." << endl;

    if (!testGetKeyException(bm5, 1))
        cout << "FAIL getKey: should throw exception if value is not in the map." << endl;
    if (!testGetValException(bm5, 2))
        cout << "FAIL getVal: should throw exception if key is not in the map." << endl;

    bm5.insert(1, 1);
    bm5.insert(2, 3);
    bm5.insert(4, 5);
    if (bm5.getKey(1) != 1)
        cout << "FAIL getKey: did not return the correct key." << endl;
    if (bm5.getVal(1) != 1)
        cout << "FAIL getVal: did not return the correct value." << endl;
    if (bm5.getKey(3) != 2)
        cout << "FAIL getKey: did not return the correct key." << endl;
    if (bm5.getVal(2) != 3)
        cout << "FAIL getVal: did not return the correct value." << endl;
    if (bm5.getKey(5) != 4)
        cout << "FAIL getKey: did not return the correct key." << endl;
    if (bm5.getVal(4) != 5)
        cout << "FAIL getVal: did not return the correct value." << endl;

    if (!bm5.removeKey(1))
        cout << "FAIL removeKey: should return true if key is in the map." << endl;
    if (bm5.removeVal(2))
        cout << "FAIL removeVal: should return false if value is not in the map." << endl;

    bm5.insert(3, 4);
    bm5.removeKey(3);
    if (bm5.containsVal(4))
        cout << "FAIL removeKey: should remove the value associated with the key." << endl;

    bm5.insert(5, 6);
    bm5.removeVal(6);
    if (bm5.containsKey(5))
        cout << "FAIL removeVal: should remove the key associated with the value." << endl;

    // Test: makeEmpty()
    BiMap<int, int> bm6;
    bm6.insert(1, 2);
    bm6.insert(3, 4);
    bm6.makeEmpty();
    if (bm6.getSize() != 0)
        cout << "FAIL makeEmpty: should remove all pairs from the map." << endl;

    return 0;
}