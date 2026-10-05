#pragma once

class Submarine {
private:
	int row = 0;
	int column = 4;
	int oxygen = 50;
	int totalEarnings = 0;
public:
	// Getters and Setters
	int getRow() const;
	void setRow(int newRow);
	int getColumn() const;
	void setColumn(int newColumn);
	int getOxygen() const;
	void setOxygen(int newOxygen);
	int getTotalEarnings() const;
	void setTotalEarnings(int newTotalEarnings);
	
	// Movement
	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
};