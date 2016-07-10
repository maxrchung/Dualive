#ifndef PHASESPECTRUM2D_HPP
#define PHASESPECTRUM2D_HPP

#include "Phase.hpp"

class PhaseSpectrum2D : public Phase {
private:
	void GenerateSpectrum() {
		std::vector<Sprite*> spectrum(data.bandCount);
		for (int i = 0; i < data.bandCount; ++i) {
			Sprite* bar = new Sprite(barPath, Vector2::Midpoint, Layer::Foreground, Origin::BottomCentre);
			spectrum[i] = bar;
			float rotateAmount = 2 * M_PI * ((float)i / data.bandCount);
			Vector2 specPos = startPoint.RotateAround(Vector2::Midpoint, rotateAmount);

			// Move to starting position
			bar->Move(startMove.ms,
				startSpectrumRound.ms,
				Vector2::Midpoint,
				specPos);

			// Rotate into position
			float localRotation = rotateAmount;
			bar->Rotate(startMove.ms,
				startMove.ms,
				localRotation,
				localRotation);

			int startIndex = data.GetMeasureIndex(startSpectrumRound);
			int speedupIndex = data.GetMeasureIndex(startSpeedupRound);
			int endIndex = data.GetMeasureIndex(endRotationRound);
			float discreteRotation = rotAmount / (speedupIndex - startIndex);
			float speedupRotation = rotSpeedupAmount / (endIndex - speedupIndex);

			float startScale = data.scaleData[i][startIndex] * barLengthScale;
			bar->ScaleVector(startMove.ms,
				startSpectrumRound.ms,
				Vector2(0.0f, 0.0f),
				Vector2(barWidthScale, startScale));

			// Scale according to data
			// Handle discrete movement/rotation
			for (int j = startIndex; j < speedupIndex; ++j) {
				// j + 1 because the first entry into ScaleData is not 0
				// Kind of weird, will probably fix this probably maybeidk
				int startTime = data.snapshotRate * (j + 1);
				int endTime = startTime + data.snapshotRate;
				float scaleAmount = data.scaleData[i][j] * barLengthScale;

				bar->ScaleVector(startTime,
					endTime,
					bar->scaleVector,
					Vector2(barWidthScale, scaleAmount));

				Vector2 pos = bar->position.RotateAround(Vector2::Midpoint, discreteRotation);
				bar->Move(startTime,
					endTime,
					bar->position,
					pos);

				bar->Rotate(startTime,
					endTime,
					bar->rotation,
					bar->rotation + discreteRotation);
			}

			for (int j = speedupIndex; j < endIndex; ++j) {
				int startTime = data.snapshotRate * (j + 1);
				int endTime = startTime + data.snapshotRate;
				float scaleAmount = data.scaleData[i][j] * barLengthScale;

				bar->ScaleVector(startTime,
					endTime,
					bar->scaleVector,
					Vector2(barWidthScale, scaleAmount));

				Vector2 pos = bar->position.RotateAround(Vector2::Midpoint, speedupRotation);
				bar->Move(startTime,
					endTime,
					bar->position,
					pos);

				bar->Rotate(startTime,
					endTime,
					bar->rotation,
					bar->rotation + speedupRotation);
			}

			float fadeAmount = (1 - (float)i / data.bandCount) * 0.75f + 0.25f;
			bar->Fade(startMove.ms,
				maxFadeSpectrum.ms,
				0.0f,
				1.0f);

			bar->Fade(thirdSpeedupEnd.ms,
				endRotationRound.ms,
				1.0f,
				0.0f);

			bar->Color(startMove.ms,
				startMove.ms,
				Color(fadeAmount * 255),
				Color(fadeAmount * 255));
		}
	}

