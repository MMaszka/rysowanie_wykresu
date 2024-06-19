#pragma once
#include <string>
#include <vector>
#include "conditioners.h"

class relation { // dla przysz³ych relacji np. równania
public:
	relation();
	virtual void rel() = 0;
	virtual ~relation();
};

class function : virtual public relation {
	std::string formula;
	long double x;
public:
	function(std::string formula);

	std::string getFormula() const {
		return formula;
	}
	long double getXVariable() const {
		return x;
	}

	void rel() override;
	void shortenFunction(const function& f);
	std::vector<std::string> convertIntoRPN(char s[], size_t l);
	long double evaluateRPN(const std::string& expression, long double x);

	virtual ~function();
};
