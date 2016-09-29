#ifndef MAIN_HPP
#define MAIN_HPP

#include "DecomposedValue.hpp"
#include "FTOutlineFuncs.hpp"
#include "Node.hpp"
#include "Pocket.hpp"
#include "Vector2.hpp"
#include <ft2build.h>
#include <freetype/ftoutln.h>
#include <fstream>
#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>
#include FT_FREETYPE_H

// Apparently static main() function is bad so we're going to here
class Main {
	typedef std::pair<Vector2, Vector2> Pair;

public:
	Main() {
		FT_Library library;
		FT_Face face;
		initialize(library, face);

		std::vector<DecomposedOutline> decomposed = decompose(face);
		std::vector<std::vector<Pair>> reduced = reduce(decomposed);
		std::unordered_set<Pocket*> localized = localize(reduced);

		std::string path(R"(C:\Users\Wax Chug da Gwad\Desktop\Dualive\Dualive\Debug\GlyphOutlineData.txt)");
		save(reduced, path);
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
		// A = 25
		// Z = 50
		// R = 42
		// Y = 49
		// May need additional for !, ?, numeric, etc.
		int startGlyphIndex = 25;
		int endGlyphIndex = 25;
		std::vector<DecomposedOutline> decomposedOutlines;

		for (int i = startGlyphIndex; i <= endGlyphIndex; ++i) {
			FT_Load_Glyph(face, i, FT_LOAD_NO_HINTING);
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

			if (i == 49) {
				// Outer border
				contours.pop_front();
			}

			if (i == 42) {
				// Inner border outlining the center section of R
				contours.erase(contours.begin() + 17);
				// Outer border
				contours.pop_front();
			}

			decomposedOutlines.push_back(contours);
		}
		return decomposedOutlines;
	}

	std::vector<std::vector<Pair>> reduce(std::vector<DecomposedOutline>& outlines) {
		std::vector<std::vector<Pair>> reduced;
		for (int i = 0; i < outlines.size(); ++i) {
			std::vector<Pair> pointPairs;
			for (auto contour : outlines[i]) {
				// Get Vector2 line pairs
				std::vector<Pair> linePairs = getLinePairs(contour);

				// R index or Y index, find the largest 3
				if (i == 42 - 25 || i == 49 - 25) {
					std::vector<Pair> maxPairs = getLargestThree(linePairs);
					for (auto linePair : maxPairs) {
						pointPairs.push_back(linePair);
					}
				}

				// Find line with largest distance
				else {
					pointPairs.push_back(getMaxPair(linePairs));
				}
			}
			reduced.push_back(pointPairs);
		}
		return reduced;
	}

	std::vector<Pair> getLinePairs(std::vector<DecomposedValue>& contour) {
		std::vector<Pair> linePoints;
		Vector2 prevPoint = Vector2(contour[0].point.x, contour[0].point.y);
		for (int j = 1; j < contour.size(); ++j) {
			Vector2 curPoint = Vector2(contour[j].point.x, contour[j].point.y);
			linePoints.push_back(Pair(prevPoint, curPoint));
			prevPoint = curPoint;
		}
		return linePoints;
	}

	std::vector<Pair> getLargestThree(std::vector<Pair>& linePairs) {
		// If there's only 3, then return that (most cases will be this)
		if (linePairs.size() == 3) {
			return linePairs;
		}

		// Else find largest 4
		// Turns out finding max of 3 gives some finnicky results (blame the font maker not me)
		// What happens is that a lot of outlines are left incomplete without a full sided edge
		std::list<Pair> maxList;
		for (auto linePair : linePairs) {
			float magnitude = (linePair.first - linePair.second).Magnitude();

			bool skipCheck = false;
			// Iterate through list, compare distance, add if larger
			for (auto j = maxList.begin(); j != maxList.end(); ++j) {
				skipCheck = false;
				float compareMagnitude = (j->first - j->second).Magnitude();
				if (magnitude > compareMagnitude) {
					maxList.insert(j, linePair);
					skipCheck = true;
					break;
				}
			}

			// Handle extra back
			if (maxList.size() > 4) {
				maxList.pop_back();
			}

			if (!skipCheck) {
				// Handle less than 4
				if (maxList.size() < 4) {
					maxList.push_back(linePair);
				}
			}
		}

		std::vector<Pair> pointPairs;
		for (auto a : maxList) {
			pointPairs.push_back(a);
		}
		return pointPairs;
	}

	Pair getMaxPair(std::vector<Pair>& linePairs) {
		Pair maxPair(linePairs[0]);
		float maxDistance = (maxPair.second - maxPair.first).Magnitude();
		for (int j = 1; j < linePairs.size(); ++j) {
			float curDistance = (linePairs[j].second - linePairs[j].first).Magnitude();
			if (curDistance > maxDistance) {
				maxPair.first = linePairs[j].first;
				maxPair.second = linePairs[j].second;
				maxDistance = curDistance;
			}
		}
		return maxPair;
	}

	std::unordered_set<Pocket*> localize(std::vector<std::vector<Pair>>& reduced) {
		std::unordered_set<Pocket*> pockets;
		for (auto& outline : reduced) {
			for (auto pair : outline) {
				Pocket::AddPockets(pockets, pair);
			}
		}

		for (auto pocket : pockets) {
			Pocket::CalculateAverage(pocket);
		}

		return pockets;
	}

	void save(std::vector<std::vector<Pair>>& located, std::string& path) {
		std::ofstream file(path);
		file << located.size() << std::endl;
		for (auto pairs : located) {
			file << pairs.size() << std::endl;
			for (auto pair : pairs) {
				file << (int)pair.first.x << " " << (int)pair.first.y << " " << (int)pair.second.x << " " << (int)pair.second.y << std::endl;
			}
		}
	}
};


#endif//MAIN_HPP