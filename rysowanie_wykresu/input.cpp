#include <iostream>
#include "input.h"

relation::relation() {}

void relation::rel() {}

relation::~relation() {}

void input::rel() {}

input::input(std::string f) : formula(f) {
	shortenFunction(*this);
}

void input::convertIntoRPN(char array[], size_t l) {
	std::vector<char> operators; // dynamiczna tablica operatorów
	std::string token; // ¿eton do zapisu ci¹gu znaków o tym samym typie
	std::vector<std::string> returnStack;
	returnStack = elementAnalysis(token, operators, returnStack, array, l); // dynamiczna tablica zwrotu zapisu w ONP

	std::cout << "Zapis funkcji w ONP: ";

	for (const auto& c : returnStack) {
		std::cout << c << " ";
	}
	std::cout << "\n";
}

input::~input() {};