#pragma once

#include <iostream>

#include "Submarine.hpp"

class Position {
private:
	// Default Start Position
	// '~' = Surface of the water
	// ' ' = Open water
	// '#' = Wall or floor
	char level[10][10] = { { '~', '~', '~', '~', '~', '~', '~', '~', '~', '~' }, // row 0
						   { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' }, // row 1
						   { ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' }, // row 2
						   { '#', '#', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ' }, // row 3
						   { '#', '#', '#', '#', ' ', ' ', '#', ' ', ' ', ' ' }, // row 4
						   { '#', '#', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ' }, // row 5
						   { '#', ' ', ' ', ' ', ' ', '#', '#', '#', ' ', ' ' }, // row 6
						   { '#', ' ', ' ', ' ', ' ', '#', '#', '#', ' ', ' ' }, // row 7
						   { '#', '#', '#', ' ', '#', '#', '#', '#', '#', ' ' }, // row 8
						   { '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' } // row 9
	}; //    Columns   -->    0    1    2    3    4    5    6    7    8    9

public:
	void displayEntireLevel(Submarine& s) {
		std::cout << "   Current Position\n";
		std::cout << "_______________________\n";
		for (int row = 0; row < 10; row++) {
			std::cout << "| ";
			for (int column = 0; column < 10; column++) {
				if (s.getRow() == row && s.getColumn() == column) {
					std::cout << '@' << ' ';
				}
				else {
					std::cout << level[row][column] << ' ';
				}
			}
			std::cout << "|\n";
		}
		std::cout << "-----------------------\n";
	}

};