#pragma once
#include <string_view>
#include <map>

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

private:
    enum class Token;
    std::map<std::string_view, Token> string_to_token;
    struct LexerInternals {
        size_t line = 0;
        size_t column = 0;
    };
	LexerInternals lexer_internals;
};