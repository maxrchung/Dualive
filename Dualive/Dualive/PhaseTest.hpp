#ifndef PHASETEST_HPP
#define PHASETEST_HPP

#include "Phase.hpp"

class PhaseTest : public Phase{
public:
	PhaseTest() {
		Sprite* line = new Sprite("Storyboard\\Blank.png", Vector2::Midpoint, Layer::Foreground);
		line->ScaleVector(Config::I()->songStart.ms,
			Config::I()->songEnd.ms,
			Vector2(0.002f, 0.768f),
			Vector2(0.002f, 0.768f));

		line->Color(Config::I()->songStart.ms,
			Config::I()->songEnd.ms,
			Color(255, 0, 0),
			Color(255, 0, 0));

		Sprite* line2 = new Sprite("Storyboard\\Blank.png", Vector2::Midpoint, Layer::Foreground);
		line2->ScaleVector(Config::I()->songStart.ms,
			Config::I()->songEnd.ms,
			Vector2(1.366f, 0.002f),
			Vector2(1.366f, 0.002f));

		line2->Color(Config::I()->songStart.ms,
			Config::I()->songEnd.ms,
			Color(255, 0, 0),
			Color(255, 0, 0));
	}
};

#endif//PHASETEST_HPP