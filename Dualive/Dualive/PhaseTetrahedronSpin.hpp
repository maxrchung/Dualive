#ifndef PHASETETRAHEDRONSPIN_HPP
#define PHASETETRAHEDRONSPIN_HPP

#include "Config.hpp"

class PhaseTetrahedronSpin {
private:
	float totalRot = M_PI * 10;
	// Discrete chunks per second
	float discPerSec = 20;
	float msPerDisc = 1000.0f / discPerSec;

	float radius = 50.0f;
	Time startSpin = Time("01:03:650");
	Time endSpin = Time("01:23:861");
public:
	PhaseTetrahedronSpin() {
		Tetrahedron* cp = new Tetrahedron(radius);
		cp->RotateX(-M_PI / 2);
		cp->Scale(2.0f);
		cp->RepositionLines(Range(startSpin.ms));

		int numDisc = (endSpin.ms - startSpin.ms) / 1000.0f * discPerSec;
		float discRot = totalRot / numDisc;
		for (int i = 0; i < numDisc; ++i) {
			float startTime = startSpin.ms + i * msPerDisc;
			float endTime = startSpin.ms + (i + 1) * msPerDisc;

			cp->RotateAround(Vector3(1, 1, 1), discRot);
			cp->RepositionLines(Range(startTime, endTime));
		}
	}
};

#endif//PHASETETRAHEDRONSPIN_HPP