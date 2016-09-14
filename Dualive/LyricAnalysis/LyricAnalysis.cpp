#include "PNGContainer.hpp"
#include <string>

// This project was an attempt at doing image analysis of
// the lyric images in order to get line and point values for
// the last section of the storyboard. After doing some tinkering
// and thinking though, I'm pretty sure this method would be a lot
// harder than I first imagined. As such, I'm going to close this
// small project for now and move onto another method: directly 
// analyzing font glyphs. Regardless, I think I'll still keep this 
// project around as a keepsake and basic code for PNG manipulation.

void abort_(const char * s, ...)
{
	va_list args;
	va_start(args, s);
	vfprintf(stderr, s, args);
	fprintf(stderr, "\n");
	va_end(args);
	abort();
}

void readInfo(PNGContainer& pc)
{
	/* open file and test for it being a png */
	FILE *fp = fopen(pc.file_name, "rb");
	if (!fp)
		abort_("[read_png_file] File %s could not be opened for reading", pc.file_name);
	fread(pc.header, 1, 8, fp);
	if (png_sig_cmp((png_const_bytep)pc.header, 0, 8))
		abort_("[read_png_file] File %s is not recognized as a PNG file", pc.file_name);


	/* initialize stuff */
	pc.png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if (!pc.png_ptr)
		abort_("[read_png_file] png_create_read_struct failed");

	pc.info_ptr = png_create_info_struct(pc.png_ptr);
	if (!pc.info_ptr)
		abort_("[read_png_file] png_create_info_struct failed");

	if (setjmp(png_jmpbuf(pc.png_ptr)))
		abort_("[read_png_file] Error during init_io");

	png_init_io(pc.png_ptr, fp);
	png_set_sig_bytes(pc.png_ptr, 8);

	png_read_info(pc.png_ptr, pc.info_ptr);

	pc.width = png_get_image_width(pc.png_ptr, pc.info_ptr);
	pc.height = png_get_image_height(pc.png_ptr, pc.info_ptr);
	pc.color_type = png_get_color_type(pc.png_ptr, pc.info_ptr);
	pc.bit_depth = png_get_bit_depth(pc.png_ptr, pc.info_ptr);

	pc.number_of_passes = png_set_interlace_handling(pc.png_ptr);
	png_read_update_info(pc.png_ptr, pc.info_ptr);


	/* read file */
	if (setjmp(png_jmpbuf(pc.png_ptr)))
		abort_("[read_png_file] Error during read_image");

	pc.row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * pc.height);
	for (int y = 0; y<pc.height; y++)
		pc.row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(pc.png_ptr, pc.info_ptr));

	png_read_image(pc.png_ptr, pc.row_pointers);

	fclose(fp);
}

void makeGrid(PNGContainer& pc)
{
	if (png_get_color_type(pc.png_ptr, pc.info_ptr) == PNG_COLOR_TYPE_RGB)
		abort_("[process_file] input file is PNG_COLOR_TYPE_RGB but must be PNG_COLOR_TYPE_RGBA "
		"(lacks the alpha channel)");

	if (png_get_color_type(pc.png_ptr, pc.info_ptr) != PNG_COLOR_TYPE_RGBA)
		abort_("[process_file] color_type of input file must be PNG_COLOR_TYPE_RGBA (%d) (is %d)",
		PNG_COLOR_TYPE_RGBA, png_get_color_type(pc.png_ptr, pc.info_ptr));

	pc.grid = std::vector<std::vector<int>>(pc.width, std::vector<int>(pc.height));

	for (int y = 0; y<pc.height; y++) {
		png_byte* row = pc.row_pointers[y];
		for (int x = 0; x<pc.width; x++) {
			png_byte* ptr = &(row[x * 4]);
			printf("Pixel at position [ %d - %d ] has RGBA values: %d - %d - %d - %d\n",
				x, y, ptr[0], ptr[1], ptr[2], ptr[3]);

			pc.grid[x][y] = ptr[3];
		}
	}
}

void processGrid(PNGContainer& pc) {

}

void processPNG(std::string& fileName) {
	PNGContainer pngContainer = PNGContainer(fileName.c_str());
	readInfo(pngContainer);
	makeGrid(pngContainer);
	processGrid(pngContainer);
}

void main() {
	int i = 0;
	std::string projectDir = R"(C:\Users\Wax Chug da Gwad\AppData\Local\osu!\Songs\Quarks_Dualive_SDVX_NOFX\Storyboard\LyricsTunnel\)";
	std::string fileName = projectDir + std::to_string(i) + ".png";
	processPNG(fileName);
}