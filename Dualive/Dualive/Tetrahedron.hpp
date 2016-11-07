#ifndef TETRAHEDRON_HPP
#define TETRAHEDRON_HPP

#include "Range.hpp"
#include "Vector3.hpp"
#include <vector>

class Tetrahedron {
public:
	Tetrahedron(float radius, Vector3 midpoint = Vector3(0, 0, 0));
	void Move(Vector3 pos);
	void RotateAround(Vector3 pivot, float rot);
	void Rotate(float rotX, float rotY, float rotZ);
	void RotateX(float rotX);
	void RotateY(float rotY);
	void RotateZ(float rotZ);
	void Scale(float sca);
	void ScaleVector(float sca);

	// Calling move, rotate, or scale changes the points' positions.
	// Because it is likely that you may want to call multiple
	// position-altering commands in sequence, you do not want to have
	// a juttery effect where the sprites move awkwardly as each
	// method is called. To combat this, we call RepositionLines
	// when you are ready to update the actual 2D sprite positions.
	// This function calls the helper function repositionLine which
	// does most of the dirty work.
	void RepositionLines(Range time, Easing easing = Easing::Linear);

	// Color and Fade behave differently than the above functions
	// because they are not concerned with the Sprite lines' positions
	void Fade(Range time, float startFloat, float endFloat, Easing easing = Easing::Linear);
	void Color(Range time, Color startColor, Color endColor, Easing easing = Easing::Linear);
	void Color(Time startTime, Time endTime, ::Color startColor, ::Color endColor, Easing easing = Easing::Linear);

	std::vector<Vector3> points;
	std::vector<Sprite*> lines;

private:
	static std::string linePath;
	float radius;
	// How far away the far point should be
	float peakFraction = 2.0f / 3;

	Vector2 applyPerspective(Vector3 vec);
	// Rerranges sprites after a Move/Rotate/Scale command
	void repositionLine(Range time, Sprite* line, Vector2 start, Vector2 end, Easing easing = Easing::Linear);
};

#endif//TETRAHEDRON_HPP