#include "Config.hpp"
#include "TetLines.hpp"
#include "TetPoints.hpp"
#include "Tetrahedron.hpp"

std::string Tetrahedron::linePath = R"(Storyboard\3D\line.png)";

Tetrahedron::Tetrahedron(float radius, Vector3 midpoint)
	: radius(radius),
	  points(TetPoints::Count),
	  lines(TetLines::Count) {
	// Lowering the peak because it looks more equilateral
	points[TetPoints::F] = midpoint + Vector3(0, radius * peakFraction, 0);
	// Lowering the center to fix rotation
	points[TetPoints::C] = midpoint;

	// mfw I can't just use far because of Windows' header define
	Vector3 farVector = midpoint + Vector3(0, radius, 0);

	Vector3 top = farVector.RotateX(Config::I()->DToR(120));
	points[TetPoints::T] = top;

	Vector3 right = top.RotateY(Config::I()->DToR(120));
	points[TetPoints::R] = right;

	Vector3 left = top.RotateY(Config::I()->DToR(-120));
	points[TetPoints::L] = left;

	Move(Vector3(0, radius - radius * peakFraction, 0));

	// I tried doing this in the vector constructor in the member initializer
	// but then realized it had the same line Sprite pointer
	for (int i = 0; i < TetLines::Count; ++i) {
		lines[i] = new Sprite(linePath, Vector2::Midpoint, Layer::Foreground, Origin::CentreLeft);
	}
}

void Tetrahedron::Move(Vector3 pos) {
	Vector3 dist = pos - points[TetPoints::C];
	for (auto& point : points) {
		point += dist;
	}
}

void Tetrahedron::RotateAround(Vector3 pivot, float rot) {
	for (auto& point : points) {
		point = point.RotateAround(pivot, rot);
	}
}

void Tetrahedron::Rotate(float rotX, float rotY, float rotZ) {
	for (auto& point : points) {
		point = point.Rotate(rotX, rotY, rotZ);
	}
}

void Tetrahedron::RotateX(float rotX) {
	Rotate(rotX, 0.0f, 0.0f);
}

void Tetrahedron::RotateY(float rotY) {
	Rotate(0.0f, rotY, 0.0f);
}

void Tetrahedron::RotateZ(float rotZ) {
	Rotate(0.0f, 0.0f, rotZ);
}

void Tetrahedron::Scale(float sca) {
	// Run into problems if sca is 0 because
	// then all the points will be at center and
	// we can no longer normalize and get directions.
	
	// Let's be honest this is pretty bad but
	// this won't affect how this function looks outside.
	// The better solution is probably adjusting scale
	// inside of repositionLines or something. idk
	if (sca == 0) {
		sca = Config::I()->reallySmallNumber;
	}

	Vector3 distToCenter = points[TetPoints::C];
	for (int i = 0; i < points.size(); ++i) {
		if (i != TetPoints::C) {
			Vector3 setToCenter = points[i] - distToCenter;
			Vector3 normalize = setToCenter.Normalize();
			Vector3 scaled;
			if (i == TetPoints::F) {
				scaled = normalize * radius * peakFraction * sca;
			}
			else {
				scaled = normalize * radius * sca;
			}
			points[i] = scaled + distToCenter;
		}
	}
}

// Just moves far point
void Tetrahedron::ScaleVector(float sca) {
	if (sca == 0) {
		sca = Config::I()->reallySmallNumber;
	}

	Vector3 dist = points[TetPoints::F] - points[TetPoints::C];
	Vector3 normalize = dist.Normalize();
	Vector3 scaled = normalize * radius * peakFraction * sca;
	points[TetPoints::F] = points[TetPoints::C] + scaled;
}

void Tetrahedron::Fade(Range time, float startFloat, float endFloat) {
	for (auto& line : lines) {
		line->Fade(time.start, time.end, startFloat, endFloat);
	}
}

void Tetrahedron::Color(Range time, ::Color startColor, ::Color endColor) {
	for (auto& line : lines) {
		line->Color(time.start, time.end, startColor, endColor);
	}
}

void Tetrahedron::RepositionLines(Range time) {
	// Apply perspective
	Vector2 top = applyPerspective(points[TetPoints::T]);
	Vector2 left = applyPerspective(points[TetPoints::L]);
	Vector2 right = applyPerspective(points[TetPoints::R]);
	Vector2 farVector = applyPerspective(points[TetPoints::F]);
	
	repositionLine(time, lines[TetLines::FL], farVector, left);
	repositionLine(time, lines[TetLines::FR], farVector, right);
	repositionLine(time, lines[TetLines::FT], farVector, top);
	repositionLine(time, lines[TetLines::LR], left, right);
	repositionLine(time, lines[TetLines::RT], right, top);
	repositionLine(time, lines[TetLines::TL], top, left);
}

Vector2 Tetrahedron::applyPerspective(Vector3 vec) {
	return vec.Perspect(Config::I()->cameraZ, Config::I()->projectionDistance);
}

void Tetrahedron::repositionLine(Range time, Sprite* line, Vector2 left, Vector2 right) {
	Vector2 prevRot = Vector2(line->rotation);
	Vector2 between = right - left;
	float rot = prevRot.AngleBetween(between);
	float totalRot = line->rotation + rot;
	line->Rotate(time.start, time.end, line->rotation, totalRot);

	float distance = between.Magnitude();
	Vector2 scaleVector(distance / Config::I()->lineWidth, Config::I()->lineScaleHeight);
	line->ScaleVector(time.start, time.end, line->scaleVector, scaleVector);

	line->Move(time.start, time.end, line->position, left);
}