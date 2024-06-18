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

class input : virtual public relation {
	std::string formula;
public:
	input(std::string formula);

	std::string getFormula() const {
		return formula;
	}

	void rel() override;
	void shortenFunction(const input& f);
	void convertIntoRPN(char s[], size_t l);

	virtual ~input();
};
