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

		std::list<LetterGroup*> letterGroups;
		for (int i = 0; i < lyrics.size(); ++i) {
			std::cout << "Processing lyric: " << i << " / " << lyrics.size() << std::endl;

			LetterGroup* letterGroup = new LetterGroup(letters, lyrics[i]);
			int startDisplay = timings[i].ms;
			int endDisplay = timings[i + 1].ms - Config::I()->mspb / 2;
			letterGroup->display(startDisplay, endDisplay);
				
			if (letterGroups.size() > 0) {
				LetterGroup* compare = letterGroups.back();
				RectPoints compareRect = compare->rectPoints;
				// Forced local rotation
				float localRotation = Config::I()->DToR(rand() % 360 - 180);
				compareRect.LocalRotate(0, 0, localRotation);

				RectPoints centerRect = letterGroup->rectPoints;
				float minDistance = fmin((centerRect.points[0] - centerRect.points[4]).Magnitude(),
					(compareRect.points[0] - compareRect.points[4]).Magnitude());

				bool foundMove = false;
				while (!foundMove) {
					RectPoints centerRectCopy = centerRect;
					RectPoints compareRectCopy = compareRect;
					float distance = minDistance;

					// Chooses random direction to move
					float moveRot = Config::I()->DToR(rand() % 360 - 180);
					Vector3 movement = Vector3(1, 0, 0).Rotate(0, 0, moveRot);
					Vector3 totalMovement = movement;

					// Slowly moves outwards and checks for closest collision
					while (centerRectCopy.Collide(compareRectCopy)) {
						compareRectCopy.Move(movement);
						totalMovement += movement;
					}

					// Skip and recalculate movement if colliding with older letters
					bool skipMove = false;
					for (auto& lg : letterGroups) {
						RectPoints old = lg->rectPoints;
						old.Move(totalMovement);
						old.LocalRotate(0, 0, localRotation);
						if (centerRectCopy.Collide(old)) {
							skipMove = true;
						}
					}
					if (skipMove) {
						continue;
					}

					foundMove = true;
					for (auto& lg : letterGroups) {
						lg->Move(totalMovement);
						lg->LocalRotate(0, 0, localRotation);
						lg->Reposition(timings[i].ms, timings[i].ms + Config::I()->mspb / 2);
						lg->Fade(timings[i].ms, timings[i].ms + 5000, 1.0f);
					}
				}
			}

			letterGroups.push_back(letterGroup);
			// Remove so there aren't too many things we have to move
			if (letterGroups.size() > 3) {
				delete letterGroups.front();
				letterGroups.pop_front();
			}
		}
	}

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

	std::vector<Time> timings = std::vector<Time>({
		Time("01:43:440"), //"LET YOU"
		Time("01:44:071"), //"DIVE AWAY",
		Time("01:45:966"), //"FROM OUR",
		Time("01:46:598"), //"PAINFUL DAYS",
		Time("01:48:493"), //"USO DARAKE",
		Time("01:49:756"), //"NO SABITA",
		Time("01:51:335"), //"HIBI WO",
		Time("01:52:598"), //"UGATTE",
		Time("01:53:545"), //"GET YOUR",
		Time("01:54:177"), //"HIDDEN WAY",
		Time("01:56:071"), //"FROM OUR",
		Time("01:56:703"), //"FLAWLESS MAZE",
		Time("01:58:598"), //"SAGASU",
		Time("02:00:177"), //"WO",
		Time("02:00:493"), //"O",
		Time("02:00:808"), //"O",
		Time("02:01:124"), //"O",
		Time("02:01:440"), //"O",
		Time("02:01:756"), //"O",
		Time("02:02:703"), //"WE'RE",
		Time("02:03:019"), //"BREATHING",
		Time("02:03:335"), //"IN",
		Time("02:03:650"), //"DUALIVE"
		Time("02:06:808")
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
				}

				vectorMap.insert({ pocketVector, points });
			}

			outlines.push_back(vectorMap);
		}

		return outlines;
	}
};

#endif//PHASETEXTGENERATION_HPP