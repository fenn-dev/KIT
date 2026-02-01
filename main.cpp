#include "LangCoreAPI.hpp"
#include <string>
#include <iostream>
#include <variant>

void printVarValue(const VarType& var) {
    std::visit([](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;

        if constexpr (std::is_same_v<T, std::monostate>)
            std::cout << "null";
        else if constexpr (std::is_same_v<T, bool>)
            std::cout << (arg ? "true" : "false");
        else if constexpr (std::is_same_v<T, std::string>)
            std::cout << "\"" << arg << "\"";
        else if constexpr (std::is_same_v<T, Wild>)
            std::cout << "[Wild/Binary]";
        else
            std::cout << arg;
        }, var);
}

void printAST(const Nodes::mainNode& ast) {
    for (const auto& node : ast.statements) {
        if (auto* var = dynamic_cast<Nodes::VariableNode*>(node.get())) {
            std::cout << "Variable: " << var->name;

            if (var->value) {
                if (auto* lit = dynamic_cast<Nodes::LiteralNode*>(var->value.get())) {
                    std::cout << " = ";
                    printVarValue(lit->value);
                }
            }
            std::cout << " (line " << var->line << ")" << std::endl;
        }
    }
}


int main() {
	LangCoreAPI langCore;
	std::string source_code = R"(
		let x: i32 = 10;
        let y = 20;
        const z = 5;
		x**;
		x = y + 5;
		x//;
		return x;
	)";

	langCore.exec_lexer(source_code);

	auto tokens = langCore.retrieve_tokens();
	for (const auto& token : tokens) {
		std::cout << "Token: " << static_cast<int>(token.type) << ", Lexeme: " << token.lexeme << ", Line: " << token.line << ", Column: " << token.column << "\n";
	}

	langCore.exec_parser();

    auto& ast = *langCore.retrieve_ast();
    printAST(ast);


	return 0;
}
