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
				// Using larger image path so there is less blurriness in image when scaling down
				Sprite* bgTri = new Sprite(bgTriLargePath, Vector2::Zero, Layer::Background);
				Vector2 pos = positions[scrambledIndices.back()];
				scrambledIndices.pop_back();
				bgTri->Move(i, i + moveOffset, bgTri->position, pos);
				bgTri->Rotate(i, i + moveOffset, bgTri->rotation, M_PI * 2, Easing::CubicIn);
				bgTri->Scale(i, i, Config::I()->patternScale / 2, Config::I()->patternScale / 2);
				bgTri->Fade(i, i + moveOffset, 0.0f, 1.0f, Easing::CubicIn);
				bgTri->Fade(i + moveOffset, endThirdSpeedup.ms, 1.0f, 1.0f);
				bgTri->Fade(Time("00:21:966").ms, Time("00:21:966").ms, 0.0f, 0.0f);

				if (i < startSpeedup.ms)
					bgTri->Color(0, 0, GetColor[GC::PINK], GetColor[GC::PINK]);
				if (i < Time("00:15:650").ms)
					bgTri->Color(startSpeedup.ms - Config::I()->mspb, startSpeedup.ms, GetColor[GC::PINK], GetColor[GC::ORANGE], Easing::CubicIn);
				if (i < secondSpeedup.ms)
					bgTri->Color(Time("00:15:650").ms - Config::I()->mspb, Time("00:15:650").ms, GetColor[GC::ORANGE], GetColor[GC::NAVY], Easing::CubicIn);
				if (i < thirdSpeedup.ms)
					Config::I()->SwitchSpriteColor(bgTri, secondSpeedup.ms, thirdSpeedup.ms, GetColor[GC::GREEN], GetColor[GC::BLUE], Config::I()->mspb, Config::I()->mspb);
				Config::I()->SwitchSpriteColor(bgTri, thirdSpeedup.ms, Time("00:21:966").ms, GetColor[GC::YELLOW], GetColor[GC::PURPLE], Config::I()->mspb / 4, Config::I()->mspb / 4);

				// Reappear and drop off
				bgTri->Fade(Time("01:03:650").ms, Time("01:03:650").ms, 0.0f, 1.0f);
				bgTri->Color(endSpin.ms, startTunnel.ms, GetColor[GC::WARNING], GetColor[GC::WARNING]);

				// Tet spin
				bgTri->Color(Time("01:06:177").ms - Config::I()->mspb, Time("01:06:177").ms, bgTri->color, GetColor[GC::BABYGREEN]);
				bgTri->Color(Time("01:08:703").ms - Config::I()->mspb, Time("01:08:703").ms, bgTri->color, GetColor[GC::STEELBLUE]);
				bgTri->Color(Time("01:09:966").ms - Config::I()->mspb, Time("01:09:966").ms, bgTri->color, GetColor[GC::COUPLEMONTHSWORNBASKETBALLORANGE]);
				bgTri->Color(Time("01:11:229").ms - Config::I()->mspb, Time("01:11:229").ms, bgTri->color, GetColor[GC::ALIENWARE]);
				bgTri->Color(Time("01:12:493").ms - Config::I()->mspb, Time("01:12:493").ms, bgTri->color, GetColor[GC::GOLDENGATERED]);
				Config::I()->SwitchSpriteColor(bgTri, Time("01:13:756").ms, Time("01:15:019").ms, GetColor[GC::SANDPAPER], GetColor[GC::BRUISE], Config::I()->mspb / 2, Config::I()->mspb / 2);
				Config::I()->SwitchSpriteColor(bgTri, Time("01:16:282").ms, Time("01:17:545").ms, GetColor[GC::MOSSYAQUARIUM], GetColor[GC::SUICIDEAD], Config::I()->mspb / 2, Config::I()->mspb / 2);
				Config::I()->SwitchSpriteColor(bgTri, Time("01:18:808").ms, Time("01:20:071").ms, GetColor[GC::SADNESS], GetColor[GC::HAPPYNESS], Config::I()->mspb, Config::I()->mspb);
				Config::I()->SwitchSpriteColor(bgTri, Time("01:20:229").ms, Time("01:21:335").ms, GetColor[GC::HAPPYNESS], GetColor[GC::SADNESS], Config::I()->mspb / 2, Config::I()->mspb / 2);
				Config::I()->SwitchSpriteColor(bgTri, Time("01:21:414").ms, Time("01:22:598").ms, GetColor[GC::HAPPYNESS], GetColor[GC::SADNESS], Config::I()->mspb / 4, Config::I()->mspb / 4);

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
				tri->Fade(i, i + Config::I()->mspb * 4, 1.0f, 0.0f, Easing::CubicIn);
				tri->Rotate(i, i + Config::I()->mspb * 4, tri->rotation, tri->rotation + 4 * M_PI, Easing::CubicIn);
				tri->Scale(i, i + Config::I()->mspb * 4, tri->scale, 0.0f, Easing::CubicIn);
				tri->Move(i, i + Config::I()->mspb * 4, tri->position, tri->position + Vector2(0, -1000), Easing::CubicIn);

				// Pop back
				triangles.pop_back();
			}
		}
	}

	void placeTriangles(std::vector<Sprite*>& triangles, Time startTime, Time endTime) {
		int timeDiff = endTime.ms - startTime.ms;
		Time endPause("01:23:545");
		float imageHeight = Config::I()->GetImageSize(R"(C:\Users\Wax Chug da Gwad\AppData\Local\osu!\Songs\474742 Quarks - Dualive\Storyboard\Spectrum2D\PatternPiece.png)").y;
		
		// Mirrored from PhaseSpectrum3D.hpp
		float specRadius = 16.0f;
		float specSpacing = 100.0f;
		float specScale = 0.2f;
		MusicAnalysisData& data = Config::I()->data;
		int timeIndex = data.GetMeasureIndex(Time("01:23:861"));

		// Yolo hardcoded... too much thinking for me
		float conversionFactor = 0.64f;
		
		for (int i = 0; i < triangles.size(); ++i) {
			float beforeHeight = triangles[i]->scale * triangles[i]->scaleVector.y * imageHeight;
			float dataScale = data.scaleData[i][timeIndex] * specScale * conversionFactor;
			Vector2 scaleVector = Vector2(triangles[i]->scaleVector.x, dataScale);
			triangles[i]->ScaleVector(startTime.ms, endTime.ms, triangles[i]->scaleVector, scaleVector);

			Vector3 up = Vector3(0, 1, 0) * specSpacing;
			float moveRot = 2 * M_PI * ((float)i / triangles.size());
			Vector3 pos = up.RotateZ(-moveRot);
			Vector2 perspect = pos.Perspect(Config::I()->cameraZ, Config::I()->projectionDistance);
			float afterHeight = dataScale * triangles[i]->scale * imageHeight;
			float displace = afterHeight / 2 - beforeHeight / 2;
			float trackDistance = perspect.Magnitude();
			Vector2 adjustedPos = perspect.Normalize() * (trackDistance + displace);
			triangles[i]->Move(startTime.ms, endPause.ms, triangles[i]->position, adjustedPos, Easing::CubicOut);

			float rot = moveRot;
			triangles[i]->Rotate(startTime.ms, endPause.ms, triangles[i]->rotation, rot);
			triangles[i]->Color(startTime.ms, endTime.ms, triangles[i]->color, GetColor[GC::SADNESS]);
			//float spectrumFade = (1 - (float)i / triangles.size()) * 0.75 + 0.25;
			//triangles[i]->Fade(startTime.ms, endTime.ms, triangles[i]->fade, spectrumFade);
			triangles[i]->Fade(startTime.ms, endTime.ms, triangles[i]->fade, 0.0f);
		}
	}

	int calcNumTri(Time startTetEnd, Time endScale, float frequency, int remainingTriangles) {
		int timeRemaining = endScale.ms - startTetEnd.ms;
		float divisions = timeRemaining / frequency;
		return ceilf(remainingTriangles / divisions);
	}

	Color patternColor = GetColor[GC::YELLOW];
	std::vector<Vector2> positions = Config::I()->GetPositions();
	std::vector<int> scrambledIndices = scrambleIndices(positions.size());
	std::string bgTriLargePath = "Storyboard\\Spectrum2D\\PatternPieceLarge.png";
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

		int numGenTri = calcNumTri(thirdSpeedup, Time(endThirdSpeedup.ms - moveOffset), Config::I()->mspb / 2, scrambledIndices.size());
		generateTriangles(triangles, thirdSpeedup, Time(endThirdSpeedup.ms - moveOffset), Config::I()->mspb / 2, numGenTri);

		degenerateTriangles(triangles, startTet, startTetSpeedup, 2 * Config::I()->mspb, 18);
		degenerateTriangles(triangles, startTetSpeedup, startTetEnd, Config::I()->mspb, 27);

		int numDegenTri = calcNumTri(startTetEnd, endScale, Config::I()->mspb / 2, triangles.size());
		degenerateTriangles(triangles, startTetEnd, endScale, Config::I()->mspb / 2, numDegenTri);

		placeTriangles(triangles, startPlace, endTet);
	}
};
#endif//PHASEMOIREGENERATION_HPP