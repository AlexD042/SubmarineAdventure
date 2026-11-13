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
				std::cout << levelArea[row][column] << ' ';
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
				std::cout << levelArea[currentRow][currentColumn] << ' ';
			}
		}
		std::cout << "|\n";
	}
	std::cout << "-------------\n";
}

char Position::charAt(int row, int column) {
	return levelArea[row][column];
}

void Position::setCharAt(int row, int column, char newChar) {
	levelArea[row][column] = newChar;
}

bool Position::isObstacle(int row, int column) {
	char c = charAt(row, column);
	return (c == '#' || c == '*' || c == '^' || c == '|' || c == '\\' || c == '/');
}

void Position::addDoor(int row, int column, int index) {
	doors.push_back(Door(row, column, index));
}
void Position::addLever(int row, int column, int index) {
	levers.push_back(Lever(row, column, index, false));
}

std::string Position::toggleLever(int r, int c) {
	for (Lever& l : levers) {
		if (l.row == r && l.column == c) {

			l.isActivated = !l.isActivated;

			if (l.isActivated) {
				setCharAt(r, c, '/');
			}
			else {
				setCharAt(r, c, '\\');
			}

			for (Door& d : doors) {
				if (d.index == l.index) {
					if (l.isActivated) {
						setCharAt(d.row, d.column, ' ');
					}
					else {
						setCharAt(d.row, d.column, '|');
					}
				}
			}

			if (l.isActivated) {
				return "Lever " + std::to_string(l.index) + " used! Corresponding doors have opened.";
			}
			else {
				return "Lever " + std::to_string(l.index) + " used! Corresponding doors have closed.";
			}
		}
	}
	return "";
}

int Position::getDoorIndex(int row, int column) {
	for (Door& d : doors) {
		if (d.row == row && d.column == column) {
			return d.index;
		}
	}
	return -1;
}