#pragma once

#include "Submarine.hpp"

#include <vector>
#include <string>

struct Door {
	int row;
	int column;
	int index;

	Door(int r, int c, int i) : row(r), column(c), index(i) {}
};

struct Lever {
	int row;
	int column;
	int index;
	bool isActivated;

	Lever(int r, int c, int i, bool a) : row(r), column(c), index(i), isActivated(a) {}
};

class Position {
private:
	std::vector<Lever> levers;
	std::vector<Door> doors;

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
	bool isObstacle(int row, int column); // return true if a location has an obstacle

	void addDoor(int row, int column, int index);
	void addLever(int row, int column, int index);
	int getDoorIndex(int row, int column);
	std::string toggleLever(int row, int column);
};