	void GenerateCenterpiece() {
		Sprite* centerpiece = new Sprite(cpPath);
		centerpiece->Scale(startExpand.ms,
			endExpand.ms,
			0.0f,
			cpExpandScale);

		centerpiece->Fade(startExpand.ms,
			endExpand.ms,
			0.0f,
			1.0f);

		centerpiece->Scale(endExpand.ms,
			endShrink.ms,
			centerpiece->scale,
			cpShrinkScale);

		centerpiece->Fade(endExpand.ms,
			Config::I()->songEnd.ms,
			1.0f,
			1.0f);

		centerpiece->Rotate(startSpectrumRound.ms,
			startSpeedupRound.ms,
			centerpiece->rotation,
			centerpiece->rotation + rotAmount);

		centerpiece->Rotate(startSpeedupRound.ms,
			endRotationRound.ms,
			centerpiece->rotation,
			centerpiece->rotation + rotSpeedupAmount);

		for (float startTime = startSpeedup.ms; startTime < secondSpeedup.ms; startTime += Config::I()->mspb * 2) {
			centerpiece->Scale(startTime - Config::I()->offset * 2,
				startTime,
				cpShrinkScale,
				cpMiniScale);

			centerpiece->Scale(startTime,
				startTime + Config::I()->offset * 2,
				cpMiniScale,
				cpShrinkScale);
		}

		for (float startTime = secondSpeedup.ms; startTime < thirdSpeedup.ms; startTime += Config::I()->mspb) {
			centerpiece->Scale(startTime - Config::I()->offset,
				startTime,
				cpShrinkScale,
				cpMiniScale);

			centerpiece->Scale(startTime,
				startTime + Config::I()->offset,
				cpMiniScale,
				cpShrinkScale);
		}

		for (float startTime = thirdSpeedup.ms; startTime < thirdSpeedupEnd.ms; startTime += Config::I()->mspb / 2) {
			centerpiece->Scale(startTime - Config::I()->offset,
				startTime,
				cpShrinkScale,
				cpMiniScale);

			centerpiece->Scale(startTime,
				startTime + Config::I()->offset,
				cpMiniScale,
				cpShrinkScale);
		}

		centerpiece->Scale(thirdSpeedupEnd.ms,
			endRotationRound.ms,
			centerpiece->scale,
			0.0f);
	}

	// Centerpiece setup
	// Easier access
	MusicAnalysisData data = Config::I()->data;
	float cpExpandScale = 0.15f;
	float cpShrinkScale = 0.075f;
	float cpMiniScale = 0.05f;
	float rotAmount = 2 * M_PI;
	// Not actually 4 times faster because of period lengths
	float rotSpeedupAmount = 4 * M_PI;
	std::string cpPath = "Storyboard\\Spectrum2D\\Centerpiece.png";

	Time startExpand = Time("00:01:756");
	Time endExpand = Time("00:02:387");
	Time endShrink = Time("00:02:703");
	Time startSpectrum = Time("00:03:019");
	Time startSpectrumRound = Config::I()->GetClosestTime(Time("00:03:019"));
	Time startSpeedup = Time("00:13:124");
	Time startSpeedupRound = Config::I()->GetClosestTime(Time("00:13:124"));
	Time endRotation = Time("00:23:229");
	Time endRotationRound = Config::I()->GetClosestTime(Time("00:23:229"));
	Time secondSpeedup = Time("00:18:177");
	Time thirdSpeedup = Time("00:20:703");
	Time thirdSpeedupEnd = Time("00:21:966");

	// Distance away from center
	float spectrumSpacing = 60.0f;
	float barWidthScale = 0.01f;
	float barLengthScale = 0.002f;
	Vector2 startPoint = Vector2::Midpoint - Vector2(0, spectrumSpacing);
	std::string barPath = "Storyboard\\Spectrum2D\\CenterpieceNoSpacing.png";

	Time startMove = "00:01:756";
	Time maxFadeSpectrum = "00:05:545";
public:
	PhaseSpectrum2D() {
		GenerateSpectrum();
		GenerateCenterpiece();
	}
};

#endif//PHASESPECTRUM2D_HPP