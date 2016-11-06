#ifndef PHASESPECTRUM2D_HPP
#define PHASESPECTRUM2D_HPP

#include "Config.hpp"

class PhaseSpectrum2D {
private:
	void GenerateSpectrum() {
		std::vector<Sprite*> spectrum(data.bandCount);
		for (int i = 0; i < data.bandCount; ++i) {
			Sprite* bar = new Sprite(barPath, Vector2::Zero, Layer::Foreground, Origin::BottomCentre);
			spectrum[i] = bar;
			float rotateAmount = 2 * M_PI * ((float)i / data.bandCount);
			Vector2 specPos = startPoint.Rotate(rotateAmount);
			// Move to starting position
			bar->Move(startSpectrumExpand.ms, startSpectrumRound.ms, Vector2::Zero, specPos, Easing::CubicIn);

			// Rotate into position
			float localRotation = rotateAmount;
			bar->Rotate(startSpectrumExpand.ms, startSpectrumExpand.ms, localRotation, localRotation);

			int startIndex = data.GetMeasureIndex(startSpectrumRound);
			int test = data.GetMeasureIndex(startSpectrum);
			int speedupIndex = data.GetMeasureIndex(startSpeedupRound);
			int endIndex = data.GetMeasureIndex(endRotationRound);
			float discreteRotation = rotAmount / (speedupIndex - startIndex);
			float speedupRotation = rotSpeedupAmount / (endIndex - speedupIndex);

			float startScale = data.scaleData[i][startIndex] * barLengthScale;
			bar->ScaleVector(startSpectrumExpand.ms, startSpectrumRound.ms, Vector2(barWidthScale, barWidthScale), Vector2(barWidthScale, startScale));

			// Scale according to data
			// Handle discrete movement/rotation
			for (int j = startIndex; j < speedupIndex; ++j) {
				// j + 1 because the first entry into ScaleData is not 0
				// Kind of weird, will probably fix this probably maybeidk
				int startTime = data.snapshotRate * (j + 1);
				int endTime = startTime + data.snapshotRate;
				float scaleAmount = data.scaleData[i][j] * barLengthScale;
				bar->ScaleVector(startTime, endTime, bar->scaleVector, Vector2(barWidthScale, scaleAmount));

				Vector2 pos = bar->position.Rotate(discreteRotation);
				bar->Move(startTime, endTime, bar->position, pos);
				bar->Rotate(startTime, endTime, bar->rotation, bar->rotation + discreteRotation);
			}

			for (int j = speedupIndex; j < endIndex; ++j) {
				int startTime = data.snapshotRate * (j + 1);
				int endTime = startTime + data.snapshotRate;
				float scaleAmount = data.scaleData[i][j] * barLengthScale;
				bar->ScaleVector(startTime, endTime, bar->scaleVector, Vector2(barWidthScale, scaleAmount));

				Vector2 pos = bar->position.Rotate(speedupRotation);
				bar->Move(startTime, endTime, bar->position, pos);
				bar->Rotate(startTime, endTime, bar->rotation, bar->rotation + speedupRotation);
			}

			float fadeAmount = (1 - (float)i / data.bandCount) * 0.75f + 0.25f;
			bar->Fade(Time("00:02:703").ms, Time("00:03:019").ms, 0.0f, fadeAmount, Easing::CubicIn);
			bar->Fade(thirdSpeedupEnd.ms, endRotationRound.ms, fadeAmount, 0.0f, Easing::CubicIn);
			bar->Color(startMove.ms, startMove.ms, GetColor[GC::PINK], GetColor[GC::PINK]);
			bar->Color(startSpeedup.ms - Config::I()->mspb, startSpeedup.ms, bar->color, GetColor[GC::ORANGE], Easing::CubicIn);
			bar->Color(Time("00:15:650").ms - Config::I()->mspb, Time("00:15:650").ms, bar->color, GetColor[GC::NAVY], Easing::CubicIn);
			Config::I()->SwitchSpriteColor(bar, secondSpeedup.ms, thirdSpeedup.ms, GetColor[GC::GREEN], GetColor[GC::BLUE], Config::I()->mspb, Config::I()->mspb);
			Config::I()->SwitchSpriteColor(bar, thirdSpeedup.ms, thirdSpeedupEnd.ms, GetColor[GC::PURPLE], GetColor[GC::SUNLIGHT], Config::I()->mspb / 8, Config::I()->mspb / 8);
		}
	}

