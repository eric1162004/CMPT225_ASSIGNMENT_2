# Full name:    Eric Cheung
# Student ID:   301125805
# Computing-id: hccheung

# Copyright Notice:
# This code is part of the assignment 2a for CSPT 225, Spring 2025.
# Unauthorized copying or distribution is prohibited.

# Purpose of this file:
# This file is used to compile and run the test files for the 
# QuadraticProbing and BiMap classes.

CXX = g++ # Use C++ compiler
# Use C++11 standard, enable all warnings, 
# and include debugging information
CXXFLAGS = -std=c++11 -Wall -g 
	
all: QuadraticProbingTest BiMapTest

# Compile Quadratic Probing Test and run it
QuadraticProbingTest: TestQuadraticProbing.cpp QuadraticProbing.cpp QuadraticProbing.h
	$(CXX) $(CXXFLAGS) -o QuadraticProbingTest TestQuadraticProbing.cpp
	./QuadraticProbingTest 

# Compile BiMap Test and run it
BiMapTest: TestBiMap.cpp BiMap.h QuadraticProbingBiMap.h QuadraticProbing.cpp
	$(CXX) $(CXXFLAGS) -o BiMapTest TestBiMap.cpp
	./BiMapTest 

clean:
	rm -f QuadraticProbingTest BiMapTest