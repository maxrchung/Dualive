#include "Config.hpp"
#include <iostream>
#include <fstream>

#define CONFIGPATH R"(C:\Users\Wax Chug da Gwad\Desktop\Dualive\Dualive\Dualive\config.txt)"

Config* Config::instance = NULL;
void Config::load() {
	std::ifstream input(CONFIGPATH);
	std::string var;
	std::string value;
	while (input >> var >> value) {
		if (var.substr(0, 2) != "//") {
			vars.insert(std::pair<std::string, std::string>(var, value));
		}
	}
}

std::string Config::Get(std::string key) {
	if (instance == NULL) {
		instance = new Config;
		instance->load();
	}
	return instance->vars.at(key);
}