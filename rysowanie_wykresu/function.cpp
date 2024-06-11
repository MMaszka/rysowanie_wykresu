#include "function.h"

Function::Function(std::string fun) {
	if (CheckFunction(fun)) {
		BreakDownFunction(fun);

	}
	else {
		std::cout << "Function did not pass check test";
	}
	
}

bool Function::CheckFunction(std::string fun) {


}

void Function::BreakDownFunction(std::string fun) {

	for (int i{}; i < 1; i++) {

		function.push_back(new int(10));

	}
}

double Function::CalculateFunction(int* fun, int x) {
	double y{};



	return y;
}

Function::~Function() {
	for (int i{}; i < function.size(); i++) {
		delete function.at(i);
	}
}