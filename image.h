/*
image.h header file contains:
 (1) image class declaration
 */
#ifndef image_h
#define image_h

//my CELL class definition 
#include "cell.h"

//libPng library
#include<png.h>

#include<stdio.h>
#include<stdlib.h>

#include<iostream>
#include<sstream> 
#include<string>

using namespace std;

class Image
{
public:
	//default constructor
	Image();
	//constructor, image created from file stored
	Image(string const & file_image);
	//copy constructor, exact image created with data of another image
	//Image(Image const& original_image);
	//destructor, frees previously allocated memory on heap
	//~Image();
	//=============================================================

	// assignment operator = :
	//Image const& operator=(Image const& original_image);	
	//equality operator == :
	//bool operator==(Image const& original_image) const;	
	//=============================================================

	//read&write functions
	bool readImage(string const& file_image);
	bool writeImage(string const& file_image);

	//accessor functions 
	size_t getWidth() const;
	size_t getHeight() const;
	CELL * getGrid() const;

	//mutator function. I can now access undelying data stored in an image
	//will use this to deal with frames 
	void manipulateImage();
	void filter();

private:
	size_t _width;
	size_t _height;
	CELL * _pixelGrid;
    //CELL g
};

#endif 
