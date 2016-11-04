#include "Config.hpp"
#include "PhaseLyricsTunnel.hpp"
#include "PhaseMoireGeneration.hpp"
#include "PhaseMoireSpin.hpp"
#include "PhaseSpectrum2D.hpp"
#include "PhaseSpectrum3D.hpp"
#include "PhaseTest.hpp"
#include "PhaseTetrahedronSpin.hpp"
#include "PhaseTextGeneration.hpp"
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
		GetColor[GC::CYAN],
		GetColor[GC::CYAN]);
	background->Fade(0,
		Time("00:01:756").ms,
		0.0f,
		1.0f,
		Easing::CubicIn);

	std::cout << "PhaseSpectrum2D..." << std::endl;
	PhaseSpectrum2D phaseSpectrum2D;
	std::cout << "PhaseMoireSpin..." << std::endl;
	PhaseMoireSpin phaseMoireSpin;
	std::cout << "PhaseMoireGeneration..." << std::endl;
	PhaseMoireGeneration phaseMoireGeneration;
	//std::cout << "PhaseLyricsTunnel..." << std::endl; 
	//PhaseLyricsTunnel phaseLyricsTunnel;
	//std::cout << "PhaseTetrahedronSpin..." << std::endl;
	//PhaseTetrahedronSpin phaseTetrahedronSpin;
	//std::cout << "PhaseSpectrum3D..." << std::endl;
	//PhaseSpectrum3D phaseSpectrum3D;
	//std::cout << "PhaseTextGeneration..." << std::endl;
	//PhaseTextGeneration phaseTextGeneration;

	// PhaseTest phaseTest;

	Storyboard::Instance()->Write(Config::I()->storyboardPath);
	//std::cin.get();
	return 0;
}