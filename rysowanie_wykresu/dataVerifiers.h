#pragma once
#include <string>

bool isLetter(char);
bool isOperator(char);
bool isBracket(char);
bool isSpecialFunction(const std::string&);
int operatorPriority(char);
bool isXVaribale(std::string);