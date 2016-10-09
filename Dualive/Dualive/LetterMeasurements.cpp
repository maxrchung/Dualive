#include "LetterMeasurements.hpp"

LetterMeasurements::LetterMeasurements(Vector2 min, Vector2 max)
	: width(max.x - min.x),
	height(max.y - min.y),
	halfWidth(width / 2),
	halfHeight(height / 2) {}
