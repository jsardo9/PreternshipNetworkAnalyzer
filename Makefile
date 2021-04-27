# Author: Chase Brown & Jacob Sardo
# This is the Makefile for the CSE 20312 - Preternship
# This Makefile contains the compiling commands to generate a new set of data

# G++ is for the GCC compiler for C++
PP := g++

# CXXFLAGS are the compiler flages for when we compile C++ code in this course -Wconversion
FLAGS := -O0 -g -Wall -Wextra -Wshadow -pedantic -Werror
CXXFLAGS := -m64 -std=c++11 -Weffc++ $(FLAGS)

# Variables for Folders
INC := include
SRC := src
OBJ := obj
EXE := exe

# Command: make NetworkAssess
NetworkAssessObjs := $(OBJ)/NetworkAssess.o
NetworkFunctionsObjs := $(OBJ)/NetworkFunctions.o

$(OBJ)/NetworkAssess.o: $(SRC)/NetworkAssess.cpp
	$(PP) $(CXXFLAGS) -c $(SRC)/NetworkAssess.cpp -o $@

$(OBJ)/NetworkFunctions.o: $(SRC)/NetworkAssess.cpp $(INC)/NetworkFunctions.h
	$(PP) $(CXXFLAGS) -c $(SRC)/NetworkAssess.cpp -o $@

NetworkFunctions: initialize $(NetworkAssessObjs) $(OBJ)/NetworkAssess.o
	$(PP) $(CXXFLAGS) -o $(EXE)/NetworkAssess $(NetworkAssessObjs)

NetworkAssess: initialize NetworkFunctions $(OBJ)/NetworkAssess.o
	$(PP) $(CXXFLAGS) -o $(EXE)/NetworkFunctions $(OBJ)/NetworkAssess.o
	$(PP) $(CXXFLAGS) DataGen/src/generate.cpp -o DataGen/exe/generate
	DataGen/exe/generate 12 60 4 1920
	$(EXE)/NetworkAssess



# Make all
all: NetworkFunctions NetworkAssess

# make initialize to create folders for the objects and executables
initialize: clean
	mkdir $(OBJ) $(EXE) DataGen/exe DataGen/data

# Make clean
clean :
	rm -rf $(OBJ) $(EXE) DataGen/exe DataGen/data
