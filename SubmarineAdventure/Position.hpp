#pragma once

#include <iostream>

class Position {
private:
	// Default Start Position
	// '~' = Surface of the water
	// ' ' = Open water
	// '#' = Wall or floor
	char level[10][10] = { { '~', '~', '~', '~', '@', '~', '~', '~', '~', '~' },
						   { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
						   { ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
						   { '#', '#', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ' },
						   { '#', '#', '#', '#', ' ', ' ', '#', ' ', ' ', ' ' },
						   { '#', '#', ' ', '#', ' ', ' ', '#', ' ', ' ', ' ' },
						   { '#', ' ', ' ', ' ', ' ', '#', '#', '#', ' ', ' ' },
						   { '#', ' ', ' ', ' ', ' ', '#', '#', '#', ' ', ' ' },
						   { '#', '#', '#', ' ', '#', '#', '#', '#', '#', ' ' },
						   { '#', '#', '#', '#', '#', '#', '#', '#', '#', '#' } 
	};

public:
	void displayEntireLevel() {
		for (int row = 0; row < 10; row++) {
			for (int column = 0; column < 10; column++) {
				std::cout << level[row][column];
			}
			std::cout << '\n';
		}
	}

};