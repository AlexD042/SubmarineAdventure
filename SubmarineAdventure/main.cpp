#include "Position.hpp"
#include "Treasure.hpp"
#include "Levels.hpp"
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

			Position map[2][3] = { { Position(levelAreaR0C0), Position(levelAreaR0C1), Position(levelAreaR0C2) },
								   { Position(levelAreaR1C0), Position(levelAreaR1C1), Position(levelAreaR1C2) }
			}; // map has 6 areas -> 2 rows and 3 columns

			int currentAreaRow = 0;
			int currentAreaColumn = 1; // starting area

			Position* currentArea = &map[currentAreaRow][currentAreaColumn];
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

			map[1][2].addDoor(4, 4, 1);
			map[1][2].addDoor(5, 4, 1);
			map[1][2].addDoor(6, 4, 1);
			map[1][2].addLever(7, 6, 1);

			currentArea->displayLevelCamera(s);
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
					if (submarineRow == 0) {
						if (currentAreaRow == 1) {
							currentAreaRow--;
							currentArea = &map[currentAreaRow][currentAreaColumn];

							s.setRow(9);
							s.setOxygen(s.getOxygen() - 1);

							std::system("cls");
							currentArea->displayLevelCamera(s);
						}
						else {
							std::cout << "You can't move off the map! Try again!\n";
						}
					}
					else if (currentArea->isObstacle(submarineRow - 1, submarineColumn)) {
						std::cout << "You can't move into an obstacle! Try again!\n";
					}
					else if (currentArea->charAt(submarineRow - 1, submarineColumn) == 'O') {
						s.setOxygen(50);
						s.moveUp();
						std::system("cls");
						currentArea->displayLevelCamera(s);
					}
					else if (submarineRow == 1 && currentAreaRow == 0) {
						s.moveUp();
						s.setOxygen(50);
						std::system("cls");
						currentArea->displayLevelCamera(s);
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
					}
					else {
						s.setOxygen(s.getOxygen() - 1);
						s.moveUp();
						std::system("cls");
						currentArea->displayLevelCamera(s);
					}
					std::cout << "Oxygen: " << s.getOxygen() << "/50\n\n";
				}
				// Move left
				else if (move == "A") {
					if (submarineColumn == 0) {
						if (currentAreaColumn == 1 || currentAreaColumn == 2) {
							currentAreaColumn--;
							currentArea = &map[currentAreaRow][currentAreaColumn];

							s.setColumn(9);
							s.setOxygen(s.getOxygen() - 1);

							std::system("cls");
							currentArea->displayLevelCamera(s);
						}
						else {
							std::cout << "You can't move off the map! Try again!\n";
						}
					}
					else if (currentArea->isObstacle(submarineRow, submarineColumn - 1)) {
						std::cout << "You can't move into an obstacle! Try again!\n";
					}
					else if (currentArea->charAt(submarineRow, submarineColumn - 1) == 'O') {
						s.setOxygen(50);
						s.moveLeft();
						std::system("cls");
						currentArea->displayLevelCamera(s);
					}
					else {
						if (submarineRow != 0) { s.setOxygen(s.getOxygen() - 1); };
						s.moveLeft();
						std::system("cls");
						currentArea->displayLevelCamera(s);
					}
					std::cout << "Oxygen: " << s.getOxygen() << "/50\n\n";
				}
				// Move down
				else if (move == "S") {
					if (submarineRow == 9) {
						if (currentAreaRow == 0) {
							currentAreaRow++;
							currentArea = &map[currentAreaRow][currentAreaColumn];

							s.setRow(0);
							s.setOxygen(s.getOxygen() - 1);

							std::system("cls");
							currentArea->displayLevelCamera(s);
						}
						else {
							std::cout << "You can't move off the map! Try again!\n";
						}
					}
					else if (currentArea->isObstacle(submarineRow + 1, submarineColumn)) {
						std::cout << "You can't move into an obstacle! Try again!\n";
					}
					else if (currentArea->charAt(submarineRow + 1, submarineColumn) == 'O') {
						s.setOxygen(50);
						s.moveDown();
						std::system("cls");
						currentArea->displayLevelCamera(s);
					}
					else {
						s.setOxygen(s.getOxygen() - 1);
						s.moveDown();
						std::system("cls");
						currentArea->displayLevelCamera(s);
					}
					std::cout << "Oxygen: " << s.getOxygen() << "/50\n\n";
				}
				// Move right
				else if (move == "D") {
					if (submarineColumn == 9) {
						if (currentAreaColumn == 0 || currentAreaColumn == 1) {
							currentAreaColumn++;
							currentArea = &map[currentAreaRow][currentAreaColumn];

							s.setColumn(0);
							s.setOxygen(s.getOxygen() - 1);

							std::system("cls");
							currentArea->displayLevelCamera(s);
						}
						else {
							std::cout << "You can't move off the map! Try again!\n";
						}
					}
					else if (currentArea->isObstacle(submarineRow, submarineColumn + 1)) {
						std::cout << "You can't move into an obstacle! Try again!\n";
					}
					else if (currentArea->charAt(submarineRow, submarineColumn + 1) == 'O') {
						s.setOxygen(50);
						s.moveRight();
						std::system("cls");
						currentArea->displayLevelCamera(s);
					}
					else {
						if (submarineRow != 0) { s.setOxygen(s.getOxygen() - 1); };
						s.moveRight();
						std::system("cls");
						currentArea->displayLevelCamera(s);
					}
					std::cout << "Oxygen: " << s.getOxygen() << "/50\n\n";
				}
				// Inspecting move
				else if (move == "INSPECT") {
					std::system("cls");
					currentArea->displayLevelCamera(s);
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
								char inspectedChar = currentArea->charAt(currentRow, currentColumn);
								// Inspecting treasure (*)
								if (inspectedChar == '*' && !possibleTreasures.empty()) {
									foundSomething = true;
									currentArea->setCharAt(currentRow, currentColumn, ' '); // Remove from map
									int randomNumber = std::rand() % possibleTreasures.size();

									std::cout << " - You found treasure: " << possibleTreasures[randomNumber].getName() << " (Value: $" << possibleTreasures[randomNumber].getValue() << ")\n";

									treasuresFound.push_back(possibleTreasures[randomNumber]);
									possibleTreasures.erase(possibleTreasures.begin() + randomNumber);
								}
								// Inspecting non-treasure (^)
								else if (inspectedChar == '^') {
									foundSomething = true;

									// If this coordinate hasn't been assigned yet, assign it
									if (assignedScenery[currentRow][currentColumn].empty()) {
										int randomScenery = std::rand() % sceneryObjects.size();
										assignedScenery[currentRow][currentColumn] = sceneryObjects[randomScenery];
									}
									std::cout << " - You investigate a strange object... You find " << assignedScenery[currentRow][currentColumn] << ".\n";
								}
								// Inspecting Deactivated Lever (\)
								else if (inspectedChar == '|') {
									foundSomething = true;
									int doorId = currentArea->getDoorIndex(currentRow, currentColumn);
									std::cout << " - There is closed door with the number " << doorId << " on it.\n";
								}
								// Inspecting a Lever ('\' or '/')
								else if (inspectedChar == '\\' || inspectedChar == '/') {
									foundSomething = true;
									currentArea->toggleLever(currentRow, currentColumn);
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