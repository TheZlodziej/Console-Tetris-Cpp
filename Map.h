#pragma once
#include "Coords.h"
#include <algorithm>
#include <iostream>

class Map {
private:
	char map[16][20]; //[cols][rows]
	char mapChar;
	char borderChar;
	int cols;
	int rows;

public:
	Map();
	~Map();

	void draw();
	void changeValue(Coords pos, char newChar);
	void removeRow(int row);
	int shiftDown();
	int getValue(const char* name);
	char getChar(const char* name);
	char getMapVal(Coords pos);

};