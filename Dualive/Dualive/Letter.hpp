#ifndef LETTER_HPP
#define LETTER_HPP

#include "Config.hpp"
#include "LetterMeasurements.hpp"

class Letter {
public:
	Letter(VectorMap& vectorMap);
private:
	static std::vector<std::vector<Vector2>> buildTravel(VectorMap& vectorMap);
	static std::vector<std::vector<Pair>> buildPairs(VectorMap& vectorMap, std::vector<std::vector<Vector2>>& travel);
	static LetterMeasurements calculateMeasurements(VectorMap& vectorMap);

	static std::string linePath;
	static float lineScaleHeight;
	static void display(Letter* letter, int startTime, int endTime, float scale, Vector2 displacement);
	static std::vector<std::vector<Sprite*>> setupSprites(std::vector<std::vector<Pair>>& pairTravel);
	static int getIndex(char c);

	VectorMap vectorMap;
	LetterMeasurements letterMeasurements;
	std::vector<std::vector<Pair>> pairTravel;
	std::vector<std::vector<Sprite*>> spriteTravel;
};

#endif//LETTER_HPP