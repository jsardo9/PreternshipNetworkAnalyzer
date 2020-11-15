# Author: Chase Brown & Jacob Sardo
# This is the Makefile for the CSE 20312 - Preternship
# This Makefile contains the compiling commands to generate a new set of data

# G++ is for the GCC compiler for C++
PP := g++

# CXXFLAGS are the compiler flages for when we compile C++ code in this course
FLAGS := -O0 -g -Wall -Wextra -Wconversion -Wshadow -pedantic -Werror
CXXFLAGS := -m64 -std=c++11 -Weffc++ $(FLAGS)

# Variables for Folders
INC := include
SRC := src
OBJ := obj
EXE := exe

# Command: make NetworkAssess
NetworkAssessObjs := $(OBJ)/NetworkAssess.o

NetworkFunctions: $(NetworkAssessObjs)
	$(PP) $(CXXFLAGS) -o $(EXE)/NetworkAssess $(NetworkAssessObjs)

$(OBJ)/NetworkAssess.o: $(SRC)/NetworkAssess.cpp
	$(PP) $(CXXFLAGS) -c $(SRC)/NetworkAssess.cpp -o $@

NetworkFunctionsObjs := $(OBJ)/NetworkFunctions.o

NetworkAssess: $(NetworkFunctionsObjs)
	$(PP) $(CXXFLAGS) -o $(EXE)/NetworkFunctions $(NetworkFunctionsObjs)
	$(EXE)/./NetworkAssess

$(OBJ)/NetworkFunctions.o: $(SRC)/NetworkAssess.cpp $(INC)/NetworkFunctions.h
	$(PP) $(CXXFLAGS) -c $(SRC)/NetworkAssess.cpp -o $@

# Make all
all: NetworkFunctions NetworkAssess

# make initialize to create folders for the objects and executables
initialize:
	mkdir $(OBJ) $(EXE)

# Make clean
clean :
	rm -rf *.o $(OBJ)/* $(EXE)/*
