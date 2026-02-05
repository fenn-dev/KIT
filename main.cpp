#include "LangCoreAPI.hpp"
#include <string>
#include <iostream>
#include <variant>

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

    try {
        langCore.exec_parser();
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Caught a runtime error in parser: " << e.what() << std::endl;
    }


	return 0;
}
