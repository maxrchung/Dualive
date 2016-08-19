#ifndef PHASETETRAHEDRONSPIN_HPP
#define PHASETETRAHEDRONSPIN_HPP

#include "Config.hpp"
#include <deque>

typedef std::deque<std::pair<int, float>> ScaleTimings;
typedef std::pair<int, float> ScaleTiming;

class PhaseTetrahedronSpin {
private:
	float totalRot = M_PI * 10;
	// Discrete chunks per second
	float discPerSec = 20;
	float msPerDisc = 1000.0f / discPerSec;

	float radius = 50.0f;
	Time startSpin = Time("01:03:650");
	Time endSpin = Time("01:23:861");
	float scaleSmall = 1.5f;
	float scaleLarge = 2.0f;

	int offset = Config::I()->offset * 2;

	void addScaleTimings(ScaleTimings scaleTimings, Time timeStart, Time timeEnd, float freq) {
		for (int i = timeStart.ms; i < timeEnd.ms; i += freq) {
			scaleTimings.push_back(ScaleTiming(i - offset, scaleLarge));
			scaleTimings.push_back(ScaleTiming(i, scaleSmall));
			scaleTimings.push_back(ScaleTiming(i + offset, scaleLarge));
		}
	}

	float getScale(ScaleTimings scaleTimings) {

	}

public:
	PhaseTetrahedronSpin() {
		Tetrahedron* cp = new Tetrahedron(radius);
		cp->RotateX(-M_PI / 2);
		cp->Scale(2.0f);
		cp->RepositionLines(Range(startSpin.ms));

		ScaleTimings scaleTimings;
		int freq = offset * 2;
		addScaleTimings(scaleTimings, Time("01:03:650"), endSpin, offset * 2);

		int numDisc = (endSpin.ms - startSpin.ms) / 1000.0f * discPerSec;
		float discRot = totalRot / numDisc;
		for (int i = 0; i < numDisc; ++i) {
			float startTime = startSpin.ms + i * msPerDisc;
			float endTime = startSpin.ms + (i + 1) * msPerDisc;

			float scale = getScale(scaleTimings);

			cp->RotateAround(Vector3(1, 1, 1), discRot);
			cp->Scale(scale);
			cp->RepositionLines(Range(startTime, endTime));
		}
	}
};

#endif//PHASETETRAHEDRONSPIN_HPP