#ifndef PHASELYRICSTUNNEL_HPP
#define PHASELYRICSTUNNEL_HPP

#include "Config.hpp"

class PhaseLyricsTunnel {
private:
	void setupLyrics(std::vector<Sprite*> lyrics) {
		for (int i = 0; i < lyrics.size(); ++i) {
			Sprite* sprite = lyrics[i];
			
			 // Fade section
			int fadeIndex = i - lyricsOnScreen;
			if (fadeIndex < 0) {
				fadeIndex = 0;
			}

			float startFade = 1 - ((i - fadeIndex) / (float)lyricsOnScreen);
			// Start at 0
			sprite->Color(startTunnel.ms - offset, timings[fadeIndex].ms, Color(0.0f), Color(255) * startFade);
			// Easiest way I can think of to keep track of fade value
			sprite->fade = startFade;

			float startScale = sprite->scale * 
				baseScale * 
				pow(longScaleIncrement, (lyricsOnScreen - ((i - fadeIndex)))) *
				pow(shortScaleIncrement, (lyricsOnScreen - ((i - fadeIndex))));
			sprite->Scale(startTunnel.ms - offset, timings[fadeIndex].ms, 0.0f, startScale);

			// Increment fade at each long step
			for (int j = fadeIndex; j < lyrics.size(); ++j) {
				// Increment if not at max
				if (sprite->fade != 1.0f) {
					float fade = sprite->fade + fadeIncrement;
					if (fade > 1.0f) {
						fade = 1.0f;
					}
					sprite->fade = fade;

					sprite->Color(timings[j].ms, timings[j + 1].ms,	sprite->color, Color(255.0f) * fade);
					sprite->Scale(timings[j].ms, timings[j + 1].ms - offset, sprite->scale, sprite->scale * longScaleIncrement);
					sprite->Scale(timings[j + 1].ms - offset, timings[j + 1].ms, sprite->scale, sprite->scale * shortScaleIncrement);
					
				}
				else {
					break;
				}
			}

			// Fade out
			sprite->Color(timings[i + 1].ms, timings[i + 1].ms + offset, sprite->color, Color(0.0f));
			sprite->Scale(timings[i + 1].ms, timings[i + 1].ms + offset, sprite->scale, sprite->scale * shortScaleIncrement);

			// Set starting rotation
			float startRotation = M_PI - longRotation / 2 - (i * rotationOffset);

			Vector2 startPos = Vector2(cos(startRotation) * spacing, -sin(startRotation) * spacing);
			sprite->Move(startTunnel.ms, startTunnel.ms, startPos, startPos);

			// Flip if origin on right
			// Have to do this after we set movement
			if (sprite->origin == Origin::CentreRight) {
				startRotation += M_PI;
			}
			sprite->Rotate(startTunnel.ms, startTunnel.ms, startRotation, startRotation);

			for (int j = 0; j < lyrics.size(); ++j) {
				spin(sprite, timings[j].ms, timings[j + 1].ms - offset, -longRotation);

				// Don't do fast spin for last lyric
				if (j != lyrics.size() - 1) {
					spin(sprite, timings[j + 1].ms - offset, timings[j + 1].ms, -shortRotation);
				}
			}
		}
	}

	void setupTet(std::vector<Sprite*> lyrics) {
		Tetrahedron* tet = new Tetrahedron(tetRadius);
		tet->RotateX(-M_PI / 2);
		tet->Scale(0.0f);
		tet->RepositionLines(Range(startTunnel.ms - offset));

		Range fadeIn(startTunnel.ms - offset, timings[0].ms);
		tet->Scale(1.0f);
		tet->RepositionLines(fadeIn);
		tet->Fade(fadeIn, 0.0f, 1.0f);

		// Spin tetrahedron
		for (int j = 0; j < lyrics.size(); ++j) {
			Range longRotTime(timings[j].ms, timings[j + 1].ms - offset);
			spinTet(tet, longRotTime, -longRotation);

			// Don't fast spin Tetrahedron for lyric
			if (j != lyrics.size() - 1) {
				Range shortRotTime(timings[j + 1].ms - offset, timings[j + 1].ms);
				spinTet(tet, shortRotTime, -shortRotation);
			}
		}

		Range lastRotTime(timings[lyrics.size()].ms - offset, endTunnel.ms);
		float lastRot = 2 * M_PI / 3 - longRotation;
		spinTet(tet, lastRotTime, -lastRot);

		tet->Scale(2.5f);
		tet->RepositionLines(Range(startExpand.ms - offset / 2, startExpand.ms));

		float endExpand = startExpand.ms + offset / 2;
		tet->Scale(2.0f);
		tet->RepositionLines(Range(startExpand.ms, endExpand));

		// Keep in place till end
		tet->Move(Vector3::Zero);
		tet->RepositionLines(Range(endExpand, startMoire.ms));
	}

