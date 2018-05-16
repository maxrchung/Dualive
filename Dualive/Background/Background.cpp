#include "Storyboard.hpp"
#include "Triangulate.hpp"

int main() {
	Sprite* bg = new Sprite("Storyboard\\Background\\Blank.png", Vector2::Zero, Layer::Background);
	bg->ScaleVector(0, 0, Vector2::ScreenSize, Vector2::ScreenSize);
	bg->Color(0, 60000, Color(255), Color(255));
	Triangulate();

	Storyboard::Instance()->Write(R"(X:\osu!\Songs\474742 Quarks - Dualive\Quarks - Dualive (Osuuki).osb)");
	return 0;
}