#include <iostream>
#include "input.h"

relation::relation() {}

void relation::rel() {}

relation::~relation() {}

void function::rel() {}

function::function(std::string f) : formula(f) {
	shortenFunction(*this);
}

std::vector<std::string> function::convertIntoRPN(char array[], size_t l) {
	std::vector<char> operators; // dynamiczna tablica operatorów
	std::string token; // ¿eton do zapisu ci¹gu znaków o tym samym typie
	std::vector<std::string> returnStack;
	bool isLetterOnce = false;
	returnStack = elementAnalysis(token, operators, returnStack, array, l, isLetterOnce); // dynamiczna tablica zwrotu zapisu w ONP

	return returnStack;
}

function::~function() {};
