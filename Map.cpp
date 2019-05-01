#include "Map.h"

Map::Map() {
	cols = sizeof map / sizeof map[0];
	rows = sizeof map[0] / sizeof(char);

	mapChar = ' ';
	borderChar = '/';

	map[0][0] = mapChar; //just to hide in error list

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			map[j][i] = mapChar;
		}
	}
}

Map::~Map() { }

void Map::draw() { 
	system("cls");
	//map itself
	for (int i = 0; i < rows; i++) {
		std::cout << borderChar << " "; //left border
		for (int j = 0; j < cols; j++) {
			if (i == 0) {
				//top border
				std::cout << borderChar << " ";
				continue;
			}
			std::cout << map[j][i] << " ";
		}
		std::cout << borderChar << " "; //right border
		std::cout << std::endl;
	}
	//bottom border
	for (int i = 0; i < cols + 2; i++) {
		std::cout << borderChar << " ";
	}
}

void Map::changeValue(Coords pos, char newChar) { map[pos.x][pos.y] = newChar; }

int Map::getValue(const char* name) {
	if (name == "COLS")
		return cols;

	if (name == "ROWS")
		return rows;

	return 0;
}

char Map::getChar(const char* name) {
	if (name == "MAP")
		return mapChar;

	if (name == "BORDER")
		return borderChar;

	return 'x';
}

char Map::getMapVal(Coords pos) { return map[pos.x][pos.y]; }

int Map::shiftDown() {
	int scoreCounter = 0;
	for (int i = 0; i < rows; i++) {
		bool removeRow_ = true;
		for (int j = 0; j < cols; j++) {
			if (map[j][i] == mapChar)
				removeRow_ = false;
		}
		if (removeRow_) {
			removeRow(i);
			scoreCounter++;
		}
	}

	return scoreCounter;
}

void Map::removeRow(int row) {
	for (int i = row; i > 0; i--) {
		for (int j = 0; j < cols; j++) {
			map[j][i] = map[j][i - 1];
		}
	}
}