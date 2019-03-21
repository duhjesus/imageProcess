/*
CELL.cpp header file contains:
 (1) CELL class definition
*/
#include "cell.h"

//Default CELL constructor
//creates a black CELL
CELL::CELL()
{
	red = 63;
	green = 159;
	blue = 191;
	alpha = 255;
}

//CELL Constructor w/ Parameters
//creates a CELL with given RGBA colors
 CELL::CELL(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	 red = red;
	 green = green;
	 blue = blue;
	 alpha = alpha;
}
