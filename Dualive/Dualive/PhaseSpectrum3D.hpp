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
		center->Scale(1.5f);
		center->RepositionLines(Range(startSpec.ms));
		center->Color(Range(startSpec.ms), GetColor[GC::SADNESS], GetColor[GC::SADNESS]);

		for (int i = 0; i < numSpec; ++i) {
			Tetrahedron* specTri = new Tetrahedron(specRadius);
			float rot = (2 * M_PI) * ((float)i / numSpec);
			// Local rotation
			specTri->RotateY(Config::I()->DToR(-30));
			// Set to start at (0, specSpacing)
			specTri->RotateZ(Config::I()->DToR(0));

			// Move to position
			Vector2 pos = Vector2(0, specSpacing);
			specTri->Move(Vector3(pos));

			// Rotate to position
			specTri->RotateZ(-rot);

			specTri->Color(Range(startSpec.ms), GetColor[GC::SADNESS], GetColor[GC::SADNESS]);
			spectrum.push_back(specTri);
		}
	}

	void spinTetrahedrons() {
		MusicAnalysisData& data = Config::I()->data;
		float discRate = data.snapshotRate / 2.0f;
		float disc = discRate / (endSpec.ms - startSpec.ms);
		float totalRot = 4 * M_PI;
		Vector3 rotAround = Vector3(-1, -1, -1);

		ScaleTimings scaleTimings;
		Config::I()->AddScaleTimings(scaleTimings, startSpec, endSpec, Config::I()->mspb, 1.5f, 1.0f);

		for (int time = startSpec.ms; time < endSpec.ms; time += discRate) {
			float rot = disc * totalRot;
			// Aiming for the tick after startSpec
			Range reposition(time, time + discRate);

			center->RotateAround(rotAround, rot);
			center->Scale(Config::I()->GetScale(scaleTimings, time));
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
				float startFade = (1 - (float)i / spectrum.size()) * 0.75 + 0.25;
				spectrum[i]->Fade(Range(startSpec.ms), startFade, startFade);
			}
		}
	}

	void fadeTetrahedrons() {
		int spriteCount = 0;
		std::vector<Sprite*> sprites = getSprites();
		std::random_shuffle(std::begin(sprites), std::end(sprites));

		fadeSection(sprites, startFade, startFadeSpeedup, Config::I()->offset);

		Time adjustedEndVoice = Time(endVoice.ms - Config::I()->offset * 8);
		float fadeRate = calcSpeedFade(startFadeSpeedup, adjustedEndVoice, sprites.size());
		fadeSection(sprites, startFadeSpeedup, adjustedEndVoice, fadeRate);
	}

	float calcSpeedFade(Time startFade, Time endFade, int remainingTriangles) {
		int timeRemaining = endFade.ms - startFade.ms;
		return timeRemaining / remainingTriangles;
	}

	void fadeSection(std::vector<Sprite*>& sprites, Time start, Time end, float frequency) {
		for (int i = start.ms; i < end.ms; i += frequency) {
			if (sprites.size() == 0) {
				return;
			}
			Sprite* end = sprites.back();
			end->Fade(i, i + Config::I()->offset * 8, end->fade, 0.0f);
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

	void colorTetrahedrons() {
		std::vector<Tetrahedron*> tets = spectrum;
		tets.push_back(center);

		for (auto tet : tets) {
			tet->Color(Time("01:23:861").ms, Time("01:26:387").ms, tet->lines[0]->color, GetColor[GC::TRAFFICONE]);
			tet->Color(Time("01:26:387").ms, Time("01:28:914").ms, tet->lines[0]->color, GetColor[GC::PARADELIGHTS]);
			tet->Color(Time("01:28:914").ms, Time("01:31:440").ms, tet->lines[0]->color, GetColor[GC::EMERALD]);
			tet->Color(Time("01:31:440").ms, Time("01:33:966").ms, tet->lines[0]->color, GetColor[GC::STOICROCK]);

			for (auto line : tet->lines) {
				Config::I()->SwitchSpriteColor(line, 
					Time("01:33:966").ms, Time("01:36:493").ms - Config::I()->mspb * 2,
					GetColor[GC::STOICROCK], GetColor[GC::FLAMINGROCKET],
					Config::I()->mspb * 2, Config::I()->mspb * 2);

				Config::I()->SwitchSpriteColor(line, 
					Time("01:36:493").ms, Time("01:39:019").ms - Config::I()->mspb * 2,
					GetColor[GC::MARBLEGUMBALL], GetColor[GC::FLAMINGROCKET],
					Config::I()->mspb * 2, Config::I()->mspb * 2);

				Config::I()->SwitchSpriteColor(line, 
					Time("01:39:019").ms, Time("01:40:282").ms - Config::I()->mspb / 2,
					GetColor[GC::SATURN], GetColor[GC::MARBLEGUMBALL],
					Config::I()->mspb / 2, Config::I()->mspb / 2);

				Config::I()->SwitchSpriteColor(line, 
					Time("01:40:282").ms, Time("01:42:177").ms, 
					GetColor[GC::SATURN], GetColor[GC::MARBLEGUMBALL],
					Config::I()->mspb / 4, Config::I()->mspb / 4);
			}
		}
	}

	// Set 1/16 before because of some drawing issue with trying
	// to call reposition lines twice(?)...?
	Time startSpec = Time("01:23:841");
	Time startFade = Time("01:33:966");
	Time startFadeSpeedup = Time("01:39:019");
	Time endVoice = Time("01:42:177");
	Time endSpec = Time("01:44:071");
	std::vector<Tetrahedron*> spectrum;
	Tetrahedron* center;
	float radius = 50.0f;
	float specRadius = 16.0f;
	float specSpacing = 100.0f;
	float specScale = 0.2f;
	int numSpec = 24;

public:
	PhaseSpectrum3D() {
		setupTetrahedrons();
		spinTetrahedrons();
		colorTetrahedrons();
		fadeTetrahedrons();
	}
};

#endif//PHASESPECTRUM3D_HPP