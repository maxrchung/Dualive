#ifndef GETCOLOR_HPP
#define GETCOLOR_HPP

#include "Color.hpp"
#include <string>
#include <unordered_map>

enum class GC {
	PINK,
	CYAN,
	GREEN,
	NAVY,
	PURPLE,
	YELLOW,
	ORANGE,
	WHITE,
	BLACK,
	BLUE,
	SUNLIGHT
};

extern std::unordered_map<GC, Color> GetColor;

#endif//GETCOLOR_HPP