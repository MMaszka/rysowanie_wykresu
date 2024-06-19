#include "conditioners.h"
#include "dataVerifiers.h"
#include <iostream>

std::vector<int> handleSpecialFunction(const std::string& token, std::vector<char>& operators, std::vector<std::string>& returnStack, char array[], size_t& i, size_t l);

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
	}
	if (!operators.empty() && (operators.back() == '(' || operators.back() == '[')) {
		operators.pop_back();
	}
	else {
		throw std::runtime_error("Nawiasy zosta³y nieprawid³owo dopasowane w zapisanej funkcji.");
	}
}

size_t moveArrayByDistance(std::vector<int> lengthArray) {
	size_t movingInt = 0; // liczba przesuwaj¹ca liczbê i po argumencie

	if (lengthArray.capacity() == 1) { // dla tylko jednego argumentu, d³ugoœæ argumentu + 2 nawiasy miêdzy argumentem
		movingInt = 2 + lengthArray[0];
	}
	else if (lengthArray.capacity() > 1) {
		// dla wiêcej ni¿ jednego argumentu, d³ugoœæ ka¿dego argumentu + 2 nawiasy + liczba przecinków tj. iloœæ argumentów - 1
		for (auto& argLen : lengthArray) {
			movingInt += argLen;
		}
		movingInt += (2 + (lengthArray.capacity() - 1));
	}
	return movingInt;
}

std::vector<std::string> elementAnalysis(std::string token, std::vector<char>& operators, std::vector<std::string>& returnStack, char array[], size_t l) {
	for (size_t i = 0; i < l; i++) {
		char character = array[i];

		if (isdigit(character)) { // jeœli napotka na liczbê, to sprawdza ich ewentualny ci¹g ca³kowity lub zmiennoprzecinkowy
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
		else if (character == 'x') { // jeœli napotka zmienn¹ x, wpycha do tablicy x-a i sprawdza ewentualne dodatkowe warunki przed i/lub po procesie
			if (array[i - (token.length() + 1)] == '/') { // jeœli x mno¿ymy przez u³amek
				returnStack.push_back("/");
				operators.pop_back();
			}
			else if (array[i - (token.length() + 1)] == '*') { // jeœli przed mno¿eniem x z liczb¹ jest jeszcze jeden iloczyn
				returnStack.push_back("*");
				operators.pop_back();
			}

			returnStack.push_back("x");
			if (isdigit(array[i - 1]) && i > 0) { // dla mno¿enia x z liczb¹ obok niej, np. zapis 8x
				character = '*';
				goto operatorOrder; // realizuje wepchniêcie znaku * do tablicy operatorów
			}
		}
		// sprawdzenie ci¹gu znaków pod k¹tem sta³ych PI lub e.
		else if (toupper(character) == 'P' && toupper(array[i + 1]) == 'I') {
			returnStack.push_back(std::to_string(3.141592653589));
			i++;
		}
		else if (toupper(character) == 'E' && toupper(array[i + 1]) != 'X') {
			returnStack.push_back(std::to_string(2.718281828459));
		}
		else if (isOperator(character)) { // sprawdzenie priorytetu dzia³ania we wzorze funkcji 
		operatorOrder:
			handleOperator(character, operators, returnStack);
		}
		// sprawdzenie znaków pod k¹tem wystêpuj¹cych nawiasów otwieraj¹cych we wzorze funkcji
		else if (character == '(' || character == '[') {
			operators.push_back(character);

			// procedura gdy wystêpuj¹ operatory przed lub po nawiasach dla sytuacji typu 2x, x^3 i kombinacje
			size_t operBraRange = 0;

			for (size_t j = i; j > 0; j--) { // sprawdzenie odleg³oœci operatora o priorytecie 1, tj. + i -
				if (operatorPriority(array[j]) == 1) {
					operBraRange = j;
					break;
				}
			}
		}
		// sprawdzenie znaków pod k¹tem wystêpuj¹cych nawiasów zamykaj¹cych we wzorze funkcji
		else if (character == ')' || character == ']') {
			handleClosingBracket(character, operators, returnStack);

			if (array[i + 1] == '(' || array[i + 1] == '[') { // pomiêdzy nawiasami nastêpuje mno¿enie, o ile operatora nie ma zapisanego
				operators.push_back('*');
			}
		}
		// sprawdzenie znaków pod k¹tem specjalnych funkcji oznaczonych w funkcji isSpecialFunction -- do ulepszenia, na razie nie dzia³a
		else if (isLetter(toupper(character)) && i > 0) { // funkcja specjalna niebêd¹ca jedynie liter¹ y
			token.clear();
			while (i < l && isLetter(toupper(array[i]))) {
				token += array[i++];
			}
			i--;

			if (isSpecialFunction(token)) { // jeœli funkcja specjalna
				std::vector<int> argLenArray = handleSpecialFunction(token, operators, returnStack, array, i, l);
				size_t movingInt = moveArrayByDistance(argLenArray);
				i += movingInt;
			}
		}
	}
	while (!operators.empty()) {
		if (isBracket(operators.back())) {
			operators.pop_back();
		}
		returnStack.push_back(std::string(1, operators.back()));
		operators.pop_back();
	}

	return returnStack;
}