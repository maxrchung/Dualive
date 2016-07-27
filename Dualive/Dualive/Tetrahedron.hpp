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

	static float cameraZ;
	static float projectionDistance;
	static std::string linePath;

	std::vector<Vector3> points;
	std::vector<Sprite*> lines;
	float radius;

private:
	// Arranges line sprites according to points
	std::vector<Vector2> repositionLines();
};

#endif//TETRAHEDRON_HPP