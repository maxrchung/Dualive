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
				for (auto line : lines) {
					line->Fade(i, i + Config::I()->mspb * 100, 1.0f, 1.0f);
					sprites.push_back(line);
				}

			}
		}
	}

	void despawn(std::vector<Sprite*> sprites) {

	}

	std::vector<Sprite*> sprites;
	std::vector<Vector2> positions;
public:
	PhaseLineBackground() {
		positions = Config::I()->GetPositions();
		removeCenter(positions);
		std::random_shuffle(positions.begin(), positions.end());
		spawn();

		std::random_shuffle(sprites.begin(), sprites.end());
		despawn(sprites);
	}
};

#endif//PHASELINEBACKGROUND_HPP