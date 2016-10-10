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

	for (auto& letter : letters) {
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
void LetterGroup::display(LetterGroup& letterGroup, int startTime, int endTime) {
	// Calculate width and scale
	float width = 0;
	for (auto letter : letterGroup.letters) {
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
	for (int i = 0; i < letterGroup.letters.size(); ++i) {
		if (letterGroup.letters[i] == NULL) {
			displacement.x += spaceWidth;
		}
		else {
			float height = letterGroup.letters[i]->letterMeasurements.max.y;
			float heightScale = (Config::I()->bgDims.y * heightMax) / height;

			float scale;
			if (widthScale < heightScale) {
				scale = widthScale;
			}
			else {
				scale = heightScale;
			}

			Letter::display(*letterGroup.letters[i], startTime, endTime, scale, displacement);
			displacement.x += letterGroup.letters[i]->letterMeasurements.max.x;
		}
	}
}