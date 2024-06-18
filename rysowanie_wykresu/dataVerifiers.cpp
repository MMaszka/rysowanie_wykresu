#include "dataVerifiers.h"

bool isLetter(char let) {
	const char letterArray[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

	for (int i = 0; i < 26; i++) {
		if (let == letterArray[i]) {
			return true;
		}
	}
	return false;
}

bool isSpecialFunction(const std::string& fun) { // wiêcej info - spójrz na plik funkcje_specjalne.txt
	const std::string specFunArray[] = { "fact", "root", "exp", "log", "lg", "ln", "sin", "cos", "tg", "ctg", "arcsin", "arccos", "arctg", "arcctg", "abs", "scn" };

	for (int i = 0; i < 16; i++) {
		if (fun == specFunArray[i]) {
			return true;
		}
	}
	return false;
}

bool isOperator(char op) {
	return  op == '+' || op == '-' || op == '*' || op == '/' || op == '^';
}

int operatorPriority(char op) {
	switch (op) {
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	case '^':
		return 3;
	default:
		return 0;
	}
}

bool isBracket(char c) {
	return (c == '(' || c == ')' || c == '[' || c == ']');
}

bool isXVaribale(std::string s) {
	for (auto sPart : s) {
		if (sPart == 'x') return true;
	}
	return false;
}