	void GenerateCenterpiece() {
		Sprite* centerpiece = new Sprite(cpPath);
		centerpiece->Scale(startExpand.ms, endExpand.ms, 0.0f, cpExpandScale, Easing::CubicOut);
		centerpiece->Fade(startExpand.ms, endExpand.ms,	0.0f, 1.0f);
		centerpiece->Scale(endExpand.ms, endShrink.ms, centerpiece->scale, cpShrinkScale, Easing::CubicIn);
		centerpiece->Scale(endShrink.ms, startSpectrum.ms, cpShrinkScale, cpMiniScale);
		centerpiece->Scale(startSpectrum.ms, startSpectrum.ms + Config::I()->offset * 2, cpMiniScale, cpShrinkScale);
		centerpiece->Fade(endExpand.ms,	thirdSpeedupEnd.ms,	1.0f, 1.0f);
		centerpiece->Rotate(startSpectrumRound.ms, startSpeedupRound.ms, centerpiece->rotation,	centerpiece->rotation + rotAmount);
		centerpiece->Rotate(startSpeedupRound.ms, endRotationRound.ms, centerpiece->rotation, centerpiece->rotation + rotSpeedupAmount);
		centerpiece->Color(Config::I()->songStart.ms, Config::I()->songStart.ms, GetColor[GC::PINK], GetColor[GC::PINK]);

		for (float startTime = startCpScale.ms; startTime < secondSpeedup.ms; startTime += Config::I()->mspb * 2) {
			centerpiece->Scale(startTime - Config::I()->offset * 2,	startTime, cpShrinkScale, cpMiniScale);
			centerpiece->Scale(startTime, startTime + Config::I()->offset * 2, cpMiniScale, cpShrinkScale);
		}

		for (float startTime = secondSpeedup.ms; startTime < thirdSpeedup.ms; startTime += Config::I()->mspb) {
			centerpiece->Scale(startTime - Config::I()->offset,	startTime, cpShrinkScale, cpMiniScale);
			centerpiece->Scale(startTime, startTime + Config::I()->offset, cpMiniScale,	cpShrinkScale);
		}

		for (float startTime = thirdSpeedup.ms; startTime < thirdSpeedupEnd.ms; startTime += Config::I()->mspb / 2) {
			centerpiece->Scale(startTime - Config::I()->offset,	startTime, cpShrinkScale, cpMiniScale);
			centerpiece->Scale(startTime, startTime + Config::I()->offset, cpMiniScale, cpShrinkScale);
		}

		centerpiece->Color(startSpeedup.ms - Config::I()->mspb, startSpeedup.ms, centerpiece->color, GetColor[GC::ORANGE], Easing::CubicIn);
		centerpiece->Color(Time("00:15:650").ms - Config::I()->mspb, Time("00:15:650").ms, centerpiece->color, GetColor[GC::NAVY], Easing::CubicIn);
		Config::I()->SwitchSpriteColor(centerpiece, secondSpeedup.ms, thirdSpeedup.ms, GetColor[GC::GREEN], GetColor[GC::BLUE], Config::I()->mspb, Config::I()->mspb);
		Config::I()->SwitchSpriteColor(centerpiece, thirdSpeedup.ms, thirdSpeedupEnd.ms, GetColor[GC::PURPLE], GetColor[GC::SUNLIGHT], Config::I()->mspb / 8, Config::I()->mspb / 8);

		centerpiece->Scale(thirdSpeedupEnd.ms, endRotationRound.ms, centerpiece->scale, 0.0f, Easing::CubicIn);
		centerpiece->Fade(thirdSpeedupEnd.ms, endRotation.ms, 1.0f, 0.0f, Easing::CubicIn);
	}

	// Centerpiece setup
	// Easier access
	MusicAnalysisData data = Config::I()->data;
	float cpExpandScale = 0.2f;
	float cpShrinkScale = 0.11f;
	float cpMiniScale = 0.08f;
	float rotAmount = 2 * M_PI;
	// Not actually 4 times faster because of period lengths
	float rotSpeedupAmount = 4 * M_PI;
	std::string cpPath = "Storyboard\\Spectrum2D\\Centerpiece.png";
	
	Time startExpand = Time("00:01:756");
	Time startSpectrumExpand = Time("00:02:387");
	Time endExpand = Time("00:02:387");
	Time endShrink = Time("00:02:861");
	Time startSpectrum = Time("00:03:019");
	Time startSpectrumRound = Config::I()->GetClosestTime(Time("00:03:019"));
	Time startCpScale = Time("00:09:335");
	Time startSpeedup = Time("00:13:124");
	Time startSpeedupRound = Config::I()->GetClosestTime(Time("00:13:124"));
	Time endRotation = Time("00:23:229");
	Time endRotationRound = Config::I()->GetClosestTime(Time("00:23:229"));
	Time secondSpeedup = Time("00:18:177");
	Time thirdSpeedup = Time("00:20:703");
	Time thirdSpeedupEnd = Time("00:21:966");

	// Distance away from center
	float spectrumSpacing = 80.0f;
	float barWidthScale = 0.018f;
	float barLengthScale = 0.003f;
	Vector2 startPoint = Vector2(0, spectrumSpacing);
	std::string barPath = "Storyboard\\Spectrum2D\\CenterpieceNoSpacing.png";

	Time startMove = "00:01:756";
	Time maxFadeSpectrum = "00:03:019";
public: 
	PhaseSpectrum2D() {
		GenerateSpectrum();
		GenerateCenterpiece();
	}
};

#endif//PHASESPECTRUM2D_HPP