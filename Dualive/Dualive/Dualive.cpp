#include "Config.hpp"
#include "PhaseLyricsTunnel.hpp"
#include "PhaseMoireGeneration.hpp"
#include "PhaseMoireSpin.hpp"
#include "PhaseSpectrum2D.hpp"
#include "PhaseTest.hpp"
#include "PhaseTetrahedronSpin.hpp"
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
	background->Fade(0,
		Time("00:01:756").ms,
		0.0f,
		1.0f);

	PhaseSpectrum2D phaseSpectrum2D;
	PhaseMoireSpin phaseMoireSpin;
	PhaseMoireGeneration phaseMoireGeneration;
	PhaseLyricsTunnel phaseLyricsTunnel;
	PhaseTetrahedronSpin phaseTetrahedronSpin;

	// PhaseTest phaseTest;

	Storyboard::Instance()->Write(Config::I()->storyboardPath);
	//std::cin.get();
	return 0;
}