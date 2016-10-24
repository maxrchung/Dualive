#ifndef RECTPOINTS_HPP
#define RECTPOINTS_HPP

#include "Config.hpp"

class RectPoints {
public:
	RectPoints() {}
	RectPoints(std::vector<Pair3>& pairs);
	
	void Move(Vector3 movement);
	void Rotate(float xRot, float yRot, float zRot);
	void Rotate(Vector3 rotAmounts);
	void LocalRotate(float xRot, float yRot, float zRot);
	bool Collide(RectPoints& rectPoints);

	// TL, TR, BR, BL, C
	std::vector<Vector3> points;
private:
	void compareVector3(Vector3 vec, Vector2& min, Vector2& max);
	static void findAxisMinMax(Vector3 axis, Vector3 corner, float& min, float& max);
};

#endif//RECTPOINTS_HPP