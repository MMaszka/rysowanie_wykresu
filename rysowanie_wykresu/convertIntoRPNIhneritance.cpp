#include <iostream>
#include "conditioners.h"
#include "dataVerifiers.h"
#include "converters.h"

std::vector<std::string> inheritRPN(char s[], size_t l) {
	std::vector<char> operators; // dynamiczna tablica operatorów
	std::string token; // ¿eton do zapisu ci¹gu znaków o tym samym typie
	std::vector<std::string> argumentStack;
	argumentStack = elementAnalysis(token, operators, argumentStack, s, l); // dynamiczna tablica zwrotu zapisu w ONP
	
	return argumentStack;
}

void handleSpecialFunction(const std::string& token, std::vector<char>& operators, std::vector<std::string>& returnStack, char array[], int& i, size_t l) {
	std::vector<std::string> arguments; // tablica argumentów funkcji
	int argCount = 0; // iloœæ zliczonych argumentów

	// Zlicza wszystkie napotkane argumenty funkcji specjalnej (maskymalnie mo¿e byæ ich 2)
	for (int j = i + 1; j < l; j++) {
		if (array[j] == ',') {
			argCount++;
		}
		else if (array[j] == ')' || array[j] == ']') {
			argCount++;
			break;
		}
	}

	// Przetwarza ka¿dy argument jaki napotka na drodze
	while (argCount > 0) {
		std::string arg;
		while (i + 1 < l && array[++i] != ',' && array[i] != ')' && array[i] != ']' && array[i] != '(' && array[i] != '[') {
			arg += array[i];
		}
		if (!arg.empty()) {
			if (arg.length() > 1 && isXVaribale(arg) == true) { // dla argumentów z³o¿onych, np. x/2, 3x^2, ln(x), itp.
				// tworzenie z argumentu kolejnej funkcji, aby zapobiec b³êdom zakresu tablicy vectorowej + ³adniej to wygl¹da, bardziej funkcyjnie
				std::string argumentEquation = "y="; 
				arg = arg.insert(0, argumentEquation);

				char* argArray = convertStringArray(arg);
				size_t sizeArgArray = arg.length();
				std::vector<std::string> convertedArg = inheritRPN(argArray, sizeArgArray); // Konwersja na ONP argumentu

				// Dodanie skonwertowanego argumentu do stosu zwrotnego ONP
				for (const auto& a : convertedArg) {
					arguments.push_back(a);
				}
			}
			else {
				arguments.push_back(arg);
			}
			argCount--;
		}
	}

	// Zwraca wszystkie argumenty do tablicy zwrotnej ONP
	for (const auto& arg : arguments) {
		returnStack.push_back(arg);
	}
	returnStack.push_back(token);
}
