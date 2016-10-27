#ifndef PHASESPECTRUM3D_HPP
#define PHASESPECTRUM3D_HPP

#include "Config.hpp"

class PhaseSpectrum3D {
private:
	void setupTetrahedrons() {
		center = new Tetrahedron(radius);
		center->RotateX(-M_PI / 2);
		// Flip around
		center->RotateY(M_PI);
		center->Scale(1.0f);
		center->RepositionLines(Range(startSpec.ms));

		for (int i = 0; i < numSpec; ++i) {
			Tetrahedron* specTri = new Tetrahedron(specRadius);
			float rot = (2 * M_PI) * ((float)i / numSpec);
			// Local rotation
			specTri->RotateY(Config::I()->DToR(-30));
			// Set to start at (-specSpacing,0,0)
			specTri->RotateZ(Config::I()->DToR(90));

			// Move to position
			Vector2 pos = Vector2(-specSpacing, 0);
			specTri->Move(Vector3(pos));

			// Rotate to position
			specTri->RotateZ(-rot);
			spectrum.push_back(specTri);
		}
	}

	void spinTetrahedrons() {
		MusicAnalysisData& data = Config::I()->data;
		float discRate = data.snapshotRate / 2.0f;
		float disc = discRate / (endSpec.ms - startSpec.ms);
		float totalRot = 4 * M_PI;
		Vector3 rotAround = Vector3(-1, -1, -1);

		for (int time = startSpec.ms; time < endSpec.ms; time += discRate) {
			float rot = disc * totalRot;
			// Aiming for the tick after startSpec
			Range reposition(time, time + discRate);

			center->RotateAround(rotAround, rot);
			center->RepositionLines(reposition);

			int timeIndex = data.GetMeasureIndex(Time(reposition.end));
			for (int i = 0; i < spectrum.size(); ++i) {
				float scale = data.scaleData[i][timeIndex] * specScale;
				spectrum[i]->RotateAround(rotAround, rot);
				spectrum[i]->ScaleVector(scale);
				if (time == startSpec.ms) {
					spectrum[i]->RepositionLines(Range(startSpec.ms));
				}
				else {
					spectrum[i]->RepositionLines(reposition);
				}
			}
		}
	}

	void fadeTetrahedrons() {
		int spriteCount = 0;
		std::vector<Sprite*> sprites = getSprites();
		std::random_shuffle(std::begin(sprites), std::end(sprites));

		fadeSection(sprites, startFade, startFadeSpeedup, Config::I()->offset);
		fadeSection(sprites, startFadeSpeedup, endSpec, Config::I()->offset / 2);
	}

	void fadeSection(std::vector<Sprite*>& sprites, Time start, Time end, float frequency) {
		for (int i = start.ms; i < end.ms; i += frequency) {
			if (sprites.size() == 0) {
				return;
			}
			Sprite* end = sprites.back();
			end->Fade(i, i + Config::I()->offset * 8, 1.0f, 0.0f);
			sprites.pop_back();
		}
	}

	std::vector<Sprite*> getSprites() {
		int spriteCount = 0;
		std::vector<Sprite*> sprites;

		// Pointer auto copies
		for (auto line : center->lines) {
			sprites.push_back(line);
			++spriteCount;
		}

		for (auto spec : spectrum) {
			for (auto line : spec->lines) {
				sprites.push_back(line);
				++spriteCount;
			}
		}

		return sprites;
	}

	Time startSpec = Time("01:23:861");
	Time startFade = Time("01:33:966");
	Time startFadeSpeedup = Time("01:39:019");
	Time endSpec = Time("01:44:071");
	std::vector<Tetrahedron*> spectrum;
	Tetrahedron* center;
	float radius = 50.0f;
	float specRadius = 16.0f;
	float specSpacing = 100.0f;
	float specScale = 0.15f;
	int numSpec = 24;

public:
	PhaseSpectrum3D() {
		setupTetrahedrons();
		spinTetrahedrons();
		fadeTetrahedrons();
	}
};

#endif//PHASESPECTRUM3D_HPP