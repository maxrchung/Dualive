#include "MusicAnalysis.hpp"

int main() {
	MusicAnalysisConfig config;
	std::string musicPath(R"(X:\Music\kradness & Camellia\SDVX Dualive No FX\Quarks_Dualive_SDVX_NOFX - Left Channel.wav)");
	std::string dataPath(R"(C:\Users\Wax Chug da Gwad\Desktop\Dualive\Dualive\Debug\MusicAnalysisData.txt)");
	config.musicPath = musicPath;
	config.dataPath = dataPath;
	config.divisions = 16;
	config.freqBandStart = 50;
	config.freqBandEnd = 18000;
	config.snapshotRate = 100;

	MusicAnalysis anal(config);
	// std::cin.get();
}