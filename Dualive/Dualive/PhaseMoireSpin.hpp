#ifndef PHASEMOIRESPIN_HPP
#define PHASEMOIRESPIN_HPP

#include "Config.hpp"

class PhaseMoireSpin {
private:
	void SetupBackground(Sprite* bg) {
		bg->Scale(startMoire.ms, 
			endMoire.ms, 
			Config::I()->patternScale, 
			Config::I()->patternScale);

		bg->Color(0,
			endThirdSpeedup.ms,
			Color(25),
			Color(25));

		bg->Color(endThirdSpeedup.ms, 
			startMoire.ms, 
			bg->color, 
			Color(255));

		bg->Color(startFadeEnd.ms, 
			endMoire.ms, 
			bg->color, 
			Color(0));
	}

	std::string bgPath = "Storyboard\\Spectrum2D\\Pattern.png";
	std::string bgPathSpacing = "Storyboard\\Spectrum2D\\PatternSpacing.png";
	Time endThirdSpeedup = Time("00:21:966");
	Time startMoire = Time("00:23:229");
	Time startFadeEnd = Time("00:42:177");
	Time endMoire = Time("00:43:440");
	// Seems good
	Vector2 moveOffset = Vector2(0, 14) * Config::I()->patternScale / 2;

public:
	PhaseMoireSpin() {
		Sprite* bg = new Sprite(bgPath, Vector2::Zero, Layer::Background);
		SetupBackground(bg);
		bg->Fade(0,
			Time("00:01:756").ms,
			0.0f,
			1.0f);

		Sprite* pattern = new Sprite(bgPathSpacing, Vector2::Zero - moveOffset, Layer::Background);
	 	SetupBackground(pattern);
		pattern->Fade(0,
			endThirdSpeedup.ms,
			Config::I()->reallySmallNumber,
			Config::I()->reallySmallNumber);
		pattern->Fade(endThirdSpeedup.ms,
			endThirdSpeedup.ms,
			1.0f,
			1.0f);
		pattern->Rotate(startMoire.ms, 
			endMoire.ms, 
			pattern->rotation, 
			2 * M_PI);
	}
};

#endif//PHASEMOIRESPIN_HPP