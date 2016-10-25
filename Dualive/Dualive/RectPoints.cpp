#include "RectPoints.hpp"

RectPoints::RectPoints(std::vector<Pair3>& pairs) {
	// Zzz can't do min/max
	Vector2 minimum(FLT_MAX, FLT_MAX);
	Vector2 maximum(FLT_MIN, FLT_MIN);

	for (auto pair3 : pairs) {
		compareVector3(pair3.first, minimum, maximum);
		compareVector3(pair3.second, minimum, maximum);
	}

	Vector2 half((maximum - minimum) / 2);
	points = {
		Vector3(minimum.x, maximum.y),
		Vector3(maximum.x, maximum.y),
		Vector3(maximum.x, minimum.y),
		Vector3(minimum.x, minimum.y),
		Vector3(minimum.x + half.x,	minimum.y + half.y)
	};
}

void RectPoints::compareVector3(Vector3 vec, Vector2& minimum, Vector2& maximum) {
	if (vec.x < minimum.x)
		minimum.x = vec.x;
	else if (vec.x > maximum.x)
		maximum.x = vec.x;

	if (vec.y < minimum.y)
		minimum.y = vec.y;
	else if (vec.y > maximum.y)
		maximum.y = vec.y;
}

void RectPoints::Move(Vector3 movement) {
	for (auto& v3 : points) {
		v3 += movement;
	}
}

void RectPoints::Rotate(Vector3 rotAmounts) {
	Rotate(rotAmounts.x, rotAmounts.y, rotAmounts.z);
}

void RectPoints::Rotate(float xRot, float yRot, float zRot) {
	for (auto& v3 : points) {
		v3 = v3.Rotate(xRot, yRot, zRot);
	}
}

void RectPoints::LocalRotate(float xRot, float yRot, float zRot) {
	Vector3 center = points[4];
	for (auto& v3 : points) {
		v3 -= center;
		v3 = v3.Rotate(xRot, yRot, zRot);
		v3 += center;
	}
}

bool RectPoints::Collide(RectPoints& rectPoints) {
	// Get points
	std::vector<Vector3> center = points;
	std::vector<Vector3> other = rectPoints.points;

	// Axes
	// Center axes
	std::vector<Vector3> centerAxes = { Vector3(1, 0), Vector3(0, 1), Vector3(0, 0, 1) };
	// Other axes
	std::vector<Vector3> otherAxes = {
		// 0 = TL
		// 1 = TR
		// 2 = BR
		// 3 = BL
		other[1] - other[0],
		other[2] - other[1]
	};
	otherAxes.push_back(otherAxes[0].Cross(otherAxes[1]));

	// Set up all axes
	std::vector<Vector3> axes = centerAxes;
	axes.insert(axes.end(), otherAxes.begin(), otherAxes.end());

	//// Adding in cross product of axes combinations
	//// This is for 3D rectangles only
	//for (auto centerAxis : centerAxes) {
	//	for (auto otherAxis : otherAxes) {
	//		axes.push_back(centerAxis.Cross(otherAxis));
	//	}
	//}

	for (auto axis : axes) {
		float minCenter = center[0].Dot(axis);
		float maxCenter = center[0].Dot(axis);
		for (auto corner : center) {
			findAxisMinMax(axis, corner, minCenter, maxCenter);
		}

		float minOther = other[0].Dot(axis);
		float maxOther = other[0].Dot(axis);
		for (auto corner : other) {
			findAxisMinMax(axis, corner, minOther, maxOther);
		}

		if (minOther > maxCenter || maxOther < minCenter) {
			return false;
		}
	}

	return true;
}

void RectPoints::findAxisMinMax(Vector3 axis, Vector3 corner, float& min, float& max) {
	Vector3 projection = corner.Project(axis);
	float scalar = projection.Dot(axis);
	if (scalar < min) {
		min = scalar;
	}
	if (scalar > max) {
		max = scalar;
	}
}