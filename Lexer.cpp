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
    else {
        column++;
    }
    return c;
}

Token::Type LangCoreAPI::lookup_type(std::string_view identifier) {
    if (auto it = string_to_token.find(identifier); it != string_to_token.end()) {
        return it->second;
    }
    return Token::Type::IDENTIFIER;
}

void LangCoreAPI::walk(std::string_view source) {
    while (cursor < source.length()) {
        size_t start = cursor;
        char c = advance(source);

        if (isspace(c)) continue;

        if (isalpha(c) || c == '_') {
            while (cursor < source.length() && (isalnum(source[cursor]) || source[cursor] == '_')) {
                advance(source);
            }
            std::string_view lexeme = source.substr(start, cursor - start);
            tokens.push_back({ lookup_type(lexeme), lexeme, line, column - lexeme.length() });
        }
        else if (isdigit(c)) {
            while (cursor < source.length() && isdigit(source[cursor])) {
                advance(source);
            }

            if (cursor < source.length() && source[cursor] == '.' && isdigit(source[cursor + 1])) {
                advance(source);
                while (cursor < source.length() && isdigit(source[cursor])) {
                    advance(source);
                }
                std::string_view lexeme = source.substr(start, cursor - start);
                tokens.push_back({ Token::Type::LITERAL_FLOAT, lexeme, line, column - lexeme.length() });
            }
            else {
                std::string_view lexeme = source.substr(start, cursor - start);
                tokens.push_back({ Token::Type::LITERAL_INT, lexeme, line, column - lexeme.length() });
            }
        }
        else {
            std::string_view lexeme = source.substr(start, 1);

            if (cursor < source.length()) {
                if (cursor + 1 < source.length()) {
                    std::string_view potential_triple = source.substr(start, 3);
                    if (string_to_token.contains(potential_triple)) {
                        advance(source);
                        advance(source);
                        lexeme = potential_triple;
                    }
                }

                if (lexeme.length() == 1) {
                    std::string_view potential_double = source.substr(start, 2);
                    if (string_to_token.contains(potential_double)) {
                        advance(source);
                        lexeme = potential_double;
                    }
                }
            }

            Token::Type type = lookup_type(lexeme);
            if (string_to_token.contains(lexeme)) {
                tokens.push_back({ type, lexeme, line, column - lexeme.length() });
            }
        }
    }
}

void LangCoreAPI::exec_lexer(std::string_view source) {
	walk(source);
}
