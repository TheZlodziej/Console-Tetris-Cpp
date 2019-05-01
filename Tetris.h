#pragma once
#include <Windows.h>
#include <stdlib.h>
#include "Map.h"
#include "Brick.h"

class Tetris {
private:
	bool Alive;
	int delay; //ms
	int score;
	Map map;
	Brick* brick;

public:
	Tetris();
	~Tetris();

	Brick::BrickType getRandomBrickType();
	bool lost();
	void addNewBrick();
	bool isRunning();
	void keyboardInput();
	void update();
	void drawScore();
};