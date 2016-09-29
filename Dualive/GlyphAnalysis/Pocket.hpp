#ifndef POCKET_HPP
#define POCKET_HPP

#include "Vector2.hpp"
#include <unordered_set>
#include <vector>

// Holds together a bunch of close points
// Calculates average 
class Pocket {
public:
	typedef std::pair<Vector2, Vector2> Pair;

	Pocket();
	Pocket(Vector2 vector);

	// Points
	std::unordered_set<Vector2> points;
	// Surrounding pockets
	std::unordered_set<Pocket*> pockets;
	Vector2 average;

	static void CalculateAverage(Pocket* pocket);

	static float cutOffDistance;
	static void AddPockets(std::unordered_set<Pocket*>& pockets, Pair pair);

private:
	static Pocket* addVectorToPocket(std::unordered_set<Pocket*>& pockets, Vector2 vector);
	static void connectPockets(Pocket* firstPocket, Pocket* secondPocket);
};

#endif//POCKET_HPP