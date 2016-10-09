#ifndef LETTERMEASUREMENTS_HPP
#define LETTERMEASUREMENTS_HPP

#include "Config.hpp"

class LetterMeasurements {
public:
	LetterMeasurements(Vector2 min, Vector2 max);
	Vector2 min;
	Vector2 max;
	float width;
	float height;
	float halfWidth;
	float halfHeight;
};

#endif//LETTERMEASUREMENTS_HPP