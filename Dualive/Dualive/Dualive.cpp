#include "Config.hpp"
#include "Time.hpp"
#include "PhaseTitle.hpp"
#include "PhaseSpectrum2D.hpp"
#include "Storyboard.hpp"
#include <iostream>

int main() {
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

	PhaseTitle phaseTitle;
	PhaseSpectrum2D phaseSpectrum2D;

	Storyboard::Instance()->Write(Config::I()->storyboardPath);
	//std::cin.get();
	return 0;
}