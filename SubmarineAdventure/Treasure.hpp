#pragma once

#include <string>

class Treasure {
private:
	std::string name;
	int value;
public:
	Treasure(std::string n, int v);
	
	std::string getName();
	int getValue();
};