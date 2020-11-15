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

# Command: make generate
generateObjs := $(OBJ)/generate.o

generator: $(generateObjs)
	$(PP) $(CXXFLAGS) -o $(EXE)/generate $(generateObjs)

$(OBJ)/generate.o: $(SRC)/generate.cpp
	$(PP) $(CXXFLAGS) -c $(SRC)/generate.cpp -o $@


generatorObjs := $(OBJ)/generator.o

generate: $(generatorObjs)
	$(PP) $(CXXFLAGS) -o $(EXE)/generator $(generatorObjs)
	$(EXE)/./generate 168 15 12 180

$(OBJ)/generator.o: $(SRC)/generate.cpp $(INC)/generator.h
	$(PP) $(CXXFLAGS) -c $(SRC)/generate.cpp -o $@

# Make all
all: generator generate

# make initialize to create folders for the objects and executables
initialize:
	mkdir $(OBJ) $(EXE)

# Make clean
clean :
	rm -rf *.o $(OBJ)/* $(EXE)/*
	rm -f data.txt
