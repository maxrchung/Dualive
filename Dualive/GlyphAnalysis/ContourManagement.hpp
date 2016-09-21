#ifndef CONTOURMANAGEMENT_HPP
#define CONTOURMANAGEMENT

#include "DecomposedValue.hpp"
#include <vector>
#include <unordered_map>

// Most likely obsolete class, but I may potentially need this again
class ContourManagement {
public:
	ContourManagement(std::unordered_map<int, std::vector<int>>& onPoints)
		: onPoints(onPoints) {}
	std::unordered_map<int, std::vector<int>> onPoints;
	std::vector<Contour> contours;
};

#endif//CONTOURMANAGEMENT