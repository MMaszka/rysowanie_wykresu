#include "input.h"
#include "converters.h"
#include <iostream>

void function::shortenFunction(const function& f) {
	std::string formula = f.getFormula();
	long double seachedYforX = f.getXVariable();
	char* formulaChar = convertStringArray(formula);
	int n = 0;

	// procedura usuwania niepotrzebnych element�w z zapisu
	for (int i = 0; i < formula.length(); i++) {
		if (formulaChar[i] == ' ') { // spacje
			for (int j = i; j < formula.length() - n; j++) {
				formulaChar[j] = formulaChar[j + 1];
			}
			n++;
		}
	}
	size_t arrayLength = formula.length() - n;

	// proces przekszta�cenia z f(x) na y
	std::string str(formulaChar, arrayLength);
	if (str.substr(0, 4) == "f(x)") {
		str.erase(0, 4);
		formula = str.insert(0, "y");
		arrayLength = str.length();

		for (int i = 0; i < arrayLength; i++) {
			formulaChar[i] = formula[i];
		}
	}
	
	std::vector<std::string> RPNExpression = convertIntoRPN(formulaChar, arrayLength);
	delete[] formulaChar;
	std::string fullyConvertedRPNExpression = combineVectorIntoFullString(RPNExpression);
	evaluateRPN(fullyConvertedRPNExpression, x);
}