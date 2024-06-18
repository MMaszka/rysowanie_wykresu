#include "conditioners.h"
#include "dataVerifiers.h"
#include <iostream>

void handleSpecialFunction(const std::string& token, std::vector<char>& operators, std::vector<std::string>& returnStack, char array[], int& i, size_t l);

void handleOperator(char character, std::vector<char>& operators, std::vector<std::string>& returnStack) {
	while (!operators.empty() && operatorPriority(operators.back()) >= operatorPriority(character)) {
		returnStack.push_back(std::string(1, operators.back()));
		operators.pop_back();
	}
	operators.push_back(character);
}

void handleClosingBracket(char character, std::vector<char>& operators, std::vector<std::string>& returnStack) {
	while (!operators.empty() && operators.back() != '(' && operators.back() != '[') {
		returnStack.push_back(std::string(1, operators.back()));
		operators.pop_back();
	}
	if (!operators.empty() && (operators.back() == '(' || operators.back() == '[')) {
		operators.pop_back();
	}
	else {
		throw std::runtime_error("Nawiasy zosta�y nieprawid�owo dopasowane w zapisanej funkcji.");
	}
}

std::vector<std::string> elementAnalysis(std::string token, std::vector<char>& operators, std::vector<std::string>& returnStack, char array[], size_t l) {
	for (int i = 0; i < l; i++) {
		char character = array[i];

		if (isdigit(character)) { // je�li napotka na liczb�, to sprawdza ich ewentualny ci�g ca�kowity lub zmiennoprzecinkowy
			token.clear();
			while (i < l && (isdigit(array[i]) || array[i] == '.')) {
				token += array[i++];
			}
			i--;
			returnStack.push_back(token);
			if (array[i - token.length()] == ')' || array[i - token.length()] == ']' || array[i + token.length()] == '(' || array[i + token.length()] == '[') { // gdy liczba przed lub za nawiasem jako iloczyn nawiasu
				operators.push_back('*');
			}
		}
		else if (character == 'x') { // je�li napotka zmienn� x, wpycha do tablicy x-a i sprawdza ewentualne dodatkowe warunki przed i/lub po procesie
			if (array[i - (token.length() + 1)] == '/') { // je�li x mno�ymy przez u�amek
				returnStack.push_back("/");
				operators.pop_back();
			}
			else if (array[i - (token.length() + 1)] == '*') { // je�li przed mno�eniem x z liczb� jest jeszcze jeden iloczyn
				returnStack.push_back("*");
				operators.pop_back();
			}

			returnStack.push_back("x");
			if (isdigit(array[i - 1]) && i > 0) { // dla mno�enia x z liczb� obok niej, np. zapis 8x
				character = '*';
				goto operatorOrder; // realizuje wepchni�cie znaku * do tablicy operator�w
			}
		}
		// sprawdzenie ci�gu znak�w pod k�tem sta�ych PI lub e.
		else if (toupper(character) == 'P' && toupper(array[i + 1]) == 'I') {
			returnStack.push_back(std::to_string(3.141592653589));
			i++;
		}
		else if (toupper(character) == 'E' && toupper(array[i + 1]) != 'X') {
			returnStack.push_back(std::to_string(2.718281828459));
		}
		else if (isOperator(character)) { // sprawdzenie priorytetu dzia�ania we wzorze funkcji 
		operatorOrder:
			handleOperator(character, operators, returnStack);
		}
		// sprawdzenie znak�w pod k�tem wyst�puj�cych nawias�w otwieraj�cych we wzorze funkcji
		else if (character == '(' || character == '[') {
			operators.push_back(character);

			// procedura gdy wyst�puj� operatory przed lub po nawiasach dla sytuacji typu 2x, x^3 i kombinacje
			int operBraRange = 0;

			for (int j = i; j > 0; j--) { // sprawdzenie odleg�o�ci operatora o priorytecie 1, tj. + i -
				if (operatorPriority(array[j]) == 1) {
					operBraRange = j;
					break;
				}
			}

			for (int j = i; j > operBraRange; j--) { // wypychanie operator�w * lub ^ w zale�no�ci od powtarzajacych si� tych samych operacji 
				if (operatorPriority(array[j]) > 1 || array[j] == 'x') {
					std::string lastElement = returnStack.back(); // ostatnio znaleziony operator w zbiorze zwrotnym

					if (array[j] == 'x') {
						if (lastElement != "*") { //  do poprawy - wprowadzi� dodatkowy warunek
							returnStack.push_back("*");
						}
						for (size_t k = operators.size() - 1; k > 0; k--) {
							if (operators[k] == '*') {
								operators.erase(operators.begin() + k);
								break;
							}
						}
					}
					else if (operatorPriority(array[j]) == 3) {
						if (lastElement != "^") { //  do poprawy - wprowadzi� dodatkowy warunek
							returnStack.push_back("^");
						}
						for (size_t k = operators.size() - 1; k > 0; k--) {
							if (operators[k] == '^') {
								operators.erase(operators.begin() + k);
								break;
							}
						}
					}
				}
			}
		}
		// sprawdzenie znak�w pod k�tem wyst�puj�cych nawias�w zamykaj�cych we wzorze funkcji
		else if (character == ')' || character == ']') {
			handleClosingBracket(character, operators, returnStack);

			if (array[i + 1] == '(' || array[i + 1] == '[') { // pomi�dzy nawiasami nast�puje mno�enie, o ile operatora nie ma zapisanego
				operators.push_back('*');
			}
		}
		// sprawdzenie znak�w pod k�tem specjalnych funkcji oznaczonych w funkcji isSpecialFunction -- do ulepszenia, na razie nie dzia�a
		else if (isLetter(toupper(character)) && i > 0) { // funkcja specjalna nieb�d�ca jedynie liter� y
			token.clear();
			while (i < l && isLetter(toupper(array[i]))) {
				token += array[i++];
			}
			i--;

			if (isSpecialFunction(token)) { // je�li funkcja specjalna
				handleSpecialFunction(token, operators, returnStack, array, i, l);
			}
		}
	}
	while (!operators.empty()) {
		returnStack.push_back(std::string(1, operators.back()));
		operators.pop_back();
	}

	return returnStack;
}