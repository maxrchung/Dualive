#ifndef PHASETEXTGENERATION_HPP
#define PHASETEXTGENERATION_HPP

#include "Config.hpp"

class PhaseTextGeneration {
	typedef std::pair<Vector2, Vector2> Pair;

public:
	PhaseTextGeneration() {
		std::string glyphDataPath = R"(C:\Users\Wax Chug da Gwad\Desktop\Dualive\Dualive\Debug\GlyphOutlineData.txt)";
		std::string linePath(R"(C:\Users\Wax Chug da Gwad\AppData\Local\osu!\Songs\Quarks_Dualive_SDVX_NOFX\Storyboard\3D\line.png)");
		std::vector<std::vector<Pair>> outlines = loadOutlinesData(glyphDataPath);

		int totalTime = Config::I()->songEnd.ms - Config::I()->songStart.ms;
		float glyphTime = (float)totalTime / outlines.size();

		float lineScaleHeight = 0.1f;
		float width = max.x + min.x;
		float height = max.y + min.y;
		float halfWidth = width / 2;
		float halfHeight = height / 2;

		for (int i = 0; i < outlines.size(); ++i) {
			Color color(rand() % 200 + 55, rand() % 200 + 55, rand() % 200 + 55);
			for (auto pair : outlines[i]) {
				Vector2 distanceVector = pair.second - pair.first;
				float lineLength = distanceVector.Magnitude();
				float lineScaleWidth = lineLength / 1000;
				Vector2 lineScale(lineScaleWidth, lineScaleHeight);
				float rotation = Vector2(1, 0).AngleBetween(distanceVector);

				Sprite* line = new Sprite(linePath, Vector2::Zero, Layer::Foreground, Origin::CentreLeft);

				int startTime = i * glyphTime;
				int endTime = startTime + glyphTime;
				line->ScaleVector(startTime, endTime, lineScale, lineScale);
				line->Rotate(startTime, endTime, rotation, rotation);

				Vector2 linePos = pair.first - Vector2(halfWidth, halfHeight);
				line->Move(startTime, endTime, linePos, linePos);
				line->Color(startTime, endTime, color, color);
			}
		}
	}

private:
	Vector2 max = Vector2(FLT_MIN, FLT_MIN);
	Vector2 min = Vector2(FLT_MAX, FLT_MAX);

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

	std::vector<std::vector<Pair>> loadOutlinesData(std::string& path) {
		float pointScale = 0.3f;
		std::ifstream file(path);

		std::vector<std::vector<Pair>> outlines;
		int numOutlines;
		file >> numOutlines;

		std::vector<Pair> pairs;
		for (int j = 0; j < numOutlines; ++j) {
			int numPairs;
			file >> numPairs;

			for (int k = 0; k < numPairs; ++k) {
				int type, x, y, x2, y2;
				file >> type >> x >> y >> x2 >> y2;
				Vector2 first = Vector2(x, y) * pointScale;
				Vector2 second = Vector2(x2, y2) * pointScale;
				Pair pair(first, second);
				pairs.push_back(pair);

				if (x < min.x)
					min.x = x;
				else if (x > max.x)
					max.x = x;
				if (x2 < min.x)
					min.x = x2;
				else if (x2 > max.x)
					max.x = x2;

				if (y < min.y)
					min.y = y;
				else if (y > max.y)
					max.y = y;
				if (y2 < min.y)
					min.y = y2;
				else if (y2 > max.y)
					max.y = y2;
			}
		}
		outlines.push_back(pairs);
		return outlines;
	}
};

#endif//PHASETEXTGENERATION_HPP