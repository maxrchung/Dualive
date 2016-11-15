#include "Config.hpp"

Config* Config::instance = NULL;

Config* Config::I() {
	if (instance == NULL) {
		instance = new Config;
	}
	return instance;
}

float Config::DToR(int degrees) {
	return degrees * M_PI / 180.0f;
}

Vector2 Config::GetImageSize(const std::string& path) {
	std::ifstream in(path);
	unsigned int width, height;

	in.seekg(16);
	in.read((char *)&width, 4);
	in.read((char *)&height, 4);
	in.close();

	width = ntohl(width);
	height = ntohl(height);

	return Vector2(width, height);
}

Time Config::GetClosestTime(Time time) {
	return Time(roundf(time.ms / 100.0f) * 100.0f);
}

void Config::SwitchSpriteColor(Sprite* sprite, int start, int end, Color first, Color second, float offset, float frequency) {
	sprite->Color(start - offset, start, sprite->color, first);
	
	std::ostringstream secondToFirst, firstToSecond;
	firstToSecond << "__C,0," << int(frequency - offset)     << "," << int(frequency)     << "," << first.r << "," << first.g << "," << first.b << "," << second.r << "," << second.g << "," << second.b;
	secondToFirst << "__C,0," << int(frequency * 2 - offset) << "," << int(frequency * 2) << "," << second.r << "," << second.g << "," << second.b << "," << first.r << "," << first.g << "," << first.b;

	std::vector<std::string> loopCommands = {
		firstToSecond.str(),
		secondToFirst.str()
	};

	int totalTime = end - start;
	int loopTime = frequency * 2;
	int numFreqs = totalTime / loopTime;
	sprite->Loop(start, numFreqs, loopCommands);

	int cycles = 0;
	for (int time = start + frequency; time <= end; time += frequency) {
		++cycles;
	}

	// If the number of cycles is odd, then we need to perform one more color switch
	if (cycles % 2 == 1) {
		sprite->Color(end - offset, end, first, second);
	}
}

void Config::AddScaleTimings(ScaleTimings& scaleTimings, Time timeStart, Time timeEnd, float freq, float scaleLarge, float scaleSmall) {
	for (int i = timeStart.ms; i < timeEnd.ms; i += freq) {
		scaleTimings.push_back(ScaleTiming(i - offset, scaleLarge));
		scaleTimings.push_back(ScaleTiming(i, scaleSmall));
		scaleTimings.push_back(ScaleTiming(i + offset, scaleLarge));
	}

	// May miss last value
	scaleTimings.push_back(ScaleTiming(timeEnd.ms - offset, scaleLarge));
	scaleTimings.push_back(ScaleTiming(timeEnd.ms, scaleSmall));
	scaleTimings.push_back(ScaleTiming(timeEnd.ms + offset, scaleLarge));
}

float Config::GetScale(ScaleTimings& scaleTimings, float time) {
	int remove = 0;
	ScaleTiming base = scaleTimings[remove];
	ScaleTiming next = scaleTimings[remove + 1];
	while (time > next.first) {
		scaleTimings.pop_front();
		base = scaleTimings[remove];
		next = scaleTimings[remove + 1];
	}

	float localMax = next.first - base.first;
	float localValue = time - base.first;
	float fraction = localValue / localMax;
	float scaleFraction = (next.second - base.second) * fraction;
	float scale = base.second + scaleFraction;

	return scale;
}

std::vector<Vector2> Config::GetPositions() {
	std::string trianglePath(R"(C:\Users\Wax Chug da Gwad\AppData\Local\osu!\Songs\474742 Quarks - Dualive\Storyboard\Spectrum2D\PatternPiece.png)");
	Vector2 imageSize(Config::I()->GetImageSize(trianglePath));
	Vector2 scaledSize(imageSize * Config::I()->patternScale);

	// Ran into some offset problems that I dealt with
	// (to a good enough degree) with flooring

	// Weirdly enough it's only on the y, maybe it's a discrepancy
	// between how my utility handles the file and how the GetImageSize
	// function handles it
	scaledSize.y = floorf(scaledSize.y);

	Vector2 halfScaledSize = scaledSize / 2;
	Vector2 bgSize(854.0f, 480.0f);
	Vector2 halfBgSize = bgSize / 2;

	// Calculate for width
	// Subtract half of the center triangle
	float halfWidth = halfBgSize.x - halfScaledSize.x;
	int numHalfWidth = ceilf(halfWidth / scaledSize.x);
	// Center + Number of triangles for each side
	int numWidth = 1 + 2 * numHalfWidth;

	// Repeat for length
	float halfLength = halfBgSize.y - halfScaledSize.y;
	int numHalfLength = ceilf(halfLength / scaledSize.y);
	int numLength = 1 + 2 * numHalfLength;

	int totalTriangles = numWidth * numLength;
	std::vector<Vector2> positions(totalTriangles);
	Vector2 startPos(-scaledSize.x * numHalfWidth,
		-scaledSize.y * numHalfLength);

	for (int i = 0; i < numLength; ++i) {
		for (int j = 0; j < numWidth; ++j) {
			int index = i * numWidth + j;
			Vector2 pos = startPos + Vector2(j * scaledSize.x,
				i * scaledSize.y);
			positions[index] = pos;
		}
	}
	return positions;
}