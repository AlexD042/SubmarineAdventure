#pragma once

class Submarine {
private:
	int row = 0;
	int column = 4;
	int oxygen = 50;
public:
	// Getters and Setters
	int getRow() const { return row; }
	int setRow(int newRow) { row = newRow; }
	int getColumn() const { return column; }
	int setColumn(int newColumn) { column = newColumn; }
	
	// Movement
	void moveUp() {
		row--;
	}
	void moveDown() {
		row++;
	}
	void moveRight() {
		column--;
	}
	void moveLeft() {
		column++;
	}
};