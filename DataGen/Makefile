# Author: Chase Brown
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

# Command: make Fundamental
FundamentalObjs := $(OBJ)/Fundamental.o

Quick: $(FundamentalObjs)
	$(PP) $(CXXFLAGS) -o $(EXE)/Fundamental$(FundamentalObjs)
	$(EXE)/./Fundamental

$(OBJ)/Fundamental.o: $(SRC)/Fundamental.cpp
	$(PP) $(CXXFLAGS) -c $(SRC)/Fundamental.cpp -o $@

QuickObjs := $(OBJ)/Quick.o

Fundamental: $(QuickObjs)
	$(PP) $(CXXFLAGS) -o $(EXE)/Quick $(QuickObjs)
	$(EXE)/./Quick

$(OBJ)/Quick.o: $(SRC)/Fundamental.cpp $(INC)/Quick.h
	$(PP) $(CXXFLAGS) -c $(SRC)/Fundamental.cpp -o $@


# Command: make Creative
CreativeObjs := $(OBJ)/Creative.o

Creativecpp: $(FundamentalObjs)
	$(PP) $(CXXFLAGS) -o $(EXE)/Creative$(CreativeObjs)
	$(EXE)/./Creative

$(OBJ)/Creative.o: $(SRC)/Creative.cpp
	$(PP) $(CXXFLAGS) -c $(SRC)/Creative.cpp -o $@

QuickCreativeObjs := $(OBJ)/QuickCreative.o

Creative: $(QuickCreativeObjs)
	$(PP) $(CXXFLAGS) -o $(EXE)/QuickCreative $(QuickCreativeObjs)
	$(EXE)/./QuickCreative

$(OBJ)/QuickCreative.o: $(SRC)/Creative.cpp $(INC)/QuickCreative.h
	$(PP) $(CXXFLAGS) -c $(SRC)/Creative.cpp -o $@




# Make all
all: SorDLLTest PQTest Creative

# make initialize to create folders for the objects and executables
initialize:
	mkdir objects executables

# Make clean
clean :
	rm -rf *.o $(OBJ)/* $(EXE)/*
