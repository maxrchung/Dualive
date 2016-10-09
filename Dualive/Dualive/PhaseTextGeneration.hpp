#ifndef PHASETEXTGENERATION_HPP
#define PHASETEXTGENERATION_HPP

#include "Config.hpp"
#include "Letter.hpp"

class PhaseTextGeneration {
public:
	PhaseTextGeneration() {
		std::string glyphDataPath = R"(C:\Users\Wax Chug da Gwad\Desktop\Dualive\Dualive\Debug\GlyphOutlineData.txt)";
		std::vector<VectorMap> outlines = loadOutlinesData(glyphDataPath);
		std::vector<Letter*> letters;

		for (auto& vectorMap : outlines) {
			letters.push_back(new Letter(vectorMap));
		}
		
	}

private:
	std::vector<std::string> lyrics = std::vector<std::string>({
		"LET YOU DIVE AWAY",
		"FROM OUR PAINFUL DAYS",
		"USO DARAKE",
		"NO SABITA",
		"HIBI WO",
		"UGATTE",
		"GET YOUR HIDDEN WAY",
		"FROM OUR FLAWLESS MAZE",
		"SAGASU",
		"WO",
		"O",
		"O",
		"O",
		"O",
		"O",
		"WE'RE BREATHING IN DUALIVE"
	});

	std::vector<VectorMap> loadOutlinesData(std::string& path) {
		float pointScale = 0.3f;
		std::ifstream file(path);
		
		std::vector<VectorMap> outlines;
		int numOutlines;
		file >> numOutlines;

		for (int j = 0; j < numOutlines; ++j) {
			VectorMap vectorMap;
			int numPockets;
			file >> numPockets;

			for (int k = 0; k < numPockets; ++k) {
				float pocketX, pocketY;
				file >> pocketX >> pocketY;
				Vector2 pocketVector = Vector2(pocketX, pocketY) * pointScale;

				std::unordered_set<Vector2> points;
				int numPoints;
				file >> numPoints;

				for (int l = 0; l < numPoints; ++l) {
					float pointX, pointY;
					file >> pointX >> pointY;
					Vector2 point = Vector2(pointX, pointY) * pointScale;
					points.insert(point);
				}

				vectorMap.insert({ pocketVector, points });
			}

			outlines.push_back(vectorMap);
		}

		return outlines;
	}
};

#endif//PHASETEXTGENERATION_HPP