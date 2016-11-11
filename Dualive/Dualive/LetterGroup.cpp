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

	// Randomize the disabled list so that it does not only take the last half of sprites
	for (int i = 0; i < sprites.size(); ++i) {
		disableIndices.push_back(i);
		disableReference.push_back(false);
		markedReference.push_back(false);
	}
	std::random_shuffle(disableIndices.begin(), disableIndices.end());
}

int LetterGroup::spaceWidth = 200;
int LetterGroup::verticalDisplacement = 150;
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

void LetterGroup::Color(int startTime, int endTime, ::Color color) {
	for (auto sprite : sprites) {
		sprite->Color(startTime, endTime, color, color);
	}
}

void LetterGroup::Move(Vector3 movement) {
	for (auto& pair : pair3s) {
		pair.first += movement;
		pair.second += movement;
	}

	rectPoints.Move(movement);
}

void LetterGroup::Rotate(Vector3 rotAmounts) {
	Rotate(rotAmounts.x, rotAmounts.y, rotAmounts.z);
}


void LetterGroup::Rotate(float xRot, float yRot, float zRot) {
	for (auto& pair : pair3s) {
		pair.first = pair.first.Rotate(xRot, yRot, zRot);
		pair.second = pair.second.Rotate(xRot, yRot, zRot);
	}
	rectPoints.Rotate(xRot, yRot, zRot);
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
	rectPoints.Rotate(xRot, yRot, zRot);
}

void LetterGroup::Fade(int startTime, int endTime, float fade, Easing easing) {
	for (auto sprite : sprites) {
		// Stop some calls
		if (sprite->fade != 0.0f) {
			sprite->Fade(startTime, endTime, sprite->fade, fade, easing);
		}
	}
}

void LetterGroup::Reposition(int startTime, int endTime, Easing easing) {
	// Disables half on each reposition
	int disableAmount = disableIndices.size() / 2;
	for (int i = 0; i < disableAmount; ++i) {
		markedReference[disableIndices.back()] = true;
		disableIndices.pop_back();
	}

	for (int i = 0; i < sprites.size(); ++i) {
		if (!disableReference[i]) {
			float displacement = (rand() % 75) / 75.0f + 0.25f;
			float offsetEnd = startTime + (endTime - startTime) * displacement;

			Sprite* line = sprites[i];
			Pair3 pair = pair3s[i];

			Vector2 startPoint = pair.first.Perspect(Config::I()->cameraZ, Config::I()->projectionDistance);
			Vector2 endPoint = pair.second.Perspect(Config::I()->cameraZ, Config::I()->projectionDistance);
			Vector2 distanceVector = endPoint - startPoint;
			float rotation = Vector2(line->rotation).AngleBetween(distanceVector);
			float totalRotation = line->rotation + rotation;

			// How to tell if sprite has been disabled
			if (markedReference[i]) {
				line->Move(startTime, offsetEnd + Config::I()->mspb * 4, line->position, startPoint, easing);
				line->Fade(startTime, offsetEnd, line->fade, line->fade / 2.0f, easing);
				line->Fade(offsetEnd, offsetEnd + Config::I()->mspb * 4, line->fade, 0.0f, easing);
				disableReference[i] = true;
			}
			else {
				line->Rotate(startTime, offsetEnd, line->rotation, totalRotation, easing);
				line->Move(startTime, offsetEnd, line->position, startPoint, easing);
				float endFade = line->fade - 1.0f / Config::I()->afterImages;
				line->Fade(startTime, offsetEnd, line->fade, endFade, easing);
			}
		}
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