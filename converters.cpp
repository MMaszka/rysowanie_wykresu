#include "converters.h"

char* convertStringArray(std::string s) {
	char* cArray = new char[s.length()];
	for (int i = 0; i < s.length(); i++) {
		cArray[i] = s[i];
	}
	return cArray;
}

std::string combineVectorIntoFullString(std::vector<std::string> arrayWithStringsinRPN) {
	std::string stringifiedExpression;
	for (auto& element : arrayWithStringsinRPN) {
		if (!stringifiedExpression.empty()) {
			stringifiedExpression += " ";
		}
		stringifiedExpression += element;
	}
	return stringifiedExpression;
}