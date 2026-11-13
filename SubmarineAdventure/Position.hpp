#pragma once

#include "Submarine.hpp"

class Position {
private:
	char levelArea[10][10];

public:
	Position(char l[10][10]) {
		for (int i = 0; i < 10; ++i) {
			for (int j = 0; j < 10; ++j) {
				levelArea[i][j] = l[i][j];
			}
		}
	};

	void displayEntireLevel(Submarine& s); // display whole level
	void displayLevelCamera(Submarine& s); //display 5x5 grid of level around submarine
	char charAt(int row, int column); // return a char at a location
	void setCharAt(int row, int column, char newChar); // set a char at a location
};