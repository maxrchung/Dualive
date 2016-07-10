#include "Config.hpp"
#include "PhaseMoire.hpp"
#include "PhaseSpectrum2D.hpp"
#include "PhaseTest.hpp"
#include "PhaseTitle.hpp"
#include "Storyboard.hpp"
#include "Time.hpp"
#include <iostream>

int main() {
	// For random
	srand(time(NULL));

	Vector2 maxBgSize(1.366f, 0.768f);
	Sprite* background = new Sprite("Storyboard\\Blank.png", Vector2::Midpoint, Layer::Background);
	background->ScaleVector(Config::I()->songStart.ms,
		Config::I()->songEnd.ms,
		maxBgSize,
		maxBgSize);
	background->Color(Config::I()->songStart.ms,
		Config::I()->songEnd.ms,
		Color(0),
		Color(0));

	// PhaseTest phaseTest;
	// PhaseTitle phaseTitle;
	PhaseSpectrum2D phaseSpectrum2D;
	PhaseMoire phaseMoire;

	Storyboard::Instance()->Write(Config::I()->storyboardPath);
	//std::cin.get();
	return 0;
}