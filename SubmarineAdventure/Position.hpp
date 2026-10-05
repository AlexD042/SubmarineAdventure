#pragma once

#include "Submarine.hpp"

class Position {
private:
	// Default Start Position
	// '~' = Surface of the water
	// ' ' = Open water
	// '#' = Wall or floor
	// '*' = Treasure
	char level[10][10] = { { '~', '~', '~', '~', '~', '~', '~', '~', '~', '~' }, // row 0
						   { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' }, // row 1
						   { '*', '#', ' ', ' ', ' ', ' ', '*', ' ', ' ', ' ' }, // row 2
						   { '#', '#', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ' }, // row 3
						   { '#', '#', '#', '#', ' ', ' ', '#', ' ', ' ', ' ' }, // row 4
						   { '#', '#', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ' }, // row 5
						   { '#', ' ', ' ', ' ', ' ', '#', '#', '#', ' ', ' ' }, // row 6
						   { '#', '*', ' ', ' ', '*', '#', '#', '#', ' ', ' ' }, // row 7
						   { '#', '#', '#', ' ', '#', '#', '#', '#', '#', '*' }, // row 8
						   { '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' }  // row 9
	}; //    Columns   -->    0    1    2    3    4    5    6    7    8    9

public:
	void displayEntireLevel(Submarine& s); // display whole level
	void displayLevelCamera(Submarine& s); //display 5x5 grid of level around submarine
	char charAt(int row, int column); // return a char at a location
	void setCharAt(int row, int column, char newChar); // set a char at a location
};