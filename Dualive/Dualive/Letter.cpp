#include "Letter.hpp"

// Pointer or ref, ayy idk
// Avoid pointers whenever possible amirite
Letter::Letter(VectorMap& vectorMap)
	: vectorMap(vectorMap), 
	letterMeasurements(calculateMeasurements(vectorMap)),
	// Yeah this looks about right
	pairTravel(buildPairs(vectorMap, buildTravel(vectorMap))),
	spriteTravel(setupSprites(pairTravel)) {
}

// Builds a vector of vector of Vector2 that indicates which points should be
// explored each interval
std::vector<std::vector<Vector2>> Letter::buildTravel(VectorMap& vectorMap) {
	std::vector<std::vector<Vector2>> travel;
	std::unordered_set<Vector2> visited;

	Vector2 vector = vectorMap.begin()->first;
	travel.push_back({ vector });
	visited.insert(vector);

	while (visited.size() != vectorMap.size()) {
		std::vector<Vector2> searchList = travel.back();
		std::vector<Vector2> addPoints;
		for (auto vector : searchList) {
			auto& search = *(vectorMap.find(vector));
			for (auto point : search.second) {
				if (visited.find(point) == visited.end()) {
					addPoints.push_back(point);
					visited.insert(point);
				}
			}
		}
		travel.push_back(addPoints);
	}

	return travel;
}

// Vector of vector of pairs that should be drawn at each step
std::vector<std::vector<Pair>> Letter::buildPairs(VectorMap& vectorMap, std::vector<std::vector<Vector2>>& travel) {
	std::vector<std::vector<Pair>> pairTravel;
	std::unordered_set<Pair> visited;

	for (int i = 0; i < travel.size(); ++i) {
		std::vector<Pair> pairs;
		for (Vector2 startPoint : travel[i]) {
			auto& mapSearch = *(vectorMap.find(startPoint));
			for (Vector2 endPoint : mapSearch.second) {
				auto& search = visited.find({ startPoint, endPoint });
				auto& reverse = visited.find({ endPoint, startPoint });
				if (search == visited.end() && reverse == visited.end()) {
					pairs.push_back(Pair(startPoint, endPoint));
					visited.insert({ startPoint, endPoint });
				}
			}
		}
		if (!pairs.empty()) {
			pairTravel.push_back(pairs);
		}
	}

	return pairTravel;
}

LetterMeasurements Letter::calculateMeasurements(VectorMap& vectorMap) {
	Vector2 max = Vector2(FLT_MIN, FLT_MIN);
	Vector2 min = Vector2(FLT_MAX, FLT_MAX);

	for (auto& mapping : vectorMap) {
		Vector2 v = mapping.first;
		if (v.x < min.x)
			min.x = v.x;
		else if (v.x > max.x)
			max.x = v.x;

		if (v.y < min.y)
			min.y = v.y;
		else if (v.y > max.y)
			max.y = v.y;
	}

	return LetterMeasurements(min, max);
}

std::string Letter::linePath = std::string(R"(C:\Users\Wax Chug da Gwad\AppData\Local\osu!\Songs\Quarks_Dualive_SDVX_NOFX\Storyboard\3D\line.png)");
std::vector<std::vector<Sprite*>> Letter::setupSprites(std::vector<std::vector<Pair>>& pairTravel) {
	std::vector<std::vector<Sprite*>> spriteTravel;

	for (auto& layer : pairTravel) {
		std::vector<Sprite*> sprites;
		// Would have used range constructor but seems like doing this with pointers is bad and they
		// just go to the same one
		for (int i = 0; i < layer.size(); ++i) {
			sprites.push_back(new Sprite(linePath, Vector2::Zero, Layer::Foreground, Origin::CentreLeft));
		}
		spriteTravel.push_back(sprites);
	}

	return spriteTravel;
}


float Letter::lineScaleHeight = 0.1f;
// Leave some time at the end
float freqFinish = 0.8f;
void Letter::display(Letter& letter, int startTime, int endTime, float scale, Vector2 displacement) {
	auto& spriteTravel = letter.spriteTravel;
	float freq = ((endTime - startTime) * freqFinish) / letter.spriteTravel.size();

	auto& pairTravel = letter.pairTravel;
	for (int i = 0; i < pairTravel.size(); ++i) {
		for (int j = 0; j < pairTravel[i].size(); ++j) {
			Pair pair = pairTravel[i][j];
			pair.first = pair.first * scale + (displacement * scale);
			pair.second = pair.second * scale + (displacement * scale);

			Vector2 distanceVector = pair.second - pair.first;
			float lineLength = distanceVector.Magnitude();
			float lineScaleWidth = lineLength / 1000;
			Vector2 lineScale(lineScaleWidth, lineScaleHeight);
			float rotation = Vector2(1, 0).AngleBetween(distanceVector);

			Sprite* line = spriteTravel[i][j];
			line->ScaleVector(startTime, startTime + (freq * (i + 1)), Vector2(0, lineScaleHeight), lineScale);
			line->Rotate(startTime, endTime, rotation, rotation);
			line->Move(startTime, endTime, pair.first, pair.first);
			line->Color(startTime, endTime, Color(255), Color(255));
		}
	}
}


int Letter::getIndex(char c) {
	return c - int('A');
}