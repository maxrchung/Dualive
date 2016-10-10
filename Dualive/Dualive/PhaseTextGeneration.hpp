#ifndef PHASETEXTGENERATION_HPP
#define PHASETEXTGENERATION_HPP

#include "Config.hpp"
#include "LetterGroup.hpp"

class PhaseTextGeneration {
public:
	PhaseTextGeneration() {
		std::string glyphDataPath = R"(C:\Users\Wax Chug da Gwad\Desktop\Dualive\Dualive\Debug\GlyphOutlineData.txt)";
		std::vector<VectorMap> outlines = loadOutlinesData(glyphDataPath);

		std::vector<Letter> letters;
		for (auto& vectorMap : outlines) {
			letters.push_back(Letter(vectorMap));
		}

		for (int i = 0; i < lyrics.size(); ++i) {
			LetterGroup letterGroup(letters, lyrics[i]);

			int startDisplay = timings[i].ms;

			if (i < lyrics.size() - 1) {
				int endDisplay = timings[i + 1].ms - Config::I()->mspb / 2;
				LetterGroup::display(letterGroup, startDisplay, endDisplay);
			}
			else {
				int dualiveEnding = Time("02:06:808").ms;
				LetterGroup::display(letterGroup, startDisplay, dualiveEnding);
			}
		}
	}

private:
	std::vector<std::string> lyrics = std::vector<std::string>({
		"LET YOU",
		"DIVE AWAY",
		"FROM OUR",
		"PAINFUL DAYS",
		"USO DARAKE",
		"NO SABITA",
		"HIBI WO",
		"UGATTE",
		"GET YOUR",
		"HIDDEN WAY",
		"FROM OUR",
		"FLAWLESS MAZE",
		"SAGASU",
		"WO",
		"O",
		"O",
		"O",
		"O",
		"O",
		"WE'RE",
		"BREATHING",
		"IN",
		"DUALIVE"
	});

	std::vector<Time> timings = std::vector<Time>({
		Time("01:43:440"), //"LET YOU"
		Time("01:44:071"), //"DIVE AWAY",
		Time("01:45:966"), //"FROM OUR",
		Time("01:46:598"), //"PAINFUL DAYS",
		Time("01:48:493"), //"USO DARAKE",
		Time("01:49:756"), //"NO SABITA",
		Time("01:51:335"), //"HIBI WO",
		Time("01:52:598"), //"UGATTE",
		Time("01:53:545"), //"GET YOUR",
		Time("01:54:177"), //"HIDDEN WAY",
		Time("01:56:071"), //"FROM OUR",
		Time("01:56:703"), //"FLAWLESS MAZE",
		Time("01:58:598"), //"SAGASU",
		Time("02:00:177"), //"WO",
		Time("02:00:493"), //"O",
		Time("02:00:808"), //"O",
		Time("02:01:124"), //"O",
		Time("02:01:440"), //"O",
		Time("02:01:756"), //"O",
		Time("02:02:703"), //"WE'RE",
		Time("02:03:019"), //"BREATHING",
		Time("02:03:335"), //"IN",
		Time("02:03:650"), //"DUALIVE"
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