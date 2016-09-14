#ifndef MAIN_HPP
#define MAIN_HPP

#include "FTOutlineFuncs.hpp"
#include <ft2build.h>
#include <freetype/ftoutln.h>
#include <iostream>
#include FT_FREETYPE_H

// Apparently static main() function is bad so we're going to here
class Main {
public:
	Main() {
		FT_Library library;
		FT_Face face;
		FT_Init_FreeType(&library);
		FT_New_Face(library, R"(C:\Users\Wax Chug da Gwad\Documents\Fonts\Aroly\AROLY.ttf)", 0, &face);
		FT_Set_Char_Size(face, 0, 16 * 64, 96, 96);

		// Glyph indices reference:
		// 'A' = 25
		// 'Z' = 50
		int charcode = 25;
		FT_UInt glyph_index = FT_Get_Char_Index(face, 'A');
		FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
		FT_Outline outline = face->glyph->outline;

		// o_o
	    // https://repository.unm.edu/bitstream/handle/1928/23168/jeff_bowles_font_rendering.pdf?sequence=1
	    // http://svn.openscenegraph.org/osg/OpenSceneGraph/branches/OpenSceneGraph-2.6/src/osgPlugins/freetype/FreeTypeFont3D.cpp
		FT_Outline_Funcs outlineFuncs;
		outlineFuncs.move_to = &moveTo;
		outlineFuncs.line_to = &lineTo;
		outlineFuncs.conic_to = &conicTo;
		outlineFuncs.cubic_to = &cubicTo;
		outlineFuncs.shift = 0;
		outlineFuncs.delta = 0;

		FT_Outline_Decompose(&outline, &outlineFuncs, this);

	}
};

#endif//MAIN_HPP