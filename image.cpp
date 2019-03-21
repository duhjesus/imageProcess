/*
image.cpp  file contains:
 (1) image class definition
*/
#include "image.h"
#define COLOR_MAX 255
#define BIT_MAX 8


void image_error(string const & error)
{
	cerr<< error<< endl;
}

Image::Image()
{
	_width=918;
	_height=917;
	_pixelGrid = new CELL[918*917];
}
/*
Image::Image(string const & file_image)
{
	return 0;
}

Image::Image(Image const& original_image)
{
	return 0;
}

Image::~Image()
{
	return;
}

Image const& Image::operator=(Image const& original_image)
{
	return 0;
}

bool Image::operator==(Image const& original_image) const
{
	return 0;
}

CELL* Image::operator()(size_t row, size_t col)
{
	return 0;
}
*/
//read&write functions
bool Image::readImage(string const& file_image)
{
	_pixelGrid = NULL;

	FILE * fp = fopen(file_image.c_str(), "rb");
	if (!fp)
	{
		image_error("Failed to open " + file_image);
		return false;
	}

	png_byte header[8];
	fread(header, 1, 8, fp);
	if (png_sig_cmp(header, 0, 8))
	{
		image_error("File is not a valid PNG file");
		fclose(fp);
		return false;
	}

	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL); 
	if (!png_ptr)
	{
		image_error("Failed to create read struct");
		fclose(fp);
		return false;
	}

	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
	{
		image_error("Failed to create info struct");
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		fclose(fp);
		return false;
	}

	if (setjmp(png_jmpbuf(png_ptr)))
	{
		image_error("Error initializing libpng io");
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		fclose(fp);
		return false;
	}

	png_init_io(png_ptr, fp);

	png_set_sig_bytes(png_ptr, 8);

	png_read_info(png_ptr, info_ptr);

	png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);
	if (bit_depth == 16)
		png_set_strip_16(png_ptr);


	png_byte color_type = png_get_color_type(png_ptr, info_ptr);
	if (color_type != PNG_COLOR_TYPE_RGBA && color_type != PNG_COLOR_TYPE_RGB)
	{
		if (color_type == PNG_COLOR_TYPE_GRAY || color_type == PNG_COLOR_TYPE_GRAY_ALPHA) {
			if (bit_depth < 8)
				png_set_expand(png_ptr);
			png_set_gray_to_rgb(png_ptr);
		}
		if (color_type == PNG_COLOR_TYPE_PALETTE)
			png_set_palette_to_rgb(png_ptr);
	}

	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(png_ptr);

	_width = png_get_image_width(png_ptr, info_ptr);
	_height = png_get_image_height(png_ptr, info_ptr);

	png_read_update_info(png_ptr, info_ptr);

	// begin reading in the image
	if (setjmp(png_jmpbuf(png_ptr)))
	{
		image_error("Error reading image with libpng");
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		fclose(fp);
		return false;
	}
	int bytes_per_row = png_get_rowbytes(png_ptr, info_ptr);
	png_byte * row = new png_byte[bytes_per_row];
	int numchannels = png_get_channels(png_ptr, info_ptr);

	int sizeGrid = _width *_height; 
	_pixelGrid = new CELL[sizeGrid];
	for (size_t y = 0; y < _height; y++){
		png_read_row(png_ptr, row, NULL);
		png_byte * pix = row;
		for (size_t x = 0; x < _width; x++){
			CELL & thePixelCell = _pixelGrid[y*_width+x];
			if (numchannels == 1 || numchannels == 2)
			{
				// monochrome
				uint8_t color = (uint8_t) *pix++;
				thePixelCell.red = color;
				thePixelCell.green = color;
				thePixelCell.blue = color;
				if (numchannels == 2)
					thePixelCell.alpha = (uint8_t) *pix++;
				else
					thePixelCell.alpha = 255;
			} 
			else if (numchannels == 3 || numchannels == 4) 
			{
				thePixelCell.red = (uint8_t) *pix++;
				thePixelCell.green = (uint8_t) *pix++;
				thePixelCell.blue = (uint8_t) *pix++;
				if (numchannels == 4)
					thePixelCell.alpha = (uint8_t) *pix++;
				else
					thePixelCell.alpha = 255;
			}

		}
	}
	delete [] row;
	png_read_end(png_ptr, NULL);
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	fclose(fp);
	return true;


}

