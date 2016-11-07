#ifndef PHASETETRAHEDRONSPIN_HPP
#define PHASETETRAHEDRONSPIN_HPP

#include "Config.hpp"
#include <deque>

class PhaseTetrahedronSpin {
private:
	float totalRot = M_PI * 10;
	// Discrete chunks per second
	float discPerSec = 20;
	float msPerDisc = 1000.0f / discPerSec;

	float radius = 50.0f;
	Time startSpin = Time("01:03:650");
	Time endSpin = Time("01:23:861");
	float scaleSmall = 1.0f;
	float scaleLarge = 2.0f;
	float scaleEnd = 1.5f;

	int offset = Config::I()->offset * 2;

public:
	PhaseTetrahedronSpin() {
		Tetrahedron* cp = new Tetrahedron(radius);
		cp->RotateX(-M_PI / 2);
		cp->RotateY(M_PI);
		cp->Scale(2.0f);
		cp->RepositionLines(Range(startSpin.ms));

		ScaleTimings scaleTimings;
		Config::I()->AddScaleTimings(scaleTimings, Time("01:03:650"), Time("01:13:756"), offset * 4, scaleLarge, scaleSmall);
		Config::I()->AddScaleTimings(scaleTimings, Time("01:13:756"), Time("01:21:335"), offset * 2, scaleLarge, scaleSmall);
		Config::I()->AddScaleTimings(scaleTimings, Time("01:21:335"), Time("01:22:598"), offset, scaleLarge, scaleSmall);
		scaleTimings.push_back(ScaleTiming(endSpin.ms, scaleEnd));

		int numDisc = (endSpin.ms - startSpin.ms) / 1000.0f * discPerSec;
		float discRot = totalRot / numDisc;
		for (int i = 0; i < numDisc; ++i) {
			float startTime = startSpin.ms + i * msPerDisc;
			float endTime = startSpin.ms + (i + 1) * msPerDisc;
			if (i == 403) {
				int test = 2;
			}
			float scale = Config::I()->GetScale(scaleTimings, endTime);

			cp->RotateAround(Vector3(-1, -1, -1), discRot);
			cp->Scale(scale);
			cp->RepositionLines(Range(startTime, endTime));
		}

		cp->Color(Range(startSpin.ms), GetColor[GC::WARNING], GetColor[GC::WARNING]);
		cp->Color(Time("01:06:177").ms - Config::I()->mspb, Time("01:06:177").ms, cp->lines[0]->color, GetColor[GC::BABYGREEN]);
		cp->Color(Time("01:08:703").ms - Config::I()->mspb, Time("01:08:703").ms, cp->lines[0]->color, GetColor[GC::STEELBLUE]);
		cp->Color(Time("01:09:966").ms - Config::I()->mspb, Time("01:09:966").ms, cp->lines[0]->color, GetColor[GC::COUPLEMONTHSWORNBASKETBALLORANGE]);
		cp->Color(Time("01:11:229").ms - Config::I()->mspb, Time("01:11:229").ms, cp->lines[0]->color, GetColor[GC::ALIENWARE]);
		cp->Color(Time("01:12:493").ms - Config::I()->mspb, Time("01:12:493").ms, cp->lines[0]->color, GetColor[GC::GOLDENGATERED]);
		for (auto sprite : cp->lines) {
			Config::I()->SwitchSpriteColor(sprite, Time("01:13:756").ms, Time("01:15:019").ms, GetColor[GC::SANDPAPER], GetColor[GC::BRUISE], Config::I()->mspb / 2, Config::I()->mspb / 2);
			Config::I()->SwitchSpriteColor(sprite, Time("01:16:282").ms, Time("01:17:545").ms, GetColor[GC::MOSSYAQUARIUM], GetColor[GC::SUICIDEAD], Config::I()->mspb / 2, Config::I()->mspb / 2);
			Config::I()->SwitchSpriteColor(sprite, Time("01:18:808").ms, Time("01:20:071").ms, GetColor[GC::SADNESS], GetColor[GC::HAPPYNESS], Config::I()->mspb, Config::I()->mspb);
			Config::I()->SwitchSpriteColor(sprite, Time("01:20:229").ms, Time("01:21:335").ms, GetColor[GC::HAPPYNESS], GetColor[GC::SADNESS], Config::I()->mspb / 2, Config::I()->mspb / 2);
			Config::I()->SwitchSpriteColor(sprite, Time("01:21:414").ms, Time("01:22:598").ms, GetColor[GC::HAPPYNESS], GetColor[GC::SADNESS], Config::I()->mspb / 4, Config::I()->mspb / 4);
		}
	}
};

#endif//PHASETETRAHEDRONSPIN_HPP