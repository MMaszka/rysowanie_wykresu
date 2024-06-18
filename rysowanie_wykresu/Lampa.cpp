#include <iostream>
#include "Lampa.h"

relation::relation() {}

void relation::rel() {}

relation::~relation() {}

void function::rel() {}

function::function(std::string f) : formula(f) {
	shortenFunction(*this);
}

void function::convertIntoRPN(char array[], size_t l) {
	std::vector<char> operators; // dynamiczna tablica operator�w
	std::string token; // �eton do zapisu ci�gu znak�w o tym samym typie
	std::vector<std::string> returnStack;
	returnStack = elementAnalysis(token, operators, returnStack, array, l); // dynamiczna tablica zwrotu zapisu w ONP

	std::cout << "Zapis funkcji w ONP: ";

	for (const auto& c : returnStack) {
		std::cout << c << " ";
	}
	std::cout << "\n";
}

function::~function() {};