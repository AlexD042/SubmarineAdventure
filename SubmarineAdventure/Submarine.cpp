#include "Submarine.hpp"

int Submarine::getRow() const { 
	return row; 
}
void Submarine::setRow(int newRow) {
	row = newRow; 
}

int Submarine::getColumn() const {
	return column; 
}
void Submarine::setColumn(int newColumn) {
	column = newColumn; 
}

int Submarine::getOxygen() const {
	return oxygen; 
}
void Submarine::setOxygen(int newOxygen) {
	oxygen = newOxygen; 
}

int Submarine::getTotalEarnings() const {
	return totalEarnings;
}
void Submarine::setTotalEarnings(int newTotalEarnings) {
	totalEarnings = newTotalEarnings;
}

void Submarine::moveUp() {
	row--;
}
void Submarine::moveDown() {
	row++;
}
void Submarine::moveRight() {
	column++;
}
void Submarine::moveLeft() {
	column--;
}