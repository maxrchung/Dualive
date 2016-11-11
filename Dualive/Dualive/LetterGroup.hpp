#ifndef LETTERGROUP_HPP
#define LETTERGROUP_HPP

#include "Config.hpp"
#include "Letter.hpp"
#include "RectPoints.hpp"

class LetterGroup {
public:
	LetterGroup(std::vector<Letter>& lettersBase, std::string& lyric);
	void display(int startTime, int endTime);
	void Color(int startTime, int endTIme, Color color);
	void Move(Vector3 movement);
	void Rotate(Vector3 rotAmounts);
	void Rotate(float xRot, float yRot, float zRot);
	void LocalRotate(float xRot, float yRot, float zRot);
	void Reposition(int startTime, int endTime, Easing easing = Easing::Linear);
	void Fade(int startTime, int endTime, float fade, Easing easing = Easing::Linear);

	RectPoints rectPoints;

private:
	void setupPair3s(std::vector<std::vector<Pair>>& pairTravel);

	// Using pointers because I think the simplest way to handle
	// spaces is by using NULL
	std::vector<Letter*> letters;
	std::vector<Sprite*> sprites;
	std::vector<Pair3> pair3s;
	
	// Random vector of indices that determine which sprite index should be disabled
	std::vector<int> disableIndices;
	// We separate by marked and disable because the former will trigger the fading to begin
	std::vector<bool> markedReference;
	std::vector<bool> disableReference;

	static int spaceWidth;
	static int verticalDisplacement;
	static float widthMax;
	static float heightMax;
};

#endif//LETTERGROUP_HPP