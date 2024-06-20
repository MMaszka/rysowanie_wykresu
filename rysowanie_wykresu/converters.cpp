#include "converters.h"

char* convertStringArray(std::string s) {
	char* cArray = new char[s.length()];
	for (int i = 0; i < s.length(); i++) {
		cArray[i] = s[i];
	}
	return cArray;
}