	void spin(Sprite* sprite, int startTime, int endTime, float rotation) {
		// Minus because we spin CCW
		sprite->Rotate(startTime, endTime, sprite->rotation, sprite->rotation - rotation);

		float discreteRotation = rotation / discrete;
		float discreteTime = (endTime - startTime) / discrete;
		for (int i = 0; i < discrete; ++i) {
			float startDiscrete = startTime + discreteTime * i;
			float endDiscrete = startTime + discreteTime * (i + 1);
			Vector2 pos = sprite->position.Rotate(-discreteRotation);
			sprite->Move(startDiscrete, endDiscrete, sprite->position, pos);
		}
	}

	void spinTet(Tetrahedron* tet, Range time, float rotation) {
		float discreteRotation = rotation / discrete;
		float discreteTime = (time.end - time.start) / discrete;
		for (int i = 0; i < discrete; ++i) {
			float startDiscrete = time.start + discreteTime * i;
			float endDiscrete = time.start + discreteTime * (i + 1);
			tet->RotateZ(discreteRotation);
			tet->RepositionLines(Range(startDiscrete, endDiscrete));
		}
	}

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
			Origin origin;
			if (i % 2 == 0) {
				origin = Origin::CentreRight;
			}
			else {
				origin = Origin::CentreLeft;
			}
			Sprite* sprite = new Sprite(localDirectory + std::to_string(i) + ".png", Vector2::Zero, Layer::Foreground, origin);
			float width = Config::I()->GetImageSize(exactDirectory + std::to_string(i) + ".png").x;
			float scale = Config::I()->bgDims.x / width;
			if (scale < maxLyricScale) {
				// Probably a bad idea to save temp variables like 
				// this, but this won't mess up timings for scaling
				sprite->scale = scale;
			}
			// Clamp so things don't get too big
			else {
				sprite->scale = maxLyricScale;
			}

			lyrics[i] = sprite;
		}
 
		return lyrics;
	}

	// long and short in terms of time
	// long: Display lyric
	// short: Moving to next location
	float longRotation = Config::I()->DToR(60);
	// Rotation between each lyric
	float rotationOffset = M_PI / 3;
	float shortRotation = M_PI - longRotation + rotationOffset;

	int lyricsOnScreen = 4;
	float fadeIncrement = 1.0f / lyricsOnScreen;
	float maxLyricScale = 0.7f;

	float baseScale = 0.05f;
	float longScaleIncrement = 1.3f;
	float shortScaleIncrement = 1.3f;

	// Number of discrete sections for spinning
	int discrete = 10;
	// It's actually missing 1 because that one is present on the screen at 0 opacity
	float offset = Config::I()->mspb;
	float spacing = 50.0f;
	float tetRadius = spacing;

	Time startTunnel = Time("00:43:440");
	Time endTet = Time("01:02:071");
	Time endTunnel = Time("01:02:387");
	Time startExpand = Time("01:03:019");
	Time startMoire = Time("01:03:650");
	std::vector<Time> timings = std::vector<Time>({
		//sugao wo kakushita
		Time("00:43:756"),
		//hyoujou wa
		Time("00:45:650"),
		//chintsuuzai
		Time("00:46:914"),
		//hontou no jibun wo
		Time("00:48:808"),
		//kakushita
		Time("00:50:703"),
		//nimensei
		Time("00:51:966"),
		//what are you waiting for?
		Time("00:53:545"),
		//i will give what you want
		Time("00:54:808"),
		//kowai no wa
		Time("00:56:071"),
		//kizuku
		Time("00:57:019"),
		//koto
		Time("00:57:966"),
		//what are you worrying about?
		Time("00:58:598"),
		//i will remove what you fear
		Time("00:59:861"),
		//muku datte
		Time("01:01:124"),
		//koto ni
		Time("01:01:756"),
		// This makes some calculations easier
		endTunnel
	});

public:
	PhaseLyricsTunnel() {
		std::string lyricsExactDirectory = R"(C:\Users\Wax Chug da Gwad\AppData\Local\osu!\Songs\Quarks_Dualive_SDVX_NOFX\Storyboard\LyricsTunnel\)";
		std::string lyricsLocalDirectory = R"(Storyboard\LyricsTunnel\)";
		std::vector<Sprite*> lyrics = loadLyrics(lyricsExactDirectory, lyricsLocalDirectory);
		setupLyrics(lyrics);
		setupTet(lyrics);
	}
};


#endif//PHASELYRICSTUNNEL_HPP