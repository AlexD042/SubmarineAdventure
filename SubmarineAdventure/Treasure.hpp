#pragma once

#include <string>

class Treasure {
private:
	std::string name;
	int value;
public:
	Treasure(std::string n, int v) {
		name = n;
		value = v;
	}
	
	std::string getName() {
		return name;
	}
	
	int getValue() {
		return value;
	}
};