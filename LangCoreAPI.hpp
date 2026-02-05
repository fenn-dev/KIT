#pragma once
#include <string_view>
#include <map>
#include <vector>
#include "Tokens.hpp"
#include "Semantics.h"

class LangCoreAPI {
private:
    struct symbol { std::string name; bool is_init; int use_count; };
public:
    void exec_lexer(std::string_view source);
    void exec_semantic_parser();
    void exec_semantic_optimizer();
    void exec_VCL_emitter();
    void exec_gcc();

    inline std::vector<Token> retrieve_tokens() { return tokens; }
private:
    // LEXER DATA
    size_t line = 0;
    size_t column = 0;
    size_t cursor = 0;
    std::vector<Token> tokens;
    void walk(std::string_view source);
    Token::Type lookup_type(std::string_view identifier);
    char advance(std::string_view source);


    std::vector<NodeValue> ast;
};