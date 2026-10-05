#include "Treasure.hpp"

Treasure::Treasure(std::string n, int v) {
	name = n;
	value = v;
}

std::string Treasure::getName() {
	return name;
}

int Treasure::getValue() {
	return value;
}