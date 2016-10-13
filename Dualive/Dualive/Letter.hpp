#ifndef LETTER_HPP
#define LETTER_HPP

#include "Config.hpp"
#include "LetterMeasurements.hpp"

class Letter {
public:
	Letter(VectorMap& vectorMap);
	static int getIndex(char c);
	void display(int startTime, int endTime, float scale, Vector2 displacement);

	VectorMap vectorMap;
	std::vector<std::vector<Pair>> pairTravel;
	std::vector<std::vector<Sprite*>> spriteTravel;
	LetterMeasurements letterMeasurements;

	static std::string linePath;
	static float lineScaleHeight;

private:
	static std::vector<std::vector<Vector2>> buildTravel(VectorMap& vectorMap);
	static std::vector<std::vector<Pair>> buildPairs(VectorMap& vectorMap, std::vector<std::vector<Vector2>>& travel);
	static LetterMeasurements calculateMeasurements(VectorMap& vectorMap);
	static std::vector<std::vector<Sprite*>> setupSprites(std::vector<std::vector<Pair>>& pairTravel);
};

#endif//LETTER_HPP