bool Image::writeImage(string const& file_image)
{
	/* create file */
	FILE *fp = fopen(file_image.c_str(), "wb");
	if (!fp)
		image_error("[write_png_file] File"+ file_image + "could not be opened for writing");


	/* initialize stuff */
	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if (!png_ptr)
		image_error("[write_png_file] png_create_write_struct failed");

	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
		image_error("[write_png_file] png_create_info_struct failed");

	if (setjmp(png_jmpbuf(png_ptr)))
		image_error("[write_png_file] Error during init_io");

	png_init_io(png_ptr, fp);


	/* write header */
	if (setjmp(png_jmpbuf(png_ptr)))
		image_error("[write_png_file] Error during writing header");

	png_set_IHDR(png_ptr, info_ptr, _width, _height,
		BIT_MAX, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	png_write_info(png_ptr, info_ptr);


// write image
	if (setjmp(png_jmpbuf(png_ptr)))
	{
		image_error("[write_png_file] Error during writing image");
		png_destroy_write_struct(&png_ptr, &info_ptr);
		fclose(fp);
		return false;
	}

	int bytes_per_row = png_get_rowbytes(png_ptr, info_ptr);
	png_byte * row = new png_byte[bytes_per_row];
	for (size_t y = 0; y < _height; y++)
	{
		for (size_t x = 0; x < _width; x++)
		{
			png_byte * pix = &(row[x*4]);

			pix[0] = _pixelGrid[y*_width+x].red;
			pix[1] = _pixelGrid[y*_width+x].green;
			pix[2] = _pixelGrid[y*_width+x].blue;
			pix[3] = _pixelGrid[y*_width+x].alpha;			
		}
		png_write_row(png_ptr, row);
	}
	delete [] row;
	png_write_end(png_ptr, NULL);
	png_destroy_write_struct(&png_ptr, &info_ptr);
	fclose(fp);
	return true;
}

//accessor functions 
size_t Image::getWidth() const
{
	return _width;
}
size_t Image::getHeight() const
{
	return _height;
}
CELL * Image::getGrid() const
{
	return _pixelGrid;
}
void Image::manipulateImage()
{
	int colorGradientCnt[255] = {0};
	long gridSize = getHeight() * getWidth();
	CELL * grid = getGrid();	
	for(long i=0; i <gridSize; i++){
		//CELL * grid = getGrid();
		//grid[i].red = 0;
		int valIndex = (int)grid[i].red;
		colorGradientCnt[valIndex]++;
		grid[i].green = 0;//1.25*grid[i].green;
		grid[i].blue = 0;//1.25*grid[i].blue;
    	grid[i].alpha = 255;//grid[i].alpha;
	}
	cout<<"\ncolorGradientCnt values=\n";
	for(int i =0; i< 255; i++){
		cout<<i<<","<<colorGradientCnt[i]<<endl;
	}
	return;
}

void Image::filter()
{
	long gridSize = getHeight() * getWidth();
	CELL * grid = getGrid();	
	for(long i=0; i <gridSize; i++){
		int redTotal = (int)grid[i].red*(1.20);//+241;
		int greenTotal = (int)grid[i].green*(1.18);//+ 0;
		int blueTotal = (int)grid[i].blue*(1.20);//+30;
		int alphaTotal = (int)grid[i].alpha+0;//+255; 
		// if (redTotal>255){
		// 	redTotal =255;
		// }
		// if (greenTotal>255){
		// 	greenTotal =255;
		// }
		// if (blueTotal>255){
		// 	blueTotal =255;
		// }
		// if (alphaTotal>255){
		// 	alphaTotal =255;
		// }		
		//overflow might be important
		//if grid[i]=					

		grid[i].red = (grid[i].red>=255) ? 255: redTotal;
		grid[i].green = (grid[i].green>=255) ? 255: greenTotal;
		grid[i].blue = (grid[i].blue>=255) ? 255: blueTotal;
    	grid[i].alpha = (alphaTotal==255) ? 255: alphaTotal;		
		// grid[i].red = (grid[i].red>=14) ? 255: redTotal;
		// grid[i].green = (greenTotal==255) ? 255: greenTotal;
		// grid[i].blue = (grid[i].blue>=225) ? 255: blueTotal;
    	// grid[i].alpha = (alphaTotal==255) ? 255: alphaTotal;
	}
	return;
}


// void Image::filter(CELL * diffGrid)
// {
// 	long gridSize = getHeight() * getWidth();
// 	CELL * grid = getGrid();	
// 	for(long i=0; i <gridSize; i++){
// 		grid[i].red += (int)diffGrid[i].red;
// 		grid[i].green +=(int)diffGrid[i].green;
// 		grid[i].blue += (int)diffGrid[i].blue;
// 	    grid[i].alpha +=(int)diffGrid[i].alpha;
// 	}
// 	return;
// }