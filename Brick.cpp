#include "Brick.h"

/*
	O:
		#
	# # #

	//////

	T:
	  # #
	# #

	//////

	S:
	# #
	# #

	//////

	Z:
	  #
	# # #

	//////

	J:
	# # # #

	//////

	L:
	#
	# # #

	//////

*/

Brick::Brick(BrickType type, Map* mapRef = nullptr) : map(*mapRef) {

	int mapCenter = map.getValue("COLS") / 2;

	switch (type) {
	case O:
		body.push_back(newBrickCoords(mapCenter + 1, 0));
		body.push_back(newBrickCoords(mapCenter - 1, 1));
		body.push_back(newBrickCoords(mapCenter, 1));
		body.push_back(newBrickCoords(mapCenter + 1, 1));

		break;

	case T:
		body.push_back(newBrickCoords(mapCenter, 0));
		body.push_back(newBrickCoords(mapCenter + 1, 0));
		body.push_back(newBrickCoords(mapCenter - 1, 1));
		body.push_back(newBrickCoords(mapCenter, 1));

		break;

	case S:
		body.push_back(newBrickCoords(mapCenter, 0));
		body.push_back(newBrickCoords(mapCenter + 1, 0));
		body.push_back(newBrickCoords(mapCenter, 1));
		body.push_back(newBrickCoords(mapCenter + 1, 1));

		break;

	case Z:
		body.push_back(newBrickCoords(mapCenter, 0));
		body.push_back(newBrickCoords(mapCenter - 1, 1));
		body.push_back(newBrickCoords(mapCenter, 1));
		body.push_back(newBrickCoords(mapCenter + 1, 1));

		break;

	case J:
		body.push_back(newBrickCoords(mapCenter - 2, 0));
		body.push_back(newBrickCoords(mapCenter - 1, 0));
		body.push_back(newBrickCoords(mapCenter, 0));
		body.push_back(newBrickCoords(mapCenter + 1, 0));

		break;

	case L:
		body.push_back(newBrickCoords(mapCenter - 1, 0));
		body.push_back(newBrickCoords(mapCenter - 1, 1));
		body.push_back(newBrickCoords(mapCenter, 1));
		body.push_back(newBrickCoords(mapCenter + 1, 1));

		break;

	default:
		break;
	}
};

Brick::~Brick() {};

void Brick::draw() {
	for (auto c : body) {
		map.changeValue(c, brickChar);
	}
}

Coords Brick::newBrickCoords(int x, int y){
	return { x, y };
}

void Brick::clear() {
	//clear old brick body
	for (auto c : body) {
		map.changeValue(c, map.getChar("MAP"));
	}
}

std::vector<Coords> Brick::getBody() { return body; }

Map& Brick::getMap() { return map; }

void Brick::rotate() {
	clear();
	Coords pivot = body[3];
	Coords rotation[2] = { {0, 1}, {-1, 0} };

	bool canRotate = false;
	std::vector<Coords> copy = body;

	for (auto& e : body) {
		Coords relativeVecotr = { e.x - pivot.x, e.y - pivot.y };
		Coords transformVector = { rotation[0].x * relativeVecotr.x + rotation[0].y * relativeVecotr.y,
								   rotation[1].x * relativeVecotr.x + rotation[1].y * relativeVecotr.y };
		e.x = pivot.x + transformVector.x;
		e.y = pivot.y + transformVector.y;

		if (e.x >= map.getValue("COLS") || e.x < 0 || !canMove(e) || e.y >= map.getValue("ROWS")) {
			body = copy;
			break;
		}
	}
}

bool Brick::canMove(Coords pos) {
	for (auto c : body) {
		bool belongsToBody = false;
		for (auto c_ : body) {
			if (pos.x == c_.x && pos.y == c_.y) {
				belongsToBody = true;
				break;
			}
		}

		if (!belongsToBody) {
			if (map.getMapVal(pos) == brickChar) {
				return false;
			}
		}
	}
	return true;
}

bool Brick::move(const char* dir) {
	bool canMove_ = false;

	if (dir == "LEFT") {
		canMove_ = std::none_of(body.begin(), body.end(), [](Coords c) { return c.x <= 0; });
		if (canMove_) {
			for (auto c : body) {
				canMove_ = canMove({ c.x - 1, c.y });
				if (!canMove_) break;
			}
		}
		if (canMove_) {
			clear();
			for (auto& c : body) {
				c.x--;
			}
		}
	}
	else if (dir == "RIGHT") {
		int cols = map.getValue("COLS") - 1;
		canMove_ = std::none_of(body.begin(), body.end(), [cols](Coords c) { return c.x >= cols; });

		if (canMove_) {
			for (auto c : body) {
				canMove_ = canMove({ c.x + 1, c.y });
				if (!canMove_) break;
			}
		}

		if (canMove_) {
			clear();
			for (auto& c : body) {
				c.x++;
			}
		}
	}

	else if (dir == "BOTTOM") {
		int rows = map.getValue("ROWS");
		canMove_ = std::none_of(body.begin(), body.end(), [rows](Coords c) { return c.y + 1 >= rows; });
		if (canMove_) {
			for (auto c : body) {
				canMove_ = canMove({ c.x, c.y + 1 });
				if (!canMove_) break;
			}
		}

		if (canMove_) {
			clear();
			for (auto& c : body) {
				c.y++;
			}
		}
	}

	return canMove_;
}

bool Brick::moveDown() {
	if (!move("BOTTOM"))
		return false;
	draw();
	return true;
}