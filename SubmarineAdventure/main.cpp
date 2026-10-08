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
		std::cout << "2. Quit Game\n\n";
		std::cout << "Enter choice (enter either '1' or '2'): ";

		std::string menuChoice;
		std::cin >> menuChoice;

		if (menuChoice == "2") {
			std::cout << "Thanks for playing!\n";
			appRunning = false;
			break;
		}
		else if (menuChoice == "1") {

			std::system("cls");

			bool isRunning = true;
			Position game;
			Submarine s;

			// Treasure objects
			std::vector<Treasure> possibleTreasures = { Treasure("Gold Coin", 15),
														Treasure("Silver Band", 5) ,
														Treasure("Bejeweled Crown", 50) ,
														Treasure("Diamond of the Ocean", 100) ,
														Treasure("Rock", 1) };
			// Submarine cargo
			std::vector<Treasure> treasuresFound = { };

			// Non-treasure objects
			std::vector<std::string> sceneryObjects = { "an ancient skeleton",
														"a rusted ship anchor",
														"a bed of coral",
														"some glowing underwater crystals",
														"an empty diving suit" };

			// Keep track of which scenery spawned at each map coordinate
			std::string assignedScenery[10][10];

			game.displayLevelCamera(s);
			std::cout << "Oxygen: " << s.getOxygen() << "/50\n\n";

			// GAME LOOP
			while (isRunning) {

				if (s.getOxygen() == 0) {
					std::cout << "Your submarine has run out of oxygen. GAME OVER!\n";
					std::cout << "Total Earnings: $" << s.getTotalEarnings() << "\n\n";

					// Pause so user can read
					std::cout << "Press Enter to return to the main menu...";
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					std::cin.get();

					std::system("cls");
					isRunning = false;
					break; // return to the main menu
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

				// Move Up
				if (move == "W") {
					if (submarineRow == 0 || game.charAt(submarineRow - 1, submarineColumn) == '#' || game.charAt(submarineRow - 1, submarineColumn) == '*' || game.charAt(submarineRow - 1, submarineColumn) == '^') {
						std::cout << "You can't move into an obstacle or off map! Try again!\n";
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
				// Move left
				else if (move == "A") {
					if (submarineColumn == 0 || game.charAt(submarineRow, submarineColumn - 1) == '#' || game.charAt(submarineRow, submarineColumn - 1) == '*' || game.charAt(submarineRow, submarineColumn - 1) == '^') {
						std::cout << "You can't move into an obstacle or off the map! Try again!\n";
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
				// Move down
				else if (move == "S") {
					if (submarineRow == 9 || game.charAt(submarineRow + 1, submarineColumn) == '#' || game.charAt(submarineRow + 1, submarineColumn) == '*' || game.charAt(submarineRow + 1, submarineColumn) == '^') {
						std::cout << "You can't move into an obstacle or off the map! Try again!\n";
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
				// Move right
				else if (move == "D") {
					if (submarineColumn == 9 || game.charAt(submarineRow, submarineColumn + 1) == '#' || game.charAt(submarineRow, submarineColumn + 1) == '*' || game.charAt(submarineRow, submarineColumn + 1) == '^') {
						std::cout << "You can't move into an obstacle or off the map! Try again!\n";
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
				// Inspecting move
				else if (move == "INSPECT") {
					std::system("cls");
					game.displayLevelCamera(s);
					std::cout << "Oxygen: " << s.getOxygen() << "/50\n\n";
					std::cout << "You inspect the area around your submarine...\n\n";

					int startRow = submarineRow - 1;
					int startColumn = submarineColumn - 1;

					bool foundSomething = false;

					// Look at 3x3 grid around submarine
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							int currentRow = startRow + i;
							int currentColumn = startColumn + j;

							if (currentRow >= 0 && currentRow <= 9 && currentColumn >= 0 && currentColumn <= 9) {

								// Inspecting treasure (*)
								if (game.charAt(currentRow, currentColumn) == '*' && !possibleTreasures.empty()) {
									foundSomething = true;
									game.setCharAt(currentRow, currentColumn, ' '); // Remove from map
									int randomNumber = std::rand() % possibleTreasures.size();

									std::cout << " - You found treasure: " << possibleTreasures[randomNumber].getName() << " (Value: $" << possibleTreasures[randomNumber].getValue() << ")\n";

									treasuresFound.push_back(possibleTreasures[randomNumber]);
									possibleTreasures.erase(possibleTreasures.begin() + randomNumber);
								}
								// Inspecting non-treasure (^)
								else if (game.charAt(currentRow, currentColumn) == '^') {
									foundSomething = true;

									// If this coordinate hasn't been assigned yet, assign it
									if (assignedScenery[currentRow][currentColumn].empty()) {
										int randomScenery = std::rand() % sceneryObjects.size();
										assignedScenery[currentRow][currentColumn] = sceneryObjects[randomScenery];
									}
									std::cout << " - You investigate a strange object... You find " << assignedScenery[currentRow][currentColumn] << ".\n";
								}
							}
						}
					}

					if (!foundSomething) {
						std::cout << "...but there was nothing to be found.\n";
					}
					std::cout << "\n";
				}
			}
		}
		else {
			std::system("cls");
			std::cout << "Invalid choice. Please try again.\n\n";
		}
	}

	return 0;
}