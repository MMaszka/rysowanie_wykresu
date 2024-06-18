#pragma once
#include <vector>
#include <string>

void handleOperator(char character, std::vector<char>& operators, std::vector<std::string>& returnStack);
void handleClosingBracket(char character, std::vector<char>& operators, std::vector<std::string>& returnStack);
std::vector<std::string> elementAnalysis(std::string token, std::vector<char>& operators, std::vector<std::string>& returnStack, char array[], size_t l);