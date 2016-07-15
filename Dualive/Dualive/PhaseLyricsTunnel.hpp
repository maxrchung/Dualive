#ifndef PHASELYRICSTUNNEL_HPP
#define PHASELYRICSTUNNEL_HPP

#include "Phase.hpp"

class PhaseLyricsTunnel : public Phase {
private:
	// Utility function for grabbing number of files from a directory
	// Seems like Windows only. May incorporate this into OsuukiSB if I can
	// see some more uses for directory stuff. So far, I've only really
	// used this
	int getImagesCount(std::string directory, std::string extension) {
		WIN32_FIND_DATAA fd;
		std::string inputDirectorySearch = directory + extension;
		HANDLE hFind = FindFirstFileA(inputDirectorySearch.c_str(), &fd);
		int imagesCount = 0;

		do {
			++imagesCount;
		} while (FindNextFileA(hFind, &fd));
		FindClose(hFind);

		return imagesCount;
	}

	std::vector<Sprite*> loadLyrics(std::string exactDirectory, std::string localDirectory) {
		int imagesCount = getImagesCount(exactDirectory, "*.png");
		std::vector<Sprite*> lyrics(imagesCount);

		// Go from back to forwards because of layer ordering
		for (int i = imagesCount - 1; i >= 0; --i) {
			Sprite* sprite = new Sprite(localDirectory + std::to_string(i) + ".png");
			// For conveniency sake, we reverse the order again
			lyrics[i] = sprite;
		}

		return lyrics;
	}

	std::string lyricsExactDirectory = R"(C:\Users\Wax Chug da Gwad\AppData\Local\osu!\Songs\Quarks_Dualive_SDVX_NOFX\Storyboard\LyricsTunnel\)";
	std::string lyricsLocalDirectory = R"(Storyboard\LyricsTunnel\)";

public:
	PhaseLyricsTunnel() {
		std::vector<Sprite*> lyrics = loadLyrics(lyricsExactDirectory, lyricsLocalDirectory);
	}
};


#endif//PHASELYRICSTUNNEL_HPP