#ifndef PHASESPECTRUM2D_HPP
#define PHASESPECTRUM2D_HPP

#include "Config.hpp"

class PhaseSpectrum2D {
private:
	void GenerateSpectrum() {
		std::vector<Sprite*> spectrum(data.bandCount);
		for (int i = 0; i < data.bandCount; ++i) {
			Sprite* back = new Sprite(barPath, Vector2::Zero, Layer::Foreground, Origin::BottomCentre);
			Sprite* bar = new Sprite(barPath, Vector2::Zero, Layer::Foreground, Origin::BottomCentre);

			spectrum[i] = bar;
			float rotateAmount = 2 * M_PI * ((float)i / data.bandCount);
			Vector2 specPos = startPoint.Rotate(rotateAmount);
			// Move to starting position
			bar->Move(startSpectrumExpand.ms, startSpectrumRound.ms, Vector2::Zero, specPos, Easing::CubicIn);

			auto innerPos = (startPoint + Vector2(0, -1)).Rotate(rotateAmount);
			back->Move(startSpectrumExpand.ms, startSpectrumRound.ms, Vector2::Zero, innerPos, Easing::CubicIn);

			// Rotate into position
			float localRotation = rotateAmount;
			bar->Rotate(startSpectrumExpand.ms, startSpectrumExpand.ms, localRotation, localRotation);
			back->Rotate(startSpectrumExpand.ms, startSpectrumExpand.ms, localRotation, localRotation);

			int startIndex = data.GetMeasureIndex(startSpectrumRound);
			int test = data.GetMeasureIndex(startSpectrum);
			int speedupIndex = data.GetMeasureIndex(startSpeedupRound);
			int endIndex = data.GetMeasureIndex(endRotationRound);
			float discreteRotation = rotAmount / (speedupIndex - startIndex);
			float speedupRotation = rotSpeedupAmount / (endIndex - speedupIndex);

			float startScale = data.scaleData[i][startIndex] * barLengthScale;
			bar->ScaleVector(startSpectrumExpand.ms, startSpectrumRound.ms, Vector2(barWidthScale, barWidthScale), Vector2(barWidthScale, startScale));
			back->ScaleVector(startSpectrumExpand.ms, startSpectrumRound.ms, Vector2(barWidthScale, barWidthScale), Vector2(barWidthScale, startScale));

			// Scale according to data
			// Handle discrete movement/rotation
			for (int j = startIndex; j < speedupIndex; ++j) {
				// j + 1 because the first entry into ScaleData is not 0
				// Kind of weird, will probably fix this probably maybeidk
				int startTime = data.snapshotRate * (j + 1);
				int endTime = startTime + data.snapshotRate;
				float scaleAmount = data.scaleData[i][j] * barLengthScale;
				bar->ScaleVector(startTime, endTime, bar->scaleVector, Vector2(barWidthScale, scaleAmount));
				back->ScaleVector(startTime, endTime, back->scaleVector, Vector2(barWidthScale + 0.006, scaleAmount + 0.02));


				Vector2 pos = bar->position.Rotate(discreteRotation);
				bar->Move(startTime, endTime, bar->position, pos);
				bar->Rotate(startTime, endTime, bar->rotation, bar->rotation + discreteRotation);

				auto backPos = back->position.Rotate(discreteRotation);
				back->Move(startTime, endTime, back->position, backPos);
				back->Rotate(startTime, endTime, back->rotation, back->rotation + discreteRotation);
			}

			for (int j = speedupIndex; j < endIndex; ++j) {
				int startTime = data.snapshotRate * (j + 1);
				int endTime = startTime + data.snapshotRate;
				float scaleAmount = data.scaleData[i][j] * barLengthScale;
				bar->ScaleVector(startTime, endTime, bar->scaleVector, Vector2(barWidthScale, scaleAmount));
				back->ScaleVector(startTime, endTime, back->scaleVector, Vector2(barWidthScale + 0.006, scaleAmount + 0.02));

				Vector2 pos = bar->position.Rotate(speedupRotation);
				bar->Move(startTime, endTime, bar->position, pos);
				bar->Rotate(startTime, endTime, bar->rotation, bar->rotation + speedupRotation);

				auto backPos = back->position.Rotate(speedupRotation);
				back->Move(startTime, endTime, back->position, backPos);
				back->Rotate(startTime, endTime, back->rotation, back->rotation + speedupRotation);
			}

			float fadeAmount = (1 - (float)i / data.bandCount) * 0.75f + 0.25f;
			bar->Fade(Time("00:02:703").ms, Time("00:03:019").ms, 0.0f, fadeAmount, Easing::CubicIn);
			bar->Fade(thirdSpeedupEnd.ms, endRotationRound.ms, fadeAmount, 0.0f, Easing::CubicIn);
			bar->Color(startMove.ms, startMove.ms, GetColor[GC::PINK], GetColor[GC::PINK]);
			bar->Color(startSpeedup.ms - Config::I()->mspb, startSpeedup.ms, bar->color, GetColor[GC::ORANGE], Easing::CubicIn);
			bar->Color(Time("00:15:650").ms - Config::I()->mspb, Time("00:15:650").ms, bar->color, GetColor[GC::NAVY], Easing::CubicIn);
			Config::I()->SwitchSpriteColor(bar, secondSpeedup.ms, thirdSpeedup.ms, GetColor[GC::GREEN], GetColor[GC::BLUE], Config::I()->mspb, Config::I()->mspb);
			Config::I()->SwitchSpriteColor(bar, thirdSpeedup.ms, thirdSpeedupEnd.ms, GetColor[GC::YELLOW], GetColor[GC::PURPLE], Config::I()->mspb / 4, Config::I()->mspb / 4);

			auto backOffset = 0.3f;
			back->Fade(Time("00:02:703").ms, Time("00:13:124").ms, 0.0f, fadeAmount, Easing::CubicIn);
			back->Fade(thirdSpeedupEnd.ms, endRotationRound.ms, fadeAmount, 0.0f, Easing::CubicIn);
			back->Color(startMove.ms, startMove.ms, GetColor[GC::PINK] * backOffset, GetColor[GC::PINK] * backOffset);
			back->Color(startSpeedup.ms - Config::I()->mspb, startSpeedup.ms, back->color, GetColor[GC::ORANGE] * backOffset, Easing::CubicIn);
			back->Color(Time("00:15:650").ms - Config::I()->mspb, Time("00:15:650").ms, back->color, GetColor[GC::NAVY] * backOffset, Easing::CubicIn);
			Config::I()->SwitchSpriteColor(back, secondSpeedup.ms, thirdSpeedup.ms, GetColor[GC::GREEN] * backOffset, GetColor[GC::BLUE] * backOffset, Config::I()->mspb, Config::I()->mspb);
			Config::I()->SwitchSpriteColor(back, thirdSpeedup.ms, thirdSpeedupEnd.ms, GetColor[GC::YELLOW] * backOffset, GetColor[GC::PURPLE] * backOffset, Config::I()->mspb / 4, Config::I()->mspb / 4);
		}
	}

