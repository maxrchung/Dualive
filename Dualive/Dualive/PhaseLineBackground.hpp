#ifndef PHASELINEBACKGROUND_HPP
#define PHASELINEBACKGROUND_HPP

#include "Config.hpp"

class PhaseLineBackground {
private:
	// Remove triangles that are too close to the center
	float maxDist = 100.0f;
	void removeCenter(std::vector<Vector2>& positions) {
		std::vector<Vector2> removedPositions;
		for (auto position : positions) {
			if (position.Magnitude() > maxDist) {
				removedPositions.push_back(position);
			}
		}

		positions = removedPositions;
	}
	
	void spawn() {
		positions = Config::I()->GetPositions();
		removeCenter(positions);
		std::random_shuffle(positions.begin(), positions.end());

		// Copied from GetPositions()
		std::string triangleAbsolutePath(R"(C:\Users\Wax Chug da Gwad\AppData\Local\osu!\Songs\Quarks_Dualive_SDVX_NOFX\Storyboard\Spectrum2D\PatternPiece.png)");
		Vector2 imageSize(Config::I()->GetImageSize(triangleAbsolutePath));
		Vector2 scaledSize(imageSize * Config::I()->patternScale);
		
		int startSpawn = Time("01:23:861").ms;
		int endSpawn = Time("01:33:966").ms;
		int timeSpawn = endSpawn - startSpawn;
		int frequency = Config::I()->mspb;
		int spawns = timeSpawn / frequency;
		int triPerSpawn = positions.size() / spawns;
		spawnTriangles(scaledSize, startSpawn, endSpawn, triPerSpawn, frequency);
	}

	std::string linePath = "Storyboard\\3D\\line.png";
	float farDistance = 500.0f;
	void spawnTriangles(Vector2 scaledSize, int startTime, int endTime, int numTri, int frequency) {
		for (int i = startTime; i < endTime; i += frequency) {
			for (int j = 0; j < numTri; ++j) {
				if (positions.empty())
					return;

				Vector2 center = positions.back();
				positions.pop_back();
				Vector2 farStart = center.Normalize() * farDistance;

				Sprite* topLeft = new Sprite(linePath, Vector2::Zero, Layer::Background, Origin::CentreLeft);
				topLeft->Rotate(i, i, -M_PI / 3, -M_PI / 3);
				Vector2 botLeftCorner = -scaledSize / 2.0f;
				topLeft->Move(i - Config::I()->mspb * 2, i, farStart + botLeftCorner, center + botLeftCorner, Easing::CubicIn);
				Vector2 scaleVector(scaledSize.x / Config::I()->lineWidth, 0.11f);
				topLeft->ScaleVector(i, i, scaleVector, scaleVector);

				Sprite* topRight = new Sprite(linePath, Vector2::Zero, Layer::Background, Origin::CentreLeft);
				topRight->Rotate(i, i, M_PI / 3, M_PI / 3);
				// The Move's -1 and ScaleVector's special scaleVector fixes a 1 pixel off error
				Vector2 topCenter = Vector2(0, scaledSize.y / 2 - 1);
				topRight->Move(i - Config::I()->mspb * 2, i, farStart + topCenter, center + topCenter, Easing::CubicIn);
				Vector2 topRightScaleVector(scaledSize.x / Config::I()->lineWidth * 0.95f, 0.11f);
				topRight->ScaleVector(i, i, topRightScaleVector, topRightScaleVector);

				Sprite* bottom = new Sprite(linePath, Vector2::Zero, Layer::Background, Origin::CentreLeft);
				bottom->Move(i - Config::I()->mspb * 2, i, farStart + botLeftCorner, center + botLeftCorner, Easing::CubicIn);
				bottom->ScaleVector(i, i, scaleVector, scaleVector);

				std::vector<Sprite*> lines = { topLeft, topRight, bottom };
				float fadeAmount = center.Magnitude() / farDistance;
				for (auto line : lines) {
					line->Fade(i - Config::I()->mspb * 2, i, 0.0f, fadeAmount);
					if (i - Config::I()->mspb * 2 < Time("01:23:841").ms)
						line->Color(Time("01:23:841").ms, Time("01:23:841").ms, GetColor[GC::SADNESS], GetColor[GC::SADNESS]);
					if (i - Config::I()->mspb * 2 < Time("01:26:387").ms)
						line->Color(Time("01:23:861").ms, Time("01:26:387").ms, GetColor[GC::SADNESS], GetColor[GC::TRAFFICONE]);
					if (i - Config::I()->mspb * 2 < Time("01:28:914").ms)
						line->Color(Time("01:26:387").ms, Time("01:28:914").ms, GetColor[GC::TRAFFICONE], GetColor[GC::PARADELIGHTS]);
					if (i - Config::I()->mspb * 2 < Time("01:31:440").ms)
						line->Color(Time("01:28:914").ms, Time("01:31:440").ms, GetColor[GC::PARADELIGHTS], GetColor[GC::EMERALD]);
					if (i - Config::I()->mspb * 2 < Time("01:33:966").ms)
						line->Color(Time("01:31:440").ms, Time("01:33:966").ms, GetColor[GC::EMERALD], GetColor[GC::STOICROCK]);

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

					sprites.push_back(line);
				}
			}
		}
	}

	void despawn() {
		std::random_shuffle(sprites.begin(), sprites.end());
		despawnTriangles(Time("01:33:966").ms, Time("01:39:019").ms, 81, Config::I()->mspb);

		int startDespawn = Time("01:39:019").ms;
		int endDespawn = Time("01:42:177").ms - Config::I()->mspb * 2;
		int timeDespawn = endDespawn - startDespawn;
		int frequency = Config::I()->offset;
		int despawns = timeDespawn / frequency;
		int triPerDespawn = sprites.size() / despawns;
		despawnTriangles(startDespawn, endDespawn, triPerDespawn, Config::I()->offset);
	}

	void despawnTriangles(int startTime, int endTime, int numSprites, int frequency) {
		for (int i = startTime; i < endTime; i += frequency) {
			for (int j = 0; j < numSprites; ++j) {
				if (sprites.empty()) {
					return;
				}
				
				Sprite* sprite = sprites.back();
				sprites.pop_back();

				sprite->Fade(i, i + Config::I()->mspb * 2, sprite->fade, 0.0f);
			}
		}
	}

	std::vector<Sprite*> sprites;
	std::vector<Vector2> positions;
public:
	PhaseLineBackground() {
		spawn();
		despawn();
	}
};

#endif//PHASELINEBACKGROUND_HPP