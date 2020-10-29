# Authors: Jacob Sardo and Chase Brown
# E-mails: jsardo@nd.edu cbrown54@nd.edu
#
# This is the Makefile for Preternship NetworkAssess Program

# G++ is for the GCC compiler for C++
PP := g++

# CFLAGS are the compiler flages for when we compile C code in this course
FLAGS := -O0 -g -Wall
CXXFLAGS := -m64 -std=c++11 $(FLAGS)
PQCFLAGS := -O0 -g -Wall -Wextra -Wconversion -Wshadow -pedantic -Werror -lm
PQCXX    := -m64 -std=c++11 -Weffc++ $(PQCFLAGS)

INC := include
SRC := src
OBJ := obj
EXE := exe

# Command: make NetworkAssess
NetworkAssessObjs := $(OBJ)/NetworkAssess.o

NetworkAssess: $(NetworkAssessObjs)
	$(PP) $(PQCXX) -o $(EXE)/NetworkAssess $(NetworkAssessObjs)
	$(EXE)/NetworkAssess

$(OBJ)/NetworkAssess.o: $(SRC)/NetworkAssess.cpp
	$(PP) $(PQCXX) -c $(SRC)/NetworkAssess.cpp -o $@

initialize:
	mkdir $(OBJ) $(EXE)

# Make clean
clean:
		rm -rf *.o $(OBJ)/* $(EXE)/*
