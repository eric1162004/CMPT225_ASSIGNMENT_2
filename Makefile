# Full name:    Eric Cheung
# Student ID:   301125805
# Computing-id: hccheung

# Copyright Notice:
# This code is part of the assignment 2a for CSPT 225, Spring 2025.
# Unauthorized copying or distribution is prohibited.

# Purpose of this file:

CXX = g++ # Use C++ compiler
CXXFLAGS = -std=c++11 -Wall -g
	
all: QuadraticProbingTest
runTest1: QuadraticProbingTest
runTest2: BiMapTest

# Compile Quadratic Probing Test and run it
QuadraticProbingTest: TestQuadraticProbing.cpp QuadraticProbing.cpp QuadraticProbing.h
	$(CXX) $(CXXFLAGS) -o QuadraticProbingTest TestQuadraticProbing.cpp
	./QuadraticProbingTest 

BiMapTest: TestBiMap.cpp BiMap.h
	$(CXX) $(CXXFLAGS) -o TestBiMap TestBiMap.cpp
	./TestBiMap 

clean:
	rm -f QuadraticProbingTest