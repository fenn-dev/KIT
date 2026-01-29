#include "LangCoreAPI.hpp"
#include <string>
#include <iostream>
#include <vector>

char LangCoreAPI::advance(std::string_view source) {
	char c = source[cursor++];

	if (c == '\n') {
		line++;
		column = 1;
	}
	else { column++; }

	return c;
}

void LangCoreAPI::walk(std::string_view source) {
	for (char c : source) {
		if (!isspace(c)) {

		}
	}
}

void LangCoreAPI::exec_lexer(std::string_view source) {
	walk(source);
}
