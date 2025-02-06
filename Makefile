# Full name:    Eric Cheung
# Student ID:   301125805
# Computing-id: hccheung

# Copyright Notice:
# This code is part of the assignment 2a for CSPT 225, Spring 2025.
# Unauthorized copying or distribution is prohibited.

# Purpose of this file:
# Compiles TestQuadraticProbing.cpp - make all 

CXX = g++ # Use C++ compiler
CXXFLAGS = -std=c++11 -Wall -g
	
all: QuadraticProbingTest

QuadraticProbingTest: TestQuadraticProbing.cpp QuadraticProbing.h
	$(CXX) $(CXXFLAGS) -o QuadraticProbingTest TestQuadraticProbing.cpp 

clean:
	rm -f QuadraticProbingTest $(TEST_EXES)