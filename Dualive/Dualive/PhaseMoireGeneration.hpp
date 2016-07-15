#ifndef PHASEMOIREGENERATION_HPP
#define PHASEMOIREGENERATION_HPP

#include "Phase.hpp"

class PhaseMoireGeneration : public Phase {
private:
	// Radix
	std::vector<int> scrambleIndices(int size) {
		std::vector<std::vector<int>> unsort(size);
		for (int i = 0; i < size; ++i) {
			unsort[rand() % size].push_back(i);
		}

		std::vector<int> randomIndices;
		for (int i = 0; i < unsort.size(); ++i) {
			for (int j = 0; j < unsort[i].size(); ++j) {
				randomIndices.push_back(unsort[i][j]);
			}
		}

		return randomIndices;
	}

	std::vector<Vector2> getPositions() {
		std::string trianglePath(R"(C:\Users\Wax Chug da Gwad\AppData\Local\osu!\Songs\Quarks_Dualive_SDVX_NOFX\Storyboard\Spectrum2D\PatternPiece.png)");
		Vector2 imageSize(Config::I()->GetImageSize(trianglePath));
		Vector2 scaledSize(imageSize * Config::I()->patternScale);
		Vector2 halfScaledSize = scaledSize / 2;
		Vector2 bgSize(854.0f, 480.0f);
		Vector2 halfBgSize = bgSize / 2;

		// Calculate for width
		// Subtract half of the center triangle
		float halfWidth = halfBgSize.x - halfScaledSize.x;
		int numHalfWidth = ceilf(halfWidth / scaledSize.x);
		// Center + Number of triangles for each side
		int numWidth = 1 + 2 * numHalfWidth;

		// Repeat for length
		float halfLength = halfBgSize.y - halfScaledSize.y;
		int numHalfLength = ceilf(halfLength / scaledSize.y);
		int numLength = 1 + 2 * numHalfLength;

		int totalTriangles = numWidth * numLength;
		std::vector<Vector2> positions(totalTriangles);
		Vector2 startPos(Vector2::Midpoint.x - scaledSize.x * numHalfWidth,
			Vector2::Midpoint.y - scaledSize.y * numHalfLength);

		for (int i = 0; i < numLength; ++i) {
			for (int j = 0; j < numWidth; ++j) {
				int index = i * numWidth + j;
				// HACKING bad
				int offset = (i - numLength / 2) * -0.5f;
				Vector2 pos = startPos + Vector2(j * scaledSize.x,
					i * scaledSize.y + offset);
				positions[index] = pos;
			}
		}
		return positions;
	}

	Vector2 switchDirection(Vector2 dir) {
		if (dir == Vector2(1, 0)) {
			return Vector2(0, 1);
		}
		else if (dir == Vector2(0, 1)) {
			return Vector2(-1, 0);
		}
		else if (dir == Vector2(-1, 0)) {
			return Vector2(0, -1);
		}
		else if (dir == Vector2(0, -1)) {
			return Vector2(1, 0);
		}
	}

	void generateTriangles(Time startTime, Time endTime, int frequency, int numTri) {
		for (float i = startTime.ms; i < endTime.ms; i += frequency) {
			for (int j = 0; j < numTri; ++j) {
				if (scrambledIndices.empty()) {
					break;
				}
				Sprite* bgTri = new Sprite(bgTriPath, Vector2::Midpoint, Layer::Background);
				Vector2 pos = positions[scrambledIndices.back()];
				scrambledIndices.pop_back();
				bgTri->Move(i, i + moveOffset, bgTri->position, pos);
				bgTri->Scale(i, i, Config::I()->patternScale, Config::I()->patternScale);

				bgTri->Fade(i, i + moveOffset, 0.0f, 1.0f);
				bgTri->Fade(i + moveOffset, endThirdSpeedup.ms, 1.0f, 1.0f);
				bgTri->Fade(endThirdSpeedup.ms, endSpectrum.ms, 1.0f, 0.0f);
				bgTri->Color(i, endThirdSpeedup.ms, patternColor, patternColor);
				bgTri->Color(endThirdSpeedup.ms, endSpectrum.ms, bgTri->color, Color(255));
			}
		}
	}

	Color patternColor = Color(100);
	std::vector<Vector2> positions = getPositions();
	std::vector<int> scrambledIndices = scrambleIndices(positions.size());
	std::string bgTriPath = "Storyboard\\Spectrum2D\\PatternPiece.png";
	int moveOffset = Config::I()->mspb * 2;
	float bgFade = 0.5f;
	Time startSpectrum = Time("00:03:019");
	Time startSpeedup = Time("00:13:124");
	Time secondSpeedup = Time("00:18:177");
	Time thirdSpeedup = Time("00:20:703");
	Time endThirdSpeedup = Time("00:21:966");
	Time endSpectrum = Time("00:23:229");

public:
	PhaseMoireGeneration() {
		generateTriangles(startSpectrum, startSpeedup, 2 * Config::I()->mspb, 3);
		generateTriangles(startSpeedup, secondSpeedup, 2 * Config::I()->mspb, 9);
		generateTriangles(secondSpeedup, thirdSpeedup, Config::I()->mspb, 81);
		generateTriangles(thirdSpeedup, endThirdSpeedup, Config::I()->mspb / 2, 243);
	}
};
#endif//PHASEMOIREGENERATION_HPP