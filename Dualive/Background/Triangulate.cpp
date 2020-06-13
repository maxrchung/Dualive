#include "Triangulate.hpp"
#include "Sprite.hpp"

#include <list>
#include <png.h>

Triangulate::Triangulate() {
	auto bg = PNGWrapper("background.png");
	
	Time start("00:00:000");
	Time end("01:00:000");

	auto points = poissonDisk(3);
	auto scale = 15;
	auto scaleDifference = 5;
	float imageSize = 1000;
	fisherYates(points);

	auto numRects = points.size();
	
	for (auto i = 0; i < numRects; i++) {
		auto point = points.back();
		auto sprite = new Sprite("triangulate.png", point);

		auto variance = (rand() % scaleDifference) - (scaleDifference / 2.0f);
		auto endScale = (scale + variance) / imageSize;
		endScale = scale / imageSize;
		sprite->Scale(start.ms, end.ms, endScale, endScale);

		auto rotation = (rand() % 314) / 100.0f;
		sprite->Rotate(start.ms, end.ms, rotation, rotation);

		Color color = GetFromPNG(bg, point);
		sprite->Color(start.ms, end.ms, color, color);

		points.pop_back();
	}
}

Color Triangulate::GetFromPNG(const PNGWrapper& bg, Vector2 point) const {
	auto x = point.x + 854 / 2;
	// Flip to account for PNG coordinates
	auto y = -point.y + 239;
	auto color = bg.Get(x, y);
	return color;
}

void Triangulate::fisherYates(std::vector<Vector2>& points) {
	for (auto i = points.size() - 1; i >= 1; --i) {
		auto random = rand() % (i + 1);
		auto temp = points[i];
		points[i] = points[random];
		points[random] = temp;
	}
}

std::vector<Vector2> Triangulate::poissonDisk(float minDist, int maxTries) const {
	BoundingRectangle bounds({
		Vector2(0, 0),
		Vector2(853, 0),
		Vector2(853, 480),
		Vector2(0, 480)
	});

	auto cellSize = minDist / sqrtf(2);
	auto widthCount = bounds.width / cellSize + 1;
	auto heightCount = bounds.height / cellSize + 1;
	auto grid = std::vector<std::vector<bool>>(widthCount, std::vector<bool>(heightCount, false));

	// Start with one active point
	auto active = std::vector<Vector2> {
		Vector2(rand() % 853, rand() % 480)
	};

	std::vector<Vector2> total;
	while (!active.empty()) {
		auto tries = 0;
		auto sample = active.back();
		while (tries++ < maxTries) {
			auto dist = rand() % (int)minDist + minDist;
			auto degrees = rand() % 360 * 3.1416f / 180.0f;
			auto rotated = Vector2(dist, 0).Rotate(degrees);
			auto next = sample + rotated;
			
			if (!bounds.Contains(next)) {
				continue;
			}

			auto x = (int)(next.x / cellSize);
			auto y = (int)(next.y / cellSize);

			if (grid[x][y]) {
				continue;
			}

			grid[x][y] = true;
			active.push_back(next);
			total.push_back(Vector2((int)next.x - 427, (int)next.y - 240));
		}
		active.pop_back();
	}

	return total;
}