	void GenerateCenterpiece() {
		Sprite* border = new Sprite(cpPath);
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

		auto borderOffset = 0.01f;
		auto colorOffset = 0.3f;
		border->Scale(startExpand.ms, endExpand.ms, 0.0f, cpExpandScale, Easing::CubicOut);
		border->Fade(Time("00:03:197").ms, Time("00:13:124").ms, 0.0f, 1.0f);
		border->Scale(startSpectrum.ms, startSpectrum.ms, cpShrinkScale + borderOffset, cpShrinkScale + borderOffset);
		border->Rotate(startSpectrumRound.ms, startSpeedupRound.ms, border->rotation, border->rotation + rotAmount);
		border->Rotate(startSpeedupRound.ms, endRotationRound.ms, border->rotation, border->rotation + rotSpeedupAmount);
		border->Color(Config::I()->songStart.ms, Config::I()->songStart.ms, GetColor[GC::PINK] * colorOffset, GetColor[GC::PINK] * colorOffset);

		for (float startTime = startCpScale.ms; startTime < secondSpeedup.ms; startTime += Config::I()->mspb * 2) {
			centerpiece->Scale(startTime - Config::I()->offset * 2,	startTime, cpShrinkScale, cpMiniScale);
			centerpiece->Scale(startTime, startTime + Config::I()->offset * 2, cpMiniScale, cpShrinkScale);
			border->Scale(startTime - Config::I()->offset * 2, startTime, cpShrinkScale + borderOffset, cpMiniScale + borderOffset);
			border->Scale(startTime, startTime + Config::I()->offset * 2, cpMiniScale + borderOffset, cpShrinkScale + borderOffset);
		}

		for (float startTime = secondSpeedup.ms; startTime < thirdSpeedup.ms; startTime += Config::I()->mspb) {
			centerpiece->Scale(startTime - Config::I()->offset,	startTime, cpShrinkScale, cpMiniScale);
			centerpiece->Scale(startTime, startTime + Config::I()->offset, cpMiniScale,	cpShrinkScale);
			border->Scale(startTime - Config::I()->offset, startTime, cpShrinkScale + borderOffset, cpMiniScale + borderOffset);
			border->Scale(startTime, startTime + Config::I()->offset, cpMiniScale + borderOffset, cpShrinkScale + borderOffset);
		}

		for (float startTime = thirdSpeedup.ms; startTime < thirdSpeedupEnd.ms; startTime += Config::I()->mspb / 2) {
			centerpiece->Scale(startTime - Config::I()->offset,	startTime, cpShrinkScale, cpMiniScale);
			centerpiece->Scale(startTime, startTime + Config::I()->offset, cpMiniScale, cpShrinkScale);
			border->Scale(startTime - Config::I()->offset, startTime, cpShrinkScale + borderOffset, cpMiniScale + borderOffset);
			border->Scale(startTime, startTime + Config::I()->offset, cpMiniScale + borderOffset, cpShrinkScale + borderOffset);
		}

		centerpiece->Color(startSpeedup.ms - Config::I()->mspb, startSpeedup.ms, centerpiece->color, GetColor[GC::ORANGE], Easing::CubicIn);
		centerpiece->Color(Time("00:15:650").ms - Config::I()->mspb, Time("00:15:650").ms, centerpiece->color, GetColor[GC::NAVY], Easing::CubicIn);
		Config::I()->SwitchSpriteColor(centerpiece, secondSpeedup.ms, thirdSpeedup.ms, GetColor[GC::GREEN], GetColor[GC::BLUE], Config::I()->mspb, Config::I()->mspb);
		Config::I()->SwitchSpriteColor(centerpiece, thirdSpeedup.ms, thirdSpeedupEnd.ms, GetColor[GC::YELLOW], GetColor[GC::PURPLE], Config::I()->mspb / 4, Config::I()->mspb / 4);

		border->Color(startSpeedup.ms - Config::I()->mspb, startSpeedup.ms, border->color, GetColor[GC::ORANGE] * colorOffset, Easing::CubicIn);
		border->Color(Time("00:15:650").ms - Config::I()->mspb, Time("00:15:650").ms, border->color, GetColor[GC::NAVY] * colorOffset, Easing::CubicIn);
		Config::I()->SwitchSpriteColor(border, secondSpeedup.ms, thirdSpeedup.ms, GetColor[GC::GREEN] * colorOffset, GetColor[GC::BLUE] * colorOffset, Config::I()->mspb, Config::I()->mspb);
		Config::I()->SwitchSpriteColor(border, thirdSpeedup.ms, thirdSpeedupEnd.ms, GetColor[GC::YELLOW] * colorOffset, GetColor[GC::PURPLE] * colorOffset, Config::I()->mspb / 4, Config::I()->mspb / 4);

		centerpiece->Scale(thirdSpeedupEnd.ms, endRotationRound.ms, centerpiece->scale, 0.0f, Easing::CubicIn);
		border->Scale(thirdSpeedupEnd.ms, endRotationRound.ms, border->scale, 0.0f, Easing::CubicIn);

		centerpiece->Fade(thirdSpeedupEnd.ms, endRotation.ms, 1.0f, 0.0f, Easing::CubicIn);
		border->Fade(thirdSpeedupEnd.ms, endRotation.ms, 1.0f, 0.0f, Easing::CubicIn);
	}

	// Centerpiece setup
	// Easier access
	MusicAnalysisData data = Config::I()->data;
	float cpExpandScale = 0.2f * 2;
	float cpShrinkScale = 0.085f * 2;
	float cpMiniScale = 0.06f * 2;
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
	float spectrumSpacing = 75.0f;
	float barWidthScale = 0.016f * 2;
	float barLengthScale = 0.0023f * 2;
	Vector2 startPoint = Vector2(0, spectrumSpacing);
	std::string barPath = "Storyboard\\Spectrum2D\\CenterpieceNoSpacing.png";
	std::string linePath = R"(Storyboard\3D\Line.png)";

	Time startMove = "00:01:756";
	Time maxFadeSpectrum = "00:03:019";
public: 
	PhaseSpectrum2D() {
		GenerateSpectrum();
		GenerateCenterpiece();
	}
};

#endif//PHASESPECTRUM2D_HPP