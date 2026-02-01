#include "LangCoreAPI.hpp"
#include "Nodes.hpp"
#include <stdexcept>
#include "Helpers.hpp"

void LangCoreAPI::exec_parser() {
	Nodes::mainNode root;
	Nodes::Nodeptr unfinishedNode;
	for (auto& token : tokens) {
		switch (token.type) {
		case Token::Type::CONST:
		case Token::Type::LET:
		{
			// Start a new variable node
			unfinishedNode = std::make_unique<Nodes::VariableNode>();
			auto node = static_cast<Nodes::VariableNode*>(unfinishedNode.get());
			node->line = static_cast<unsigned int>(token.line);
			node->column = static_cast<unsigned int>(token.column);
			node->type = Token::Type::LET;
			node->isConst = (token.type == Token::Type::CONST);
			node->value = nullptr;
			break;
		}

		case Token::Type::IDENTIFIER:
		{
			if (unfinishedNode && (unfinishedNode->type == Token::Type::LET || unfinishedNode->type == Token::Type::CONST)) {
				static_cast<Nodes::VariableNode*>(unfinishedNode.get())->name = std::string(token.lexeme);
			}
			else {

			}
			break;
		}

		case Token::Type::COLON:
			break;

		case TypeCases:
		{
			if (unfinishedNode && unfinishedNode->type == Token::Type::LET || unfinishedNode->type == Token::Type::CONST) {
				unfinishedNode->type = token.type;
			}
			break;
		}

		case Token::Type::ASSIGN:
			break;

		case LiteralCases:
		{
			if (unfinishedNode) {
				auto* varNode = static_cast<Nodes::VariableNode*>(unfinishedNode.get());

				// Create the literal
				auto literalNode = std::make_unique<Nodes::LiteralNode>();
				literalNode->line = static_cast<unsigned int>(token.line);
				literalNode->column = static_cast<unsigned int>(token.column);
				literalNode->type = token.type;

				// This is where identifyType still uses std::any (which is fine for primitives)
				literalNode->value = identifyType(std::string(token.lexeme));

				// Transfer ownership: LiteralNode is now OWNED by VariableNode
				varNode->value = std::move(literalNode);

				if (varNode->type == Token::Type::LET)
					varNode->type = token.type;
			}
			break;
		}
		case Token::Type::SEMICOLON:
		{
			if (unfinishedNode) {
				root.statements.push_back(std::move(unfinishedNode));
				unfinishedNode = nullptr;
			}
			break;
		}

		}
	}

	ast = std::move(root);
}
