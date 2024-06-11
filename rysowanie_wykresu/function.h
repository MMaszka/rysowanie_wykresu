#pragma once
#include <iostream>
#include <string>
#include <vector>

class Function {
	std::vector <int*> function;
	Function(std::string fun);
	bool CheckFunction(std::string fun);
	void BreakDownFunction(std::string fun);
	double CalculateFunction(int* fun, int x);
	void draw();

	~Function();
};