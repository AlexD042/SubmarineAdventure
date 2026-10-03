#include "Position.hpp"

int main() {
	bool isRunning = true;
	Position game;
	Submarine s;
	std::cout << "*******************************\n";
	std::cout << "Welcome to Submarine Adventure!\n";
	std::cout << "*******************************\n\n";
	game.displayLevelCamera(s);
	while (isRunning) {
		char move;
		std::cout << "\nEnter a move: ";
		std::cin >> move;
		if (!std::cin) {
			std::cout << "Invalid input.\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		// check for if user enetered more than one character
		if (std::cin.get() != '\n') {
			std::cout << "Invalid input. Please enter only one character.\n";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		// check if user entered a correct character
		move = std::toupper(move);
		if (move == 'W' || move == 'A' || move == 'S' || move == 'D') {
			std::cout << "You chose: " << move << '\n';
		}
		else {
			std::cout << "Please enter only WASD.\n";
			continue;
		}

		switch (move) {
		case 'W':
			if (s.getRow() == 0 || game.charAt(s.getRow() - 1, s.getColumn()) == '#') {
				std::cout << "You can't move into a wall or off map! Try again!\n";
			}
			else {
				s.moveUp();
				std::system("cls");
				game.displayLevelCamera(s);
			}
			break;
		case 'A':
			if (s.getColumn() == 0 || game.charAt(s.getRow(), s.getColumn() - 1) == '#') {
				std::cout << "You can't move into a wall or off the map! Try again!\n";
			}
			else {
				s.moveLeft();
				std::system("cls");
				game.displayLevelCamera(s);
			}
			break;
		case 'S':
			if (s.getRow() == 9 || game.charAt(s.getRow() + 1, s.getColumn()) == '#') {
				std::cout << "You can't move into a wall or off the map! Try again!\n";
			}
			else {
				s.moveDown();
				std::system("cls");
				game.displayLevelCamera(s);
			}
			break;
		case 'D':
			if (s.getColumn() == 9 || game.charAt(s.getRow(), s.getColumn() + 1) == '#') {
				std::cout << "You can't move into a wall or off the map! Try again!\n";
			}
			else {
				s.moveRight();
				std::system("cls");
				game.displayLevelCamera(s);
			}
			break;
		default:
			break;
		}
	}
}