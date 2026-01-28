#include "LangCoreAPI.hpp"
#include <string>
int main() {
	LangCoreAPI langCore;
	std::string source_code = R"(
		i32 x = 10;
		x = x **;
		x = x + 5;
		x = x //;
		return x;)";

	langCore.exec_lexer(source_code);
}
