#include "LetterGroup.hpp"

LetterGroup::LetterGroup(std::vector<Letter>& lettersBase, std::string& lyric) {
	for (auto character : lyric) {
		if (character == ' ') {
			letters.push_back(NULL);
		}
		else if (character == '\'') {
			auto vectorMap = lettersBase.back().vectorMap;
			letters.push_back(new Letter(vectorMap));
		}
		else {
			int index = Letter::getIndex(character);
			auto vectorMap = lettersBase[index].vectorMap;
			letters.push_back(new Letter(vectorMap));
		}
	}

	// Set up sprites
	for (auto letter : letters) {
		if (letter != NULL) {
			for (auto& layer : letter->spriteTravel) {
				sprites.insert(sprites.end(), layer.begin(), layer.end());
			}
		}
	}
}

int LetterGroup::spaceWidth = 200;
int LetterGroup::verticalDisplacement = 200;
float LetterGroup::widthMax = 0.9f;
float LetterGroup::heightMax = 0.2f;
void LetterGroup::display(int startTime, int endTime) {
	// Calculate width and scale
	float width = 0;
	for (auto letter : this->letters) {
		if (letter == NULL) {
			width += spaceWidth;
		}
		else {
			width += letter->letterMeasurements.max.x;
		}
	}
	float widthScale = (Config::I()->bgDims.x * widthMax) / width;
	Vector2 displacement(-width / 2, -verticalDisplacement);

	// Display each letter with width/scale
	for (int i = 0; i < this->letters.size(); ++i) {
		if (this->letters[i] == NULL) {
			displacement.x += spaceWidth;
		}
		else {
			float height = this->letters[i]->letterMeasurements.max.y;
			float heightScale = (Config::I()->bgDims.y * heightMax) / height;

			float scale;
			if (widthScale < heightScale) {
				scale = widthScale;
			}
			else {
				scale = heightScale;
			}

			this->letters[i]->display(startTime, endTime, scale, displacement);
			displacement.x += this->letters[i]->letterMeasurements.max.x;
			setupPair3s(letters[i]->pairTravel);
			rectPoints = RectPoints(pair3s);
		}
	}
}

void LetterGroup::Move(Vector3 movement) {
	for (auto& pair : pair3s) {
		pair.first += movement;
		pair.second += movement;
	}

	rectPoints.Move(movement);
}

void LetterGroup::Rotate(float xRot, float yRot, float zRot) {
	for (auto& pair : pair3s) {
		pair.first = pair.first.Rotate(xRot, yRot, zRot);
		pair.second = pair.second.Rotate(xRot, yRot, zRot);
	}
}

void LetterGroup::LocalRotate(float xRot, float yRot, float zRot) {
	Vector3 center = rectPoints.points[4];
	for (auto& pair : pair3s) {
		pair.first = pair.first - center;
		pair.first = pair.first.Rotate(xRot, yRot, zRot);
		pair.first = pair.first + center;

		pair.second = pair.second - center;
		pair.second = pair.second.Rotate(xRot, yRot, zRot);
		pair.second = pair.second + center;
	}
}

void LetterGroup::Fade(int startTime, int endTime, float fade) {
	for (auto sprite : sprites) {
		sprite->Fade(startTime, endTime, sprite->fade, fade);
	}
}

void LetterGroup::Reposition(int startTime, int endTime) {
	for (int i = 0; i < sprites.size(); ++i) {
		Pair3 pair = pair3s[i];

		Vector2 startPoint = pair.first.Perspect(Config::I()->cameraZ, Config::I()->projectionDistance);
		Vector2 endPoint = pair.second.Perspect(Config::I()->cameraZ, Config::I()->projectionDistance);

		Vector2 distanceVector = endPoint - startPoint;
		float lineLength = distanceVector.Magnitude();
		float lineScaleWidth = lineLength / 1000;
		Vector2 lineScale(lineScaleWidth, Letter::lineScaleHeight);
		float rotation = Vector2(1, 0).AngleBetween(distanceVector);

		Sprite* line = sprites[i];
		line->ScaleVector(startTime, endTime, line->scaleVector, lineScale);
		line->Rotate(startTime, endTime, line->rotation, rotation);
		line->Move(startTime, endTime, line->position, startPoint);
		line->Color(startTime, endTime, Color(255), Color(255));
	}
}

// Used for converting the 2D pairs to 3D pairs
// Applied after initial display
void LetterGroup::setupPair3s(std::vector<std::vector<Pair>>& pairTravel) {
	for (auto& layer : pairTravel) {
		for (auto pair : layer) {
			pair3s.push_back(Pair3(Vector3(pair.first), Vector3(pair.second)));
		}
	}
}