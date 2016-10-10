#ifndef LETTERGROUP_HPP
#define LETTERGROUP_HPP

#include "Config.hpp"
#include "Letter.hpp"

class LetterGroup {
public:
	LetterGroup(std::vector<Letter>& lettersBase, std::string& lyric);
	static void display(LetterGroup& letterGroup, int startTime, int endTime);

private:
	// Using pointers because I think the simplest way to handle
	// spaces is by using NULL
	std::vector<Letter*> letters;
	std::vector<Sprite*> sprites;

	static int spaceWidth;
	static int verticalDisplacement;
	static float widthMax;
	static float heightMax;
};

#endif//LETTERGROUP_HPP