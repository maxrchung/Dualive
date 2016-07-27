#include "Config.hpp"
#include "TetPoints.hpp"
#include "Tetrahedron.hpp"

float Tetrahedron::cameraZ = 3.0f;
float Tetrahedron::projectionDistance = 3.0f;
std::string Tetrahedron::linePath = R"(Storyboard\3D\line.png)";

Tetrahedron::Tetrahedron(float radius, Vector3 midpoint)
	: radius(radius),
	  points(TetPoints::Count),
	  lines(TetPoints::Count, new Sprite(linePath, Vector2::Midpoint, Layer::Foreground, Origin::CentreLeft)) {
	points[TetPoints::C] = midpoint;

	// mfw I can't just use far because of Windows' header define
	Vector3 farVector = midpoint + Vector3(0, radius, 0);
	points[TetPoints::F] = farVector;

	Vector3 top = farVector.RotateY(Config::DToR(120));
	points[TetPoints::T] = top;

	Vector3 right = top.RotateX(Config::DToR(120));
	points[TetPoints::R] = right;
}

void Tetrahedron::Move(Range time, Vector3 pos) {
	repositionLines();
}

void Tetrahedron::RotateAround(Range time, Vector3 pivot, float rot) {
	repositionLines();
}

void Tetrahedron::Rotate(Range time, float rotX, float rotY, float rotZ) {
	repositionLines();
}

void Tetrahedron::RotateX(Range time, float rotx) {
	repositionLines();
}

void Tetrahedron::RotateY(Range time, float roty) {
	repositionLines();
}

void Tetrahedron::RotateZ(Range time, float rotz) {
	repositionLines();
}

void Tetrahedron::Scale(Range time, float sca) {
	repositionLines();
}

std::vector<Vector2> Tetrahedron::repositionLines() {

}
