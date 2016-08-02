#ifndef TETRAHEDRON_HPP
#define TETRAHEDRON_HPP

#include "Range.hpp"
#include "Vector3.hpp"
#include <vector>

class Tetrahedron {
public:
	Tetrahedron(float radius, Vector3 midpoint = Vector3(0, 0, 0));
	void Move(Range time, Vector3 pos);
	void RotateAround(Range time, Vector3 pivot, float rot);
	void Rotate(Range time, float rotX, float rotY, float rotZ);
	void RotateX(Range time, float rotX);
	void RotateY(Range time, float rotY);
	void RotateZ(Range time, float rotZ);
	void Scale(Range time, float sca);

	// Color and Fade behave differently than the above functions
	// because they affect the Sprite lines directly
	void Fade(Range time, float startFloat, float endFloat);
	void Color(Range time, Color startColor, Color endColor);

	static std::string linePath;

	std::vector<Vector3> points;
	std::vector<Sprite*> lines;
	float radius;

private:
	Vector2 applyPerspective(Vector3 vec);
	// Rerranges sprites after a Move/Rotate/Scale command
	void repositionLines(Range time);
	void repositionLine(Range time, Sprite* line, Vector2 start, Vector2 end);
};

#endif//TETRAHEDRON_HPP