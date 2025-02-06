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

// Bijective Map class
//
// CONSTRUCTION: Implemented with two hash tables with Quaddratic Probing.
//
// ******************PUBLIC OPERATIONS*********************
// void makeEmpty()           --> Remove all pairs
// int getSize() const        --> Return the current number of pairs
// bool insert(x, y)          --> Insert pair <x,y>, provided x is not the key of a current pair
//                                and y is not the value of a current pair.
//                                Return true iff <x,y> was inserted.
// bool containsKey(x)        --> Return true if x is the key of a current pair
// bool containsVal(x)        --> Return true if x is the value of a current pair
// bool removeKey(x)          --> Remove the pair with key x if it exists
// bool removeVal(x)          --> Remove the pair with value x if it exists
// const & ValType getVal(x)  --> Return the value associated with key x
// const & KeyType getKey(x)  --> Return the key associated with value x

template <typename KeyType, typename ValType> //
class BiMap
{
public:
    BiMap()
        // constructor
        void makeEmpty()
        // remove all pairs
        int getSize() const
        // returns the current number of pairs
        bool insert(const KeyType &x, const ValType &y)
        // insert pair <x,y>, provided x is not the
        // key of a current pair and y is not the value of
        // a current pair.  Return true iff <x,y> was inserted.
        bool containsKey(const &KeyType x) const
        // returns true if x is the key of a current pair.
        bool containsVal(const &ValType x) const
        // returns true if x is the value of a current pair.
        bool removeKey(const KeyType &x)
        // removes the pair with key x if it exists.
        bool removeVal(const ValType &x)
        // removes the pair with values x if it exists.
        const ValType& getVal(const KeyType &x) const
        // returns the value associated with key x.
        const KeyType& getKey(const ValType &x) const
    // returns the key associated with value x.
};