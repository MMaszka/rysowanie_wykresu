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
public:
	function(std::string formula);

	std::string getFormula() const {
		return formula;
	}

	void rel() override;
	void shortenFunction(const function& f);
	std::vector<std::string> convertIntoRPN(char s[], size_t l);
	std::vector<std::string> RPNExpression;
	double evaluateRPN(const std::vector<std::string>& expression, double x);

	virtual ~function();
};
