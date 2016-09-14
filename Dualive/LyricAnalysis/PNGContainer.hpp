#ifndef PNGCONTAINER_HPP
#define PNGCONTAINER_HPP

#include "png.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <vector>

class PNGContainer {
public:
	PNGContainer(const char* file_name)
		: file_name(file_name) {}

	int width, height;
	png_byte color_type;
	png_byte bit_depth;
	png_structp png_ptr;
	png_infop info_ptr;
	int number_of_passes;
	png_bytep* row_pointers;
	char header[8];    // 8 is the maximum size that can be checked
	const char* file_name;
	std::vector<std::vector<int>> grid;
};

#endif//PNGCONTAINER_HPP