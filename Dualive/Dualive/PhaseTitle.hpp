#ifndef PHASETITLE_HPP
#define PHASETITLE_HPP

#include "Config.hpp"

class PhaseTitle {
private:
	float startScale = 0.0f;
	float endScale = 0.25f;
	float peakExpandScale = 1.2f;
	float endExpandScale = 0.5f;
	float titleSpacing = 75.0f;
	std::string title = "quarksdualive";
	std::string titleDirectory = "Storyboard\\Title\\";
	Time startMove = Time("00:01:756");
	Time endMove = Time("00:02:703");
	Time startExpand = Time("00:02:940");
	Time peakExpand = Time("00:03:019");
	Time endExpand = Time("00:05:545");

public:
	PhaseTitle() {
		int splitPoint = title.find('s');

		for (int i = 0; i < 2; i++) {
			std::string path = titleDirectory + std::to_string(i) + ".png";
			Sprite* sprite = new Sprite(path);
			Vector2 size = Config::I()->GetImageSize(Config::I()->beatmapDirectory + path) * endScale;

			// Scale to expand
			sprite->Scale(startMove.ms,
				endMove.ms,
				startScale,
				endScale);
			
			int direction = -1;
			if (i == 1) {
				direction = 1;
			}

			// Determine how far to move
			int midwidth = size.x / 2;
			int offsetWidth = (midwidth + titleSpacing) * direction;
			Vector2 endPos(Vector2::Midpoint.x + offsetWidth, Vector2::Midpoint.y);
			sprite->Move(startMove.ms,
				endMove.ms,
				Vector2::Midpoint,
				endPos,
				Easing::ExpoOut);
			
			// Extra expand at peak
			sprite->Scale(startExpand.ms,
				peakExpand.ms,
				sprite->scale,
				endScale * peakExpandScale);

			// Getting smaller  after peak
			sprite->Scale(peakExpand.ms,
				endExpand.ms,
				sprite->scale,
				sprite->scale * endExpandScale);

			// Fading to peak expand
			sprite->Fade(startMove.ms,
				endMove.ms,
				0.0f,
				1.0f);

			// Fading out from peak expand
			sprite->Fade(peakExpand.ms,
				endExpand.ms,
				1.0f,
				0.0f);
		}
	}
};

#endif//PHASETITLE_HPP