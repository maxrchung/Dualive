#ifndef PHASESPECTRUM2D_HPP
#define PHASESPECTRUM2D_HPP

#include "Phase.hpp"

class PhaseSpectrum2D : public Phase {
public:
	PhaseSpectrum2D() {
		std::string directory = "Storyboard\\Spectrum2D\\";
		std::string cpPath = directory + "Centerpiece.png";

		Time startExpand("00:01:756");
		Time endExpand("00:02:387");
		Time endShrink("00:02:703");

		float cpExpandScale = 0.15f;
		float cpShrinkScale = 0.075f;

		Sprite* centerpiece = new Sprite(cpPath);
		centerpiece->Scale(startExpand.ms,
			endExpand.ms,
			0.0f,
			cpExpandScale);

		centerpiece->Fade(startExpand.ms,
			endExpand.ms,
			0.0f,
			1.0f);

		centerpiece->Scale(endExpand.ms,
			endShrink.ms,
			centerpiece->scale,
			cpShrinkScale);

		centerpiece->Fade(endExpand.ms,
			Config::I()->songEnd.ms,
			1.0f,
			1.0f);

		

	}
};

#endif//PHASESPECTRUM2D_HPP