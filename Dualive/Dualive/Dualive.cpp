#include "Config.hpp"
#include "PhaseLyricsTunnel.hpp"
#include "PhaseMoireGeneration.hpp"
#include "PhaseMoireSpin.hpp"
#include "PhaseSpectrum2D.hpp"
#include "PhaseTest.hpp"
#include "PhaseTitle.hpp"
#include "Storyboard.hpp"
#include "Time.hpp"
#include <iostream>

int main() {
	// For random
	srand(time(NULL));

	Vector2 maxBgSize(Vector2::ScreenSize);
	Sprite* background = new Sprite("Storyboard\\Background\\Blank.png", Vector2::Midpoint, Layer::Background);
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
	PhaseMoireGeneration phaseMoireGeneration;
	//PhaseMoireSpin phaseMoireSpin;
	//PhaseLyricsTunnel phaseLyricsTunnel;

	Storyboard::Instance()->Write(Config::I()->storyboardPath);
	//std::cin.get();
	return 0;
}