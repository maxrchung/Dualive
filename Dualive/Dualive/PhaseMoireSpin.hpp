#ifndef PHASEMOIRESPIN_HPP
#define PHASEMOIRESPIN_HPP

#include "Config.hpp"

class PhaseMoireSpin {
private:
	void SetupBackground(Sprite* bg) {
		bg->Scale(startMoire.ms, endMoire.ms, Config::I()->patternScale, Config::I()->patternScale);
		bg->Color(0, 0, GetColor[GC::YELLOW], GetColor[GC::YELLOW]);
		Config::I()->SwitchSpriteColor(bg, Time("00:27:019").ms, Time("00:28:282").ms, GetColor[GC::TOMATOSAUCE], GetColor[GC::YELLOW], Config::I()->mspb, Config::I()->mspb);
		Config::I()->SwitchSpriteColor(bg, Time("00:30:808").ms, Time("00:33:335").ms, GetColor[GC::BUBBLEGUM], GetColor[GC::TOMATOSAUCE], Config::I()->mspb, Config::I()->mspb);
		bg->Color(Time("00:34:282").ms, Time("00:34:598").ms, GetColor[GC::BUBBLEGUM], GetColor[GC::INDIGOPRIDE]);
		bg->Color(Time("00:35:545").ms, Time("00:35:861").ms, GetColor[GC::INDIGOPRIDE], GetColor[GC::FOREST]);
		Config::I()->SwitchSpriteColor(bg, Time("00:37:124").ms, Time("00:38:387").ms, GetColor[GC::CLOUD], GetColor[GC::SPIDERMANBLUE], Config::I()->mspb, Config::I()->mspb);
		bg->Color(Time("00:39:335").ms, Time("00:39:650").ms, GetColor[GC::CLOUD], GetColor[GC::MAROON]);
		Config::I()->SwitchSpriteColor(bg, Time("00:40:914").ms, Time("00:42:177").ms, GetColor[GC::ICE], GetColor[GC::MAROON], Config::I()->mspb, Config::I()->mspb);
	}

	std::vector<Time> jitteries = std::vector<Time>({
		// Trill
		Time("00:33:650"),
		Time("00:33:729"),
		Time("00:33:808"),
		Time("00:33:887"),
		Time("00:33:966"),

		Time("00:34:282"),

		Time("00:34:598"),

		// Trill
		Time("00:34:914"),
		Time("00:34:993"),
		Time("00:35:071"),
		Time("00:35:150"),
		Time("00:35:229"),

		Time("00:35:545"),

		Time("00:35:861"),

		// Trill
		Time("00:36:177"),
		Time("00:36:256"),
		Time("00:36:335"),
		Time("00:36:414"),
		Time("00:36:493"),

		Time("00:36:808"),

		// Voice section
		Time("00:37:124"),
		Time("00:37:282"),
		Time("00:37:440"),
		Time("00:37:598"),
		Time("00:37:756"),
		Time("00:37:914"),
		Time("00:38:071"),
		Time("00:38:229"),
		Time("00:38:387"),

		Time("00:38:703"),

		Time("00:39:019"),

		Time("00:39:335"),

		Time("00:39:650"),

		// Trill
		Time("00:39:966"),
		Time("00:40:045"),
		Time("00:40:124"),
		Time("00:40:203"),

		// Voice
		Time("00:40:282"),
		Time("00:40:361"),
		Time("00:40:440"),
		Time("00:40:519"),
		Time("00:40:598"),
		Time("00:40:756"),
		Time("00:40:914"),
		Time("00:41:071"),
		Time("00:41:229"),
		Time("00:41:387"),
		Time("00:41:545"),
		Time("00:41:703"),
		Time("00:41:861"),
		Time("00:42:019"),
		Time("00:42:177")
	});

	std::string bgPath = "Storyboard\\Background\\Pattern.png";
	std::string bgPathSpacing = "Storyboard\\Background\\PatternSpacing.png";
	Time startSong = Time("00:01:756");
	Time endThirdSpeedup = Time("00:21:966");
	Time startMoire = Time("00:23:229");
	Time startFadeEnd = Time("00:42:177");
	Time jitteryStart = Time("00:33:335");
	Time jitteryEnd = Time("00:42:177");
	Time endMoire = Time("00:43:440");
	// Seems good Kappa
	Vector2 moveOffset = Vector2(0, 7) * Config::I()->patternScale / 2;

public:
	PhaseMoireSpin() {
		Sprite* bg = new Sprite(bgPathSpacing, Vector2::Zero - moveOffset, Layer::Background);
		SetupBackground(bg);
		bg->Fade(endThirdSpeedup.ms, endThirdSpeedup.ms, 0.0f, 1.0f, Easing::CubicIn);
		bg->Fade(Time("00:42:177").ms, Time("00:43:440").ms, 1.0f, 0.05f, Easing::CubicOut);
		bg->Fade(Time("00:43:440").ms, Time("01:03:650").ms, 0.05f, 1.0f, Easing::CubicIn);
		bg->Fade(Time("01:03:650").ms, Time("01:03:650").ms, 1.0f, 0.0f);

		// Lyrics tunnel for pattern
		Config::I()->SwitchSpriteColor(bg, Time("00:53:545").ms, Time("00:54:493").ms, GetColor[GC::FAKEINDIGO], bg->color, Config::I()->mspb / 2, Config::I()->mspb / 2);
		Config::I()->SwitchSpriteColor(bg, Time("00:54:808").ms, Time("00:55:756").ms, GetColor[GC::FLUFFPINK], bg->color, Config::I()->mspb / 2, Config::I()->mspb / 2);
		Config::I()->SwitchSpriteColor(bg, Time("00:58:598").ms, Time("00:59:545").ms, GetColor[GC::ANGRYBLUE], bg->color, Config::I()->mspb / 2, Config::I()->mspb / 2);
		Config::I()->SwitchSpriteColor(bg, Time("00:59:861").ms, Time("01:00:808").ms, GetColor[GC::WARNING], bg->color, Config::I()->mspb / 2, Config::I()->mspb / 2);

		// Note we need the moveOffset... I think(?).
		// I think what's going on is that because the midpoint of an equilateral triangle is not
		// its rotational center, we have to do some minor hacks like this in order to get rotation
		// correct.
		Sprite* pattern = new Sprite(bgPathSpacing, Vector2::Zero - moveOffset, Layer::Background);
	 	SetupBackground(pattern);
		pattern->Fade(Time("00:21:966").ms, Time("00:23:229").ms, 0.0f, 1.0f);

		// muh cubic
		pattern->Rotate(startMoire.ms, jitteryStart.ms, pattern->rotation, 2 * M_PI, Easing::SineIn);

		float finalRotAmount = M_PI / 2;
		float remainingRot = 2 *  M_PI - finalRotAmount;
		float discRot = remainingRot / jitteries.size();
		for (int i = 0; i < jitteries.size(); ++i) {
			if (i == 0) {
				pattern->Rotate(jitteryStart.ms, jitteries[i].ms, pattern->rotation, pattern->rotation + discRot, Easing::CubicIn);
			}
			else {
				pattern->Rotate(jitteries[i - 1].ms, jitteries[i].ms, pattern->rotation, pattern->rotation + discRot, Easing::CubicIn);
			}
		}
		pattern->Rotate(jitteryEnd.ms, endMoire.ms, pattern->rotation, pattern->rotation + finalRotAmount, Easing::SineOut);
		pattern->Fade(Time("00:42:177").ms, Time("00:43:440").ms, 1.0f, 0.0f, Easing::CubicOut);
	}
};

#endif//PHASEMOIRESPIN_HPP