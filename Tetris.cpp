#include "Tetris.h"

Tetris::Tetris() {
	Alive = true;
	brick = nullptr;
	score = 0;
	delay = 150;
	addNewBrick();
};

Tetris::~Tetris() {};

Brick::BrickType Tetris::getRandomBrickType() {
	srand(time(NULL));
	return Brick::BrickType(rand() % 6);
}

bool Tetris::lost() {
	for (auto i : brick->getBody()) {
		if (i.y <= 0)
			return true;
	}
	return false;
}

void Tetris::addNewBrick() {
	delete brick;
	brick = new Brick(getRandomBrickType(), &map);
}

bool Tetris::isRunning() {
	if (Alive) return true;

	system("cls");
	std::cout << std::endl;
	for (int i = 0; i < map.getValue("ROWS") / 2 - 1; i++) std::cout << std::endl;
	for (int i = 0; i < map.getValue("COLS") / 2 - 4; i++) std::cout << " ";
	std::cout << "Game Over!" << std::endl;
	for (int i = 0; i < map.getValue("COLS") / 2 - 4; i++) std::cout << " ";
	std::cout << "Score: " << score;
	for (int i = 0; i < map.getValue("ROWS") / 2 - 1; i++) std::cout << std::endl;

	return false;
}

void Tetris::drawScore() {
	std::cout << std::endl;
	std::cout << std::endl;
	for (int i = 0; i < map.getValue("COLS") - 3; i++) std::cout << " "; //not divided by 2 because every map character there comes a space
	std::cout << "Score: " << score;
	std::cout << std::endl;
}

void Tetris::keyboardInput() {
	if (GetAsyncKeyState(VK_LEFT) & 0x8000 || GetAsyncKeyState('A'))
		brick->move("LEFT");
	
	else if (GetAsyncKeyState(VK_RIGHT) & 0x8000 || GetAsyncKeyState('D'))
		brick->move("RIGHT");
	
	else if (GetAsyncKeyState(VK_UP) & 0x8000 || GetAsyncKeyState('W'))
		brick->rotate();

	else if (GetAsyncKeyState(VK_DOWN) & 0x8000 || GetAsyncKeyState('S'))
		brick->moveDown();

	brick->draw();
}

void Tetris::update() {
	score++;
	keyboardInput();
	map.draw();

	if (!brick->moveDown()) {
			score += 100 * map.shiftDown();

		if (lost())
			Alive = false;

		addNewBrick();
		return;
	}
	
	drawScore();
	Sleep(delay);
}
