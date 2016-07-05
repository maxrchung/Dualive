#ifndef PHASETEST_HPP
#define PHASETEST_HPP

#include "Phase.hpp"

class PhaseTest : public Phase{
public:
	PhaseTest() {
		Sprite* line = new Sprite("Storyboard\\Blank.png", Vector2::Midpoint, Layer::Background);
		line->ScaleVector(Config::I()->songStart.ms,
			Config::I()->songEnd.ms,
			Vector2(0.002f, 0.768f),
			Vector2(0.002f, 0.768f));

		Sprite* line2 = new Sprite("Storyboard\\Blank.png", Vector2::Midpoint, Layer::Background);
		line2->ScaleVector(Config::I()->songStart.ms,
			Config::I()->songEnd.ms,
			Vector2(1.366f, 0.002f),
			Vector2(1.366f, 0.002f));
	}
};

#endif//PHASETEST_HPP