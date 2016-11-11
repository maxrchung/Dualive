#ifndef PHASETEXTGENERATION_HPP
#define PHASETEXTGENERATION_HPP

#include "Config.hpp"
#include "LetterGroup.hpp"

class PhaseTextGeneration {
public:
	PhaseTextGeneration() {
		std::string glyphDataPath = R"(C:\Users\Wax Chug da Gwad\Desktop\Dualive\Dualive\Debug\GlyphOutlineData.txt)";
		std::vector<VectorMap> outlines = loadOutlinesData(glyphDataPath);

		std::vector<Letter> letters;
		for (auto& vectorMap : outlines) {
			letters.push_back(Letter(vectorMap));
		}

	    int foregroundColor = (int)GC::IFPLUTOWASAPLANET;

		std::list<LetterGroup*> letterGroups;
		for (int i = 0; i < lyrics.size(); ++i) {
			std::cout << "Processing lyric: " << i << " / " << lyrics.size() << std::endl;
			
			LetterGroup* letterGroup = new LetterGroup(letters, lyrics[i]);
			int startDisplay = timings[i].ms - Config::I()->mspb;
			int endDisplay = timings[i + 1].ms - Config::I()->mspb;
			letterGroup->display(startDisplay, endDisplay);
			letterGroup->Color(startDisplay, endDisplay, GetColor[(GC)foregroundColor]);
			if (i != 0) {
				foregroundColor += 2;
			}
			else {
				++foregroundColor;
			}

			// Fade out last Dualive
			if (i == lyrics.size() - 1) {
				letterGroup->Fade(Time("02:05:545").ms, Time("02:06:808").ms, 0.0f, Easing::CubicIn);
			}

			if (letterGroups.size() > 0) {
				RectPoints centerRect = letterGroup->rectPoints;
				RectPoints compareRect = letterGroups.back()->rectPoints;

				float minDistance = fmin((centerRect.points[0] - centerRect.points[3]).Magnitude(),
					(compareRect.points[0] - compareRect.points[3]).Magnitude());

				bool foundMove = false;
				while (!foundMove) {
					RectPoints centerRectCopy = centerRect;
					RectPoints compareRectCopy = compareRect;

					// Forced local rotation
					Vector3 rotAmounts(0, 0, Config::I()->DToR(rand() % 120 - 60));
					compareRectCopy.Rotate(rotAmounts);

					// Chooses random direction to move
					// Do not go to edges
					Vector3 moveAmounts(0, 0, Config::I()->DToR(rand() % 160 + 10));
					// Flip on each word
					if (i % 2 == 0) {
						moveAmounts *= -1;
					}

					Vector3 movement = Vector3(minDistance, 0, 0).Rotate(moveAmounts.x, moveAmounts.y, moveAmounts.z);
					Vector3 totalMovement = movement;
					Vector3 increment = Vector3(1, 0, 0).Rotate(moveAmounts.x, moveAmounts.y, moveAmounts.z);
					compareRectCopy.Move(movement);

					// Slowly moves outwards and checks for closest collision
					while (centerRectCopy.Collide(compareRectCopy)) {
						compareRectCopy.Move(increment);
						totalMovement += increment;
					}
					totalMovement += increment * bufferDistance;

					// Skip and recalculate movement if colliding with older letters
					bool skipMove = false;
					for (auto& lg : letterGroups) {
						RectPoints old = lg->rectPoints;
						old.Rotate(rotAmounts);
						old.Move(totalMovement);
						if (centerRectCopy.Collide(old)) {
							skipMove = true;
							break;
						}
					}
					if (skipMove) {
						continue;
					}

					foundMove = true;
					for (auto& lg : letterGroups) {
						lg->Rotate(rotAmounts);
						lg->Move(totalMovement);
						lg->Reposition(timings[i].ms - Config::I()->mspb, timings[i].ms, Easing::CubicOut);
					}
				}
			}

			letterGroups.push_back(letterGroup);
			// Remove so there aren't too many things we have to move
			if (letterGroups.size() > Config::I()->afterImages) {
				delete letterGroups.front();
				letterGroups.pop_front();
			}
		}
	}

	std::vector<Time> static timings;

private:
	std::vector<std::string> lyrics = std::vector<std::string>({
		"LET YOU",
		"DIVE AWAY",
		"FROM OUR",
		"PAINFUL DAYS",
		"USO DARAKE",
		"NO SABITA",
		"HIBI WO",
		"UGATTE",
		"GET YOUR",
		"HIDDEN WAY",
		"FROM OUR",
		"FLAWLESS MAZE",
		"SAGASU",
		"WO",
		"O",
		"O",
		"O",
		"O",
		"O",
		"WE'RE",
		"BREATHING",
		"IN",
		"DUALIVE"
	});

	float bufferDistance = 20.0f;

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
				}

				vectorMap.insert({ pocketVector, points });
			}

			outlines.push_back(vectorMap);
		}

		return outlines;
	}
};

#endif//PHASETEXTGENERATION_HPP