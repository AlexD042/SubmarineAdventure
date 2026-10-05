#include "Position.hpp"

#include <iostream>

void Position::displayEntireLevel(Submarine& s) {
	int submarineRow = s.getRow();
	int submarineColumn = s.getColumn();

	std::cout << "   Current Position\n";
	std::cout << "_______________________\n";
	for (int row = 0; row < 10; row++) {
		std::cout << "| ";
		for (int column = 0; column < 10; column++) {
			if (submarineRow == row && submarineColumn == column) {
				std::cout << "@ ";
			}
			else {
				std::cout << level[row][column] << ' ';
			}
		}
		std::cout << "|\n";
	}
	std::cout << "-----------------------\n";
}

void Position::displayLevelCamera(Submarine& s) {
	int submarineRow = s.getRow();
	int submarineColumn = s.getColumn();

	int startRow = submarineRow - 2;
	int startColumn = submarineColumn - 2;

	// checks for if the submarine is close to the edge of the map and corrects starting row or column
	if (startRow < 0) {
		startRow = 0;
	}
	if (startColumn < 0) {
		startColumn = 0;
	}
	if (startRow > 5) {
		startRow = 5;
	}
	if (startColumn > 5) {
		startColumn = 5;
	}

	std::cout << " Camera View\n";
	std::cout << "_____________\n";
	for (int i = 0; i < 5; i++) {
		std::cout << "| ";
		for (int j = 0; j < 5; j++) {
			int currentRow = startRow + i;
			int currentColumn = startColumn + j;

			if (currentRow == submarineRow && currentColumn == submarineColumn) {
				std::cout << "@ ";
			}
			else {
				std::cout << level[currentRow][currentColumn] << ' ';
			}
		}
		std::cout << "|\n";
	}
	std::cout << "-------------\n";
}

char Position::charAt(int row, int column) {
	return level[row][column];
}

void Position::setCharAt(int row, int column, char newChar) {
	level[row][column] = newChar;
}