#include "Config.hpp"
#include <iostream>

int main() {
	std::cout << Config::Get("asdf") << std::endl;
	std::cin.get();
	return 0;
}