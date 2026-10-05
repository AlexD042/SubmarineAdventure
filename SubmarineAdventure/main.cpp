#include "Position.hpp"
#include "Treasure.hpp"
#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <limits>

int main() {
	// seed random function
	std::srand(std::time(0));

	bool appRunning = true;

	// APP LOOP
	while (appRunning) {
		std::cout << "*******************************\n";
		std::cout << "Welcome to Submarine Adventure!\n";
		std::cout << "*******************************\n\n";
		std::cout << "1. Start Game\n";
		std::cout << "2. Quit\n\n";
		std::cout << "Enter choice: ";

		std::string menuChoice;
		std::cin >> menuChoice;

		if (menuChoice == "2" || menuChoice == "quit" || menuChoice == "Quit") {
			std::cout << "Thanks for playing!\n";
			appRunning = false;
			break;
		}
		else if (menuChoice == "1" || menuChoice == "start" || menuChoice == "Start") {

			std::system("cls");

			bool isRunning = true;
			Position game;
			Submarine s;
			std::vector<Treasure> possibleTreasures = { Treasure("Gold Coin", 15),
														Treasure("Silver Band", 5) ,
														Treasure("Bejeweled Crown", 50) ,
														Treasure("Diamond of the Ocean", 100) ,
														Treasure("Rock", 1) };
			std::vector<Treasure> treasuresFound = { };

			game.displayLevelCamera(s);
			std::cout << "Oxygen: " << s.getOxygen() << "/50\n\n";

			// GAME LOOP
			while (isRunning) {

				if (s.getOxygen() == 0) {
					std::cout << "Your submarine has run out of oxygen. GAME OVER!\n";
					std::cout << "Total Earnings: $" << s.getTotalEarnings() << "\n\n";

					// Pause so the user can read their score before going back to the menu
					std::cout << "Press Enter to return to the main menu...";
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cin.get();

					std::system("cls"); // Clear screen for the main menu
					isRunning = false;
					break; // Breaks the inner loop, returning to the main menu loop
				}

				int submarineRow = s.getRow();
				int submarineColumn = s.getColumn();

				std::string move;
				std::cout << "\nEnter a move (WASD or INSPECT): ";
				std::cin >> move;

				if (!std::cin) {
					std::cout << "Invalid input.\n";
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					continue;
				}

				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				// Convert to uppercase
				for (char& c : move) {
					c = std::toupper(c);
				}

				// Check if user entered a valid command
				if (move != "W" && move != "A" && move != "S" && move != "D" && move != "INSPECT") {
					std::cout << "Please enter only WASD or INSPECT.\n";
					continue;
				}

				// Move
				if (move == "W") {
					if (submarineRow == 0 || game.charAt(submarineRow - 1, submarineColumn) == '#' || game.charAt(submarineRow - 1, submarineColumn) == '*') {
						std::cout << "You can't move into a wall or off map! Try again!\n";
						std::cout << "Oxygen: " << s.getOxygen() << "/50\n\n";
					}
					else if (submarineRow == 1) { // RETURNING TO THE SURFACE
						s.moveUp();
						s.setOxygen(50);
						std::system("cls");
						game.displayLevelCamera(s);
						std::cout << "You reached the surface!\n";
						std::cout << "Oxygen refilled.\n\n";

						if (!treasuresFound.empty()) {
							std::cout << "Treasure collected:\n";

							int tempEarnings = 0;
							for (Treasure t : treasuresFound) {
								int treasureValue = t.getValue();
								std::cout << t.getName() << ": $" << treasureValue << '\n';
								s.setTotalEarnings(s.getTotalEarnings() + treasureValue);
								tempEarnings += treasureValue;
							}
							std::cout << '\n';
							treasuresFound.clear();

							std::cout << "Earnings this descent: $" << tempEarnings << "\n\n";
						}
						std::cout << "Total Earnings: $" << s.getTotalEarnings() << "\n\n";
						std::cout << "Oxygen: " << s.getOxygen() << "/50\n\n";

					}
					else {
						s.setOxygen(s.getOxygen() - 1);
						s.moveUp();
						std::system("cls");
						game.displayLevelCamera(s);
						std::cout << "Oxygen: " << s.getOxygen() << "/50\n\n";
					}
				}
				else if (move == "A") {
					if (submarineColumn == 0 || game.charAt(submarineRow, submarineColumn - 1) == '#' || game.charAt(submarineRow, submarineColumn - 1) == '*') {
						std::cout << "You can't move into a wall or off the map! Try again!\n";
						std::cout << "Oxygen: " << s.getOxygen() << "/50\n\n";
					}
					else if (submarineRow == 0) {
						s.moveLeft();
						std::system("cls");
						game.displayLevelCamera(s);
						std::cout << "Oxygen: " << s.getOxygen() << "/50\n\n";
					}
					else {
						s.setOxygen(s.getOxygen() - 1);
						s.moveLeft();
						std::system("cls");
						game.displayLevelCamera(s);
						std::cout << "Oxygen: " << s.getOxygen() << "/50\n\n";
					}
				}
				else if (move == "S") {
					if (submarineRow == 9 || game.charAt(submarineRow + 1, submarineColumn) == '#' || game.charAt(submarineRow + 1, submarineColumn) == '*') {
						std::cout << "You can't move into a wall or off the map! Try again!\n";
						std::cout << "Oxygen: " << s.getOxygen() << "/50\n\n";
					}
					else {
						s.setOxygen(s.getOxygen() - 1);
						s.moveDown();
						std::system("cls");
						game.displayLevelCamera(s);
						std::cout << "Oxygen: " << s.getOxygen() << "/50\n\n";
					}
				}
				else if (move == "D") {
					if (submarineColumn == 9 || game.charAt(submarineRow, submarineColumn + 1) == '#' || game.charAt(submarineRow, submarineColumn + 1) == '*') {
						std::cout << "You can't move into a wall or off the map! Try again!\n";
						std::cout << "Oxygen: " << s.getOxygen() << "/50\n\n";
					}
					else if (submarineRow == 0) {
						s.moveRight();
						std::system("cls");
						game.displayLevelCamera(s);
						std::cout << "Oxygen: " << s.getOxygen() << "/50\n\n";
					}
					else {
						s.setOxygen(s.getOxygen() - 1);
						s.moveRight();
						std::system("cls");
						game.displayLevelCamera(s);
						std::cout << "Oxygen: " << s.getOxygen() << "/50\n\n";
					}
				}
				else if (move == "INSPECT") {
					std::cout << "\nYou inspect the area around your submarine...";

					int startRow = submarineRow - 1;
					int startColumn = submarineColumn - 1;

					bool treasureFound = false;

					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							int currentRow = startRow + i;
							int currentColumn = startColumn + j;

							if (currentRow >= 0 && currentRow <= 9 && currentColumn >= 0 && currentColumn <= 9) {
								if (game.charAt(currentRow, currentColumn) == '*' && !possibleTreasures.empty()) {
									treasureFound = true;
									game.setCharAt(currentRow, currentColumn, ' ');
									int randomNumber = std::rand() % possibleTreasures.size();

									std::system("cls");
									game.displayLevelCamera(s);
									std::cout << "Oxygen: " << s.getOxygen() << "/50\n\n";
									std::cout << "\nYou found: " << possibleTreasures[randomNumber].getName() << " (Value: $" << possibleTreasures[randomNumber].getValue() << ")\n\n";

									treasuresFound.push_back(possibleTreasures[randomNumber]);
									possibleTreasures.erase(possibleTreasures.begin() + randomNumber);
								}
							}
						}
					}
					if (treasureFound) {
						treasureFound = false;
					}
					else {
						std::cout << " ...but there was nothing to be found.\n\n\n";
					}
				}
			}
		}
		else {
			std::cout << "Invalid choice. Please try again.\n\n";
		}
	}

	return 0;
}