#ifndef PHASEMOIREGENERATION_HPP
#define PHASEMOIREGENERATION_HPP

#include "Config.hpp"

class PhaseMoireGeneration {
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

		// Ran into some offset problems that I dealt with
		// (to a good enough degree) with flooring

		// Weirdly enough it's only on the y, maybe it's a discrepancy
		// between how my utility handles the file and how the GetImageSize
		// function handles it
		scaledSize.y = floorf(scaledSize.y);

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
		Vector2 startPos(-scaledSize.x * numHalfWidth,
			-scaledSize.y * numHalfLength);

		for (int i = 0; i < numLength; ++i) {
			for (int j = 0; j < numWidth; ++j) {
				int index = i * numWidth + j;
				Vector2 pos = startPos + Vector2(j * scaledSize.x,
					i * scaledSize.y);
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

	void generateTriangles(std::vector<Sprite*>& triangles, Time startTime, Time endTime, int frequency, int numTri) {
		for (float i = startTime.ms; i < endTime.ms; i += frequency) {
			for (int j = 0; j < numTri; ++j) {
				if (scrambledIndices.empty()) {
					return;
				}
				Sprite* bgTri = new Sprite(bgTriPath, Vector2::Zero, Layer::Background);
				Vector2 pos = positions[scrambledIndices.back()];
				scrambledIndices.pop_back();
				bgTri->Move(i, i + moveOffset, bgTri->position, pos);
				bgTri->Scale(i, i, Config::I()->patternScale, Config::I()->patternScale);
				bgTri->Fade(i, i + moveOffset, 0.0f, 1.0f);
				bgTri->Fade(i + moveOffset, endThirdSpeedup.ms, 1.0f, 1.0f);
				bgTri->Fade(endSpectrum.ms - Config::I()->offset, endSpectrum.ms, 1.0f, 0.0f);
				bgTri->Color(i, endThirdSpeedup.ms, patternColor, patternColor);
				bgTri->Color(endThirdSpeedup.ms, endSpectrum.ms, bgTri->color, Color(255));

				// Reappear and drop off
				bgTri->Fade(endSpin.ms, startTunnel.ms, 0.0f, 1.0f);
				bgTri->Color(endSpin.ms, startTunnel.ms, Color(25), Color(25));
				triangles.push_back(bgTri);
			}
		}
	}

	void degenerateTriangles(std::vector<Sprite*>& triangles, Time startTime, Time endTime, int frequency, int numTri) {
		for (float i = startTime.ms; i < endTime.ms; i += frequency) {
			for (int j = 0; j < numTri; ++j) {
				if (triangles.size() == trianglesRemaining) {
					return;
				}

				// Get last
				Sprite* tri = triangles.back();
				tri->Fade(i, i + Config::I()->offset * 4, 1.0f, 0.0f);
				// Pop back
				triangles.pop_back();
			}
		}
	}

	void placeTriangles(std::vector<Sprite*>& triangles, Time startTime, Time endTime) {
		float spacing = 100.0f;
		int timeDiff = endTime.ms - startTime.ms;
		for (int i = 0; i < triangles.size(); ++i) {
			Vector2 up = Vector2(0, 1) * spacing;
			float rot = 2 * M_PI * ((float)i / triangles.size());
			Vector2 pos = up.Rotate(rot);
			triangles[i]->Move(startTime.ms, endTime.ms, triangles[i]->position, pos);
			triangles[i]->Rotate(startTime.ms, endTime.ms, triangles[i]->rotation, rot);
			Vector2 scaleVector = triangles[i]->scaleVector;
			scaleVector.y = 0.02f;
			triangles[i]->ScaleVector(startTime.ms, endTime.ms, triangles[i]->scaleVector, scaleVector);
			triangles[i]->Fade(startTime.ms, endTime.ms, triangles[i]->fade, 1.0f);
			triangles[i]->Color(startTime.ms, endTime.ms, triangles[i]->color, Color(255.0f));
		}
	}

	int calcNumTri(Time startTetEnd, Time endScale, float frequency, int remainingTriangles) {
		int timeRemaining = endScale.ms - startTetEnd.ms;
		float divisions = timeRemaining / frequency;
		return ceilf(remainingTriangles / divisions);
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
	Time endSpin = Time("00:42:177");
	Time startTunnel = Time("00:43:440");
	Time startTet = Time("01:03:650");
	Time startTetSpeedup = Time("01:13:756");
	Time startTetEnd = Time("01:21:335");
	Time endScale = Time("01:22:598");
	Time startPlace = Time("01:22:598");
	Time endTet = Time("01:23:861");
	int trianglesRemaining = 24;

public:
	PhaseMoireGeneration() {
		std::vector<Sprite*> triangles;
		generateTriangles(triangles, startSpectrum, startSpeedup, 2 * Config::I()->mspb, 3);
		generateTriangles(triangles, startSpeedup, secondSpeedup, 2 * Config::I()->mspb, 9);
		generateTriangles(triangles, secondSpeedup, thirdSpeedup, Config::I()->mspb, 81);

		int numGenTri = calcNumTri(thirdSpeedup, endThirdSpeedup, Config::I()->mspb / 2, scrambledIndices.size());
		generateTriangles(triangles, thirdSpeedup, endThirdSpeedup, Config::I()->mspb / 2, numGenTri);

		degenerateTriangles(triangles, startTet, startTetSpeedup, 2 * Config::I()->mspb, 18);
		degenerateTriangles(triangles, startTetSpeedup, startTetEnd, Config::I()->mspb, 27);

		int numDegenTri = calcNumTri(startTetEnd, endScale, Config::I()->mspb / 2, triangles.size());
		degenerateTriangles(triangles, startTetEnd, endScale, Config::I()->mspb / 2, numDegenTri);

		placeTriangles(triangles, startPlace, endTet);
	}
};
#endif//PHASEMOIREGENERATION_HPP