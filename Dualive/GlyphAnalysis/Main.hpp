#ifndef MAIN_HPP
#define MAIN_HPP

#include "DecomposedValue.hpp"
#include "FTOutlineFuncs.hpp"
#include <ft2build.h>
#include <freetype/ftoutln.h>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include FT_FREETYPE_H

// Apparently static main() function is bad so we're going to here
class Main {
public:
	Main() {
		FT_Library library;
		FT_Face face;
		initialize(library, face);

		std::vector<DecomposedOutline> decomposedOutlines = decompose(face);
		std::string path(R"(C:\Users\Wax Chug da Gwad\Desktop\Dualive\Dualive\Debug\GlyphOutlineData.txt)");
		saveContours(decomposedOutlines, path);
	}
private:
	void initialize(FT_Library& library, FT_Face& face) {
		FT_Init_FreeType(&library);
		FT_New_Face(library, R"(C:\Users\Wax Chug da Gwad\Documents\Fonts\Aroly\AROLY.ttf)", 0, &face);
		FT_Set_Char_Size(face, 0, 16 * 64, 96, 96);
	}

	std::vector<DecomposedOutline> decompose(FT_Face& face) {
		// To find the glyph index mapped to the correct character code, use this conversion:
		// glyph_index = FT_Get_Char_Index( face, charcode );
		// I'm not using the above method because I'm just looking up the indices directly through http://opentype.js.org/glyph-inspector.html

		// Hardcoded glyph indices reference:
		// 'A' = 25
		// 'Z' = 50
		// May need additional for !, ?, numeric, etc.
		int startGlyphIndex = 25;
		int endGlyphIndex = 50;
		std::vector<DecomposedOutline> decomposedOutlines;

		for (int i = startGlyphIndex; i <= endGlyphIndex; ++i) {
			FT_Load_Glyph(face, i, FT_LOAD_DEFAULT);
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

			DecomposedOutline contours;
			FT_Outline_Decompose(&outline, &outlineFuncs, &contours);
			decomposedOutlines.push_back(contours);
		}
		return decomposedOutlines;
	}

	void saveContours(std::vector<DecomposedOutline>& decomposedOutlines, std::string& path) {
		std::ofstream file(path);
		file << decomposedOutlines.size() << std::endl;
		for (auto decomposedOutline : decomposedOutlines) {
			file << decomposedOutline.size() << std::endl;
			for (auto contour : decomposedOutline) {
				file << contour.size() << std::endl;
				for (auto decomposedValue : contour) {
					file << decomposedValue.type << " " << decomposedValue.point.x << " " << decomposedValue.point.y << std::endl;
				}
			}
		}
	}
};

#endif//MAIN_HPP