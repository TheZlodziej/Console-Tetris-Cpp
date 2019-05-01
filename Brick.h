#pragma once
#include <vector>
#include <cstdlib>
#include <time.h>
#include <iostream>
#include <algorithm>
#include "Coords.h"
#include "Map.h"

class Brick {
private:
	std::vector<Coords> body;
	Map& map;
	char brickChar = 'x';
	std::string currentRotation = "TOP";

public:
	enum BrickType { O, T, S, Z, J, L };

	Brick(BrickType type, Map* mapRef);
	~Brick();

	Coords newBrickCoords(int x, int y);
	bool move(const char* dir);
	void rotate();
	void draw();
	std::vector<Coords> getBody();
	bool canMove(Coords pos);
	bool moveDown();
	void clear();
	Map& getMap();
};