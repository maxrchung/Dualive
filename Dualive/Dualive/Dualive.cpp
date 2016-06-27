#include "Config.hpp"
#include "Time.hpp"
#include "PhaseTitle.hpp"
#include "Storyboard.hpp"
#include <iostream>

int main() {
	PhaseTitle phaseTitle;


	Storyboard::Instance()->Write(Config::I()->storyboardPath);
	//std::cin.get();
	return 0;
}