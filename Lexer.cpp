#include "LangCoreAPI.hpp"
#include <string>

void LangCoreAPI::exec_lexer(std::string_view source) {
	lexer_internals.line = 1;
	lexer_internals.column = 1;
	size_t pos = 0;
	while (pos < source.size()) {
		char current_char = source[pos];
		// Simple whitespace handling
		if (current_char == '\n') {
			lexer_internals.line++;
			lexer_internals.column = 1;
			pos++;
			continue;
		} else if (isspace(current_char)) {
			lexer_internals.column++;
			pos++;
			continue;
		}
		// Token recognition (very simplified for demonstration)
		bool matched = false;
		for (const auto& [str, token] : string_to_token) {
			if (source.substr(pos, str.size()) == str) {
				// Token recognized
				// In a full implementation, you would store the token and its position
				pos += str.size();
				lexer_internals.column += str.size();
				matched = true;
				break;
			}
		}
		if (!matched) {
			// Handle unrecognized character
			pos++;
			lexer_internals.column++;
		}
	}
}


