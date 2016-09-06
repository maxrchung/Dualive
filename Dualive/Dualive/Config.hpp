#ifndef CONFIG_HPP
#define CONFIG_HPP

#define CONFIGPATH R"(C:\Users\Wax Chug da Gwad\Desktop\Dualive\Dualive\Dualive\config.txt)"

#include "MusicAnalysis.hpp"
#include "Sprite.hpp"
#include "Tetrahedron.hpp"
#include "Time.hpp"
#include "Vector2.hpp"
#include <algorithm>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <winsock.h>

class Config {
public:
	static Config* I();

	// Convert degrees to radians
	float DToR(int degrees);

	Vector2 GetImageSize(const std::string& path);

	Time GetClosestTime(Time time);

	// Background dimensions
	Vector2 bgDims = Vector2(853.0f, 480.0f);

	// Kappa
	float reallySmallNumber = 0.00001f;

	// BPM
	float bpm = 190.0f;
	float mpb = 1 / bpm;
	float spb = mpb * 60;
	// ~316 ms per beat
	float mspb = 1000 * spb;
	float offset = mspb / 4;

	// Camera
	float cameraZ = 500.0f;
	float projectionDistance = 400.0f;

	// Scaling
	float patternScale = 0.35f;
	float lineWidth = 1000.0f;
	float lineScaleHeight = 0.1f;

	// Paths
	std::string beatmapDirectory = R"(C:\Users\Wax Chug da Gwad\AppData\Local\osu!\Songs\Quarks_Dualive_SDVX_NOFX\)";
	std::string dataPath = R"(C:\Users\Wax Chug da Gwad\Desktop\Dualive\Dualive\Debug\MusicAnalysisData.txt)";
	std::string storyboardPath = R"(C:\Users\Wax Chug da Gwad\AppData\Local\osu!\Songs\Quarks_Dualive_SDVX_NOFX\Quarks - Dualive (Osuuki).osb)";

	// MusicAnalysisData
	MusicAnalysisData data = MusicAnalysis::LoadData(dataPath);

	// Times
	Time songStart = Time("00:00:000");
	Time songEnd = Time("02:07:985");

private:
	static Config* instance;
	Config() {};
	Config(const Config&) {};
	Config& operator=(const Config&) {};
};

#endif//CONFIG_HPP