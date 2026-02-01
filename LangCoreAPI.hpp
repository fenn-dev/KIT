#pragma once
#include <string_view>
#include <map>
#include <vector>
#include "Tokens.hpp"
#include "Nodes.hpp"

class LangCoreAPI {
public:
    void exec_lexer(std::string_view source);
    void exec_parser();
    void exec_semantic_analyzer();
    void exec_ir_generator();
    void exec_ir_optimizer();
    void exec_nasm_generator();
    void exec_assembler();
    void exec_linker();

    inline std::vector<Token> retrieve_tokens() { return tokens; }
	inline Nodes::mainNode* retrieve_ast() { return &ast; }
private:
    // LEXER DATA
    size_t line = 0;
    size_t column = 0;
    size_t cursor = 0;
    std::vector<Token> tokens;
    void walk(std::string_view source);
    Token::Type lookup_type(std::string_view identifier);
    char advance(std::string_view source);
	// PARSER DATA
	Nodes::mainNode ast;
};