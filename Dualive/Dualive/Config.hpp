#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <map>

class Config {
public:
	static std::string Get(std::string key);
private:
	static Config* instance;
	void load();
	std::map<std::string, std::string> vars;
	Config() {};
	Config(const Config&) {};
	Config& operator=(const Config&) {};
};

#endif//CONFIG_HPP