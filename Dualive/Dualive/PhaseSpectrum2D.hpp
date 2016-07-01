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

		centerpiece->Rotate(endExpand.ms,
			endExpand.ms + 10000,
			centerpiece->rotation,
			centerpiece->rotation + 2 * M_PI);

		// Distance away from center
		float spectrumSpacing = 60.0f;
		Vector2 startPoint = Vector2::Midpoint - Vector2(spectrumSpacing, 0);
		// Easier access
		MusicAnalysisData data = Config::I()->data;
		float barWidthScale = 0.015f;

		Time startSpectrum("00:03:019");
		Time maxFadeSpectrum("00:05:545");

		std::vector<Sprite*> spectrum(data.bandCount);
		for (int i = 0; i < data.bandCount; ++i) {
			Sprite* bar = new Sprite(cpPath, Vector2::Midpoint, Layer::Foreground, Origin::BottomCentre);
			spectrum[i] = bar;
			float rotateAmount = 2 * M_PI * ((float) i / data.bandCount);
			Vector2 specPos = startPoint.RotateAround(Vector2::Midpoint, rotateAmount);

			bar->Move(startExpand.ms,
				startSpectrum.ms,
				Vector2::Midpoint,
				specPos);

			bar->Scale(startExpand.ms,
				startSpectrum.ms,
				barWidthScale,
				barWidthScale);

			float localRotation = (-M_PI / 2) + rotateAmount;
			bar->Rotate(startExpand.ms,
				startExpand.ms,
				localRotation,
				localRotation);

			bar->Fade(startExpand.ms,
				maxFadeSpectrum.ms,
				0.0f,
				1.0f);

			bar->Fade(maxFadeSpectrum.ms,
				Config::I()->songEnd.ms,
				1.0f,
				1.0f);
		}
	}
};

#endif//PHASESPECTRUM2D_HPP