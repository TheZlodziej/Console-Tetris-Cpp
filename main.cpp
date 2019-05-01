#include "Tetris.h"

int main(int argc, char* argv[]) {
	Tetris Game;
	while (Game.isRunning()) {
		Game.update();
	}
}