#include "Config.hpp"
#include "PhaseLineBackground.hpp"
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

	Sprite* triangle = new Sprite("triangle.png", Vector2::Zero, Layer::Background);
	triangle->Scale(0, 0, 2.7428f, 2.7428f);
	triangle->Fade(0, Time("00:01:756").ms, 1.0f, 1.0f);
	triangle->Fade(Time("00:01:756").ms, Time("00:01:756").ms, 0.0f, 0.0f);
	triangle->Fade(Time("02:05:545").ms, Time("02:07:988").ms, 1.0f, 1.0f);

	Sprite* bg = new Sprite("Storyboard\\Background\\Blank.png", Vector2::Zero, Layer::Background);
	bg->ScaleVector(0, 0, Vector2::ScreenSize, Vector2::ScreenSize);
	bg->Color(0, 0, GetColor[GC::CYAN], GetColor[GC::CYAN]);
	bg->Fade(0, Time("00:01:756").ms, 0.0f, 1.0f, Easing::CubicIn);
	Config::I()->SwitchSpriteColor(bg, Time("00:27:019").ms, Time("00:28:282").ms, GetColor[GC::MUSTARD], GetColor[GC::CYAN], Config::I()->mspb, Config::I()->mspb);
	Config::I()->SwitchSpriteColor(bg, Time("00:30:808").ms, Time("00:33:335").ms, GetColor[GC::CHEWEDBUBBLEGUM], GetColor[GC::MUSTARD], Config::I()->mspb, Config::I()->mspb);
	bg->Color(Time("00:34:282").ms, Time("00:34:598").ms, GetColor[GC::CHEWEDBUBBLEGUM], GetColor[GC::LEMONGRASS]);
	bg->Color(Time("00:35:545").ms, Time("00:35:861").ms, GetColor[GC::LEMONGRASS], GetColor[GC::TURQUOISE]);
	Config::I()->SwitchSpriteColor(bg, Time("00:37:124").ms, Time("00:38:387").ms, GetColor[GC::PEACH], GetColor[GC::SPIDERMANRED], Config::I()->mspb, Config::I()->mspb);
	bg->Color(Time("00:39:335").ms, Time("00:39:650").ms, GetColor[GC::PEACH], GetColor[GC::MUSTARD]);
	Config::I()->SwitchSpriteColor(bg, Time("00:40:914").ms, Time("00:42:177").ms, GetColor[GC::BURGANDY], GetColor[GC::MUSTARD], Config::I()->mspb, Config::I()->mspb);
	bg->Color(Time("01:22:598").ms, Time("01:23:861").ms, bg->color, GetColor[GC::HAPPYNESS]);

	bg->Color(Time("01:23:861").ms, Time("01:26:387").ms, bg->color, GetColor[GC::AQUAMARINE]);
	bg->Color(Time("01:26:387").ms, Time("01:28:914").ms, bg->color, GetColor[GC::PARADENIGHT]);
	bg->Color(Time("01:28:914").ms, Time("01:31:440").ms, bg->color, GetColor[GC::COALMINE]);
	bg->Color(Time("01:31:440").ms, Time("01:33:966").ms, bg->color, GetColor[GC::TENSIONSENVELOPMENT]);
	Config::I()->SwitchSpriteColor(bg,
		Time("01:33:966").ms, Time("01:36:493").ms - Config::I()->mspb * 2,
		GetColor[GC::TENSIONSENVELOPMENT], GetColor[GC::THELIGHTOFSPACE],
		Config::I()->mspb * 2, Config::I()->mspb * 2);

	Config::I()->SwitchSpriteColor(bg,
		Time("01:36:493").ms, Time("01:39:019").ms - Config::I()->mspb,
		GetColor[GC::LIPSTICK], GetColor[GC::THELIGHTOFSPACE],
		Config::I()->mspb * 2, Config::I()->mspb * 2);

	Config::I()->SwitchSpriteColor(bg,
		Time("01:39:019").ms, Time("01:40:282").ms - Config::I()->mspb / 2,
		GetColor[GC::URANUSDEATH], GetColor[GC::LIPSTICK],
		Config::I()->mspb / 2, Config::I()->mspb / 2);

	Config::I()->SwitchSpriteColor(bg,
		Time("01:40:282").ms, Time("01:42:177").ms,
		GetColor[GC::URANUSDEATH], GetColor[GC::LIPSTICK],
		Config::I()->mspb / 4, Config::I()->mspb / 4);
	bg->Color(Time("01:42:177").ms, Time("01:43:440").ms, bg->color, GetColor[GC::LIPSTICK]);

	int backgroundColor = (int)GC::GREENPASTURE;
	auto& timings = PhaseTextGeneration::timings;
	for (int i = 1; i < timings.size(); ++i) {
		bg->Color(timings[i].ms - Config::I()->mspb, timings[i].ms, bg->color, GetColor[(GC)backgroundColor], Easing::CubicIn);
		backgroundColor += 2;
	}

	bg->Fade(Time("02:05:545").ms, Time("02:06:808").ms, bg->fade, 0.0f, Easing::CubicIn);

	std::cout << "PhaseSpectrum2D..." << std::endl; PhaseSpectrum2D phaseSpectrum2D;
	std::cout << "PhaseMoireGeneration..." << std::endl; PhaseMoireGeneration phaseMoireGeneration;
	std::cout << "PhaseLineBackground..." << std::endl; PhaseLineBackground phaseLineBackground;
	std::cout << "PhaseMoireSpin..." << std::endl; PhaseMoireSpin phaseMoireSpin;

	Sprite* spotlight = new Sprite("Storyboard\\Background\\Fade.png", Vector2::Zero, Layer::Background);
	spotlight->Scale(Time("01:22:598").ms, Time("01:22:598").ms, 0.45f, 0.45f);
	spotlight->Fade(Time("01:22:598").ms, Time("01:22:598").ms, 0.0f, 1.0f);
	spotlight->Fade(Time("01:22:598").ms, Time("01:23:861").ms, 0.75f, 1.0f, Easing::CubicIn);
	spotlight->Fade(Time("02:05:545").ms, Time("02:06:808").ms, spotlight->fade, 0.0f, Easing::CubicIn);

	Sprite* cover = new Sprite("Storyboard\\Background\\Blank.png", Vector2::Zero, Layer::Background);
	cover->ScaleVector(0, 0, Vector2::ScreenSize, Vector2::ScreenSize);
	cover->Color(0, 0, Color(0), Color(0));
	float coverFadeMax = 1.0f;
	cover->Fade(0, Time("00:01:756").ms, 0.0f, 0.88f, Easing::CubicOut);
	cover->Fade(Time("00:01:756").ms, Time("00:21:966").ms, cover->fade, 0.0f, Easing::CubicIn);
	cover->Fade(Time("00:43:440").ms, Time("01:03:650").ms, 0.0f, coverFadeMax);
	cover->Fade(Time("01:03:650").ms, Time("01:23:861").ms, cover->fade, 0.0f);

	std::cout << "PhaseLyricsTunnel..." << std::endl; PhaseLyricsTunnel phaseLyricsTunnel;
	std::cout << "PhaseTetrahedronSpin..." << std::endl; PhaseTetrahedronSpin phaseTetrahedronSpin;
	std::cout << "PhaseSpectrum3D..." << std::endl; PhaseSpectrum3D phaseSpectrum3D;
	std::cout << "PhaseTextGeneration..." << std::endl; PhaseTextGeneration phaseTextGeneration;

	Storyboard::Instance()->Write(Config::I()->storyboardPath);
	//std::cin.get();
	return 0;
} 