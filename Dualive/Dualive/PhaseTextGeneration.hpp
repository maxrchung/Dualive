#ifndef PHASETEXTGENERATION_HPP
#define PHASETEXTGENERATION_HPP

#include "Config.hpp"
#include <unordered_map>
#include <unordered_set>

// Pair hash
namespace std {
	template<>
	struct hash<std::pair<Vector2, Vector2>> {
		size_t operator()(const std::pair<Vector2, Vector2>& value) const {
			return (std::hash<Vector2>()(value.first) * 0x1f1f1f1f) ^ (std::hash<Vector2>()(value.second) << 1);
		}
	};
}

class PhaseTextGeneration {
	typedef std::unordered_map<Vector2, std::unordered_set<Vector2>> VectorMap;
	typedef std::pair<Vector2, Vector2> Pair;
public:
	PhaseTextGeneration() {
		std::string glyphDataPath = R"(C:\Users\Wax Chug da Gwad\Desktop\Dualive\Dualive\Debug\GlyphOutlineData.txt)";
		std::vector<VectorMap> outlines = loadOutlinesData(glyphDataPath);

		for (int i = 0; i < outlines.size(); ++i) {
			Color color(rand() % 200 + 55, rand() % 200 + 55, rand() % 200 + 55);

			VectorMap vectorMap = outlines[i];
			std::vector<std::vector<Vector2>> travel = buildTravel(outlines[i]);

			int time = Time("00:03:019").ms;
			int freq = Config::I()->mspb * 2;
			int endTime = travel.size() * 5000;
			std::unordered_set<Pair> visited;
			for (int i = 0; i < travel.size(); ++i) {
				for (Vector2 startPoint : travel[i]) {
					auto& mapSearch = *(vectorMap.find(startPoint));
					for (Vector2 endPoint : mapSearch.second) {
						auto& search = visited.find({ startPoint, endPoint });
						auto& reverse = visited.find({ endPoint, startPoint });
						if (search == visited.end() && reverse == visited.end()) {
							display(startPoint, endPoint, time, freq, endTime);
							visited.insert({ startPoint, endPoint });
						}
					}
				}
				time += freq;
			}

			//for (auto& pocket : outlines[i]) {
			//	for (auto& point : pocket.second) {
			//		Vector2 pocketValue = pocket.first;
			//		Vector2 distanceVector = point - pocketValue;
			//		float lineLength = distanceVector.Magnitude();
			//		float lineScaleWidth = lineLength / 1000;
			//		Vector2 lineScale(lineScaleWidth, lineScaleHeight);
			//		float rotation = Vector2(1, 0).AngleBetween(distanceVector);

			//		Sprite* line = new Sprite(linePath, Vector2::Zero, Layer::Foreground, Origin::CentreLeft);
			//		line->ScaleVector(startTime, endTime, lineScale, lineScale);
			//		line->Rotate(startTime, endTime, rotation, rotation);

			//		Vector2 linePos = pocketValue - Vector2(halfWidth, halfHeight);
			//		line->Move(startTime, endTime, linePos, linePos);
			//		line->Color(startTime, endTime, color, color);
			//	}
			//}
		}
	}

private:
	Vector2 max = Vector2(FLT_MIN, FLT_MIN);
	Vector2 min = Vector2(FLT_MAX, FLT_MAX);
	float width;
	float height;
	float halfWidth;
	float halfHeight;

	std::string linePath = std::string(R"(C:\Users\Wax Chug da Gwad\AppData\Local\osu!\Songs\Quarks_Dualive_SDVX_NOFX\Storyboard\3D\line.png)");
	float lineScaleHeight = 0.1f;
	void display(Vector2 startPoint, Vector2 endPoint, int startTime, int freq, int endTime) {
		Vector2 distanceVector = endPoint - startPoint;
		float lineLength = distanceVector.Magnitude();
		float lineScaleWidth = lineLength / 1000;
		Vector2 lineScale(lineScaleWidth, lineScaleHeight);
		float rotation = Vector2(1, 0).AngleBetween(distanceVector);

		Sprite* line = new Sprite(linePath, Vector2::Zero, Layer::Foreground, Origin::CentreLeft);
		line->ScaleVector(startTime, startTime + freq, Vector2(0, lineScaleHeight), lineScale);
		line->Rotate(startTime, endTime, rotation, rotation);

		Vector2 linePos = startPoint - max / 2;
		line->Move(startTime, endTime, linePos, linePos);
		line->Color(startTime, endTime, Color(255), Color(255));
	}

	// Builds a vector of vector of Vector2 that indicates which points should be
	// explored each interval
	std::vector<std::vector<Vector2>> buildTravel(VectorMap& vectorMap) {
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

	std::vector<std::string> lyrics = std::vector<std::string>({
		"LET YOU DIVE AWAY",
		"FROM OUR PAINFUL DAYS",
		"USO DARAKE",
		"NO SABITA",
		"HIBI WO",
		"UGATTE",
		"GET YOUR HIDDEN WAY",
		"FROM OUR FLAWLESS MAZE",
		"SAGASU",
		"WO",
		"O",
		"O",
		"O",
		"O",
		"O",
		"WE'RE BREATHING IN DUALIVE"
	});

	std::vector<VectorMap> loadOutlinesData(std::string& path) {
		float pointScale = 0.3f;
		std::ifstream file(path);
		
		std::vector<VectorMap> outlines;
		int numOutlines;
		file >> numOutlines;

		for (int j = 0; j < numOutlines; ++j) {
			VectorMap vectorMap;
			int numPockets;
			file >> numPockets;

			for (int k = 0; k < numPockets; ++k) {
				float pocketX, pocketY;
				file >> pocketX >> pocketY;
				Vector2 pocketVector = Vector2(pocketX, pocketY) * pointScale;

				std::unordered_set<Vector2> points;
				int numPoints;
				file >> numPoints;

				for (int l = 0; l < numPoints; ++l) {
					float pointX, pointY;
					file >> pointX >> pointY;
					Vector2 point = Vector2(pointX, pointY) * pointScale;
					points.insert(point);

					if (point.x < min.x) {
						min.x = point.x;
					}
					else if (point.x > max.x) {
						max.x = point.x;
					}

					if (point.y < min.y) {
						min.y = point.y;
					}
					else if (point.y > max.y) {
						max.y = point.y;
					}
				}

				vectorMap.insert({ pocketVector, points });
			}

			outlines.push_back(vectorMap);
		}

		width = max.x + min.x;
		height = max.y + min.y;
		halfWidth = width / 2;
		halfHeight = height / 2;

		return outlines;
	}
};

#endif//PHASETEXTGENERATION_HPP