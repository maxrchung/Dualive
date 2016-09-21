#ifndef PHASETEXTGENERATION_HPP
#define PHASETEXTGENERATION_HPP

#include "Config.hpp"
#include "DecomposedValue.hpp"

class PhaseTextGeneration {
public:
	PhaseTextGeneration() {
		std::string glyphDataPath = R"(C:\Users\Wax Chug da Gwad\Desktop\Dualive\Dualive\Debug\GlyphOutlineData.txt)";
		std::string linePath(R"(C:\Users\Wax Chug da Gwad\AppData\Local\osu!\Songs\Quarks_Dualive_SDVX_NOFX\Storyboard\3D\line.png)");
		std::vector<std::vector<std::vector<Vector2>>> glyphs = loadGlyphData(glyphDataPath);

		int totalTime = Config::I()->songEnd.ms - Config::I()->songStart.ms;
		float glyphTime = (float)totalTime / glyphs.size();

		float lineScaleHeight = 0.1f;
		float width = max.x + min.x;
		float height = max.y + min.y;
		float halfWidth = width / 2;
		float halfHeight = height / 2;

		for (int i = 0; i < glyphs.size(); ++i) {
			for (auto contour : glyphs[i]) {
				Vector2 prevPoint = contour[0];
				Color color(rand() % 200 + 55, rand() % 200 + 55, rand() % 200 + 55);
				for (int j = 1; j < contour.size(); ++j) {
					Vector2 distance = contour[j] - prevPoint;
					float lineLength = distance.Magnitude();
					float lineScaleWidth = lineLength / 1000;
					Vector2 lineScale(lineScaleWidth, lineScaleHeight);
					float rotation = Vector2(1, 0).AngleBetween(distance);

					Sprite* line = new Sprite(linePath, Vector2::Zero, Layer::Foreground, Origin::CentreLeft);

					int startTime = i * glyphTime;
					int endTime = startTime + glyphTime;
					line->ScaleVector(startTime, endTime, lineScale, lineScale);
					line->Rotate(startTime, endTime, rotation, rotation);

					Vector2 linePos = prevPoint - Vector2(halfWidth, halfHeight);
					line->Move(startTime, endTime, linePos, linePos);
					line->Color(startTime, endTime, color, color);
				}
			}
		}
	}

private:
	Vector2 max = Vector2(FLT_MIN, FLT_MIN);
	Vector2 min = Vector2(FLT_MAX, FLT_MAX);

	// Points:				Vector2
	// Contours:			vector<Points>
	// Glyph Outlines:		vector<Contours>
	// Glyph collection:	vector<Glyph Outlines>
	std::vector<std::vector<std::vector<Vector2>>> loadGlyphData(std::string& path) {
		float pointScale = 0.4f;

		std::vector<std::vector<std::vector<Vector2>>> glyphs;

		std::ifstream file(path);
		int numGlyphs;
		file >> numGlyphs;

		for (int i = 0; i < numGlyphs; ++i) {
			int numOutlines;
			file >> numOutlines;

			std::vector<std::vector<Vector2>> contours;
			for (int j = 0; j < numOutlines; ++j) {
				int numContours;
				file >> numContours;

				std::vector<Vector2> points;
				for (int k = 0; k < numContours; ++k) {
					int type, x, y;
					file >> type >> x >> y;
					Vector2 value = Vector2(x, y) * pointScale;
					points.push_back(value);

					if (value.x < min.x) {
						min.x = value.x;
					}
					else if (value.x > max.x) {
						max.x = value.x;
					}
					if (value.y < min.y) {
						min.y = value.y;
					}
					else if (value.y > max.y) {
						max.y = value.y;
					}
				}
				contours.push_back(points);
			}
			glyphs.push_back(contours);
		}

		return glyphs;
	}
};

#endif//PHASETEXTGENERATION_HPP