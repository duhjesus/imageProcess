/*
 CELL.h header file contains:
 (1) CELL class declaration
 */
#ifndef CELL_h
#define CELL_h

#include <stdint.h>
#include <stdlib.h>

class CELL 
{
public:
	//Default Constructor
	CELL(); 
	//Constructor with RGBA parameters
	CELL(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
	// A single CELL's stored RGBA values
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;
};

// something to test (alternate way:)
// accessor and mutator methods accessing private color variables
// could lead to slow down as well? many function calls/pointers return value
// for rgba values overhead ? O_o

//many CELLs accessing 4 color streams accessing memory on the heap
//could lead to significant slow down. don't do it this way probably.
//Returns all the dynamic memory used by the object
//	~CELL();
//private:
//	int * rgba = new int[4];

#endif