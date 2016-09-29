#ifndef NODE_HPP
#define NODE_HPP

#include "Vector2.hpp"
#include <set>
#include <vector>

class Node {
public:
	Node() {};
	Node(Vector2 point) : point(point) {}
	Vector2 point;
	// Surrounding nodes
	std::set<Node*> nodes;
};

#endif//NODE_HPP