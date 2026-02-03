#include "LangCoreAPI.hpp"
#include "Nodes.hpp"
#include <stdexcept>
#include <iostream>
#include "Helpers.hpp"

#define PARSER_DEBUG

bool commit_variable(LangCoreAPI* core, std::string label, Token::Type type, std::unique_ptr<Nodes::Node> value) {
    auto* symbols = core->retrieve_symbol_table();
    auto* current_ast = core->retrieve_ast();

    if (!symbols || !current_ast) return false;

    for (const auto& sym : *symbols) {
        if (sym.name == label) return false;
    }

    auto varNode = std::make_unique<Nodes::VariableNode>();
    varNode->name = std::move(label);
    varNode->type = type;
    varNode->value = std::move(value);

    current_ast->statements.push_back(std::move(varNode));
    symbols->push_back({ varNode->name, (varNode->value != nullptr), 0 });

    return true;
}

void LangCoreAPI::exec_parser() {
    Nodes::mainNode root;

    Token::Type storagedecl = Token::Type::UNKNOWN;
    bool expectingInheritance = false;
    bool assignment = false;

    std::string v_label = "";
    Token::Type v_type = Token::Type::UNKNOWN;
    std::unique_ptr<Nodes::Node> v_value = nullptr;

    for (auto& token : tokens) {
#ifdef PARSER_DEBUG
        std::cout << "loop start | Token: " << (int)token.type << " Lexeme: " << token.lexeme << "\n";
#endif
        switch (token.type) {
        case Token::Type::CONST:
        case Token::Type::LET:
            storagedecl = token.type;
#ifdef PARSER_DEBUG
            std::cout << "storage type set\n";
#endif
            break;

        case Token::Type::IDENTIFIER:
            if (storagedecl != Token::Type::UNKNOWN) {
                v_label = std::string(token.lexeme);
            }
            else {
                for (auto& sym : symbol_table) {
                    if (sym.name == token.lexeme) {
                        sym.use_count++;
                        break;
                    }
                }

                if (assignment) {
                    auto refNode = std::make_unique<Nodes::IdentifierNode>();
                    refNode->name = std::string(token.lexeme);
                    v_value = std::move(refNode);
                    assignment = false;
                }
            }
            break;

        case Token::Type::COLON:
            expectingInheritance = true;
#ifdef PARSER_DEBUG
            std::cout << "colon\n";
#endif
            break;

        case TypeCases:
            if (expectingInheritance) {
                v_type = token.type;
                expectingInheritance = false;
#ifdef PARSER_DEBUG
                std::cout << "type set\n";
#endif
            }
            break;

        case Token::Type::ASSIGN:
            assignment = true;
#ifdef PARSER_DEBUG
            std::cout << "ready to assign\n";
#endif
            break;

        case LiteralCases:
            if (assignment) {
                auto literalNode = std::make_unique<Nodes::LiteralNode>();
                literalNode->line = static_cast<unsigned int>(token.line);
                literalNode->column = static_cast<unsigned int>(token.column);
                literalNode->type = token.type;

                std::string raw = std::string(token.lexeme);
                literalNode->value = identifyType(raw);

                v_value = std::move(literalNode);
                assignment = false;
#ifdef PARSER_DEBUG
                std::cout << "literal case set as value\n";
#endif
            }
            break;

        case Token::Type::SEMICOLON:
#ifdef PARSER_DEBUG
            std::cout << "hit semicolon\n";
#endif
            if (storagedecl != Token::Type::UNKNOWN && !v_label.empty()) {
                bool exists = false;
                for (const auto& sym : symbol_table) {
                    if (sym.name == v_label) { exists = true; break; }
                }

                if (exists) throw std::runtime_error("Variable redeclaration!");

                auto varNode = std::make_unique<Nodes::VariableNode>();
                varNode->name = v_label;
                varNode->type = v_type;
                varNode->value = std::move(v_value);
                varNode->isConst = (storagedecl == Token::Type::CONST);

                root.statements.push_back(std::move(varNode));
                symbol_table.push_back({ v_label, true, 0 });

#ifdef PARSER_DEBUG
                std::cout << "variable commited\n";
#endif
            }

            v_label.clear();
            v_value.reset();
            v_type = Token::Type::UNKNOWN;
            storagedecl = Token::Type::UNKNOWN;
            expectingInheritance = false;
            assignment = false;
#ifdef PARSER_DEBUG
            std::cout << "loop data reset\n";
#endif
            break;

        default: break;
        }
    }

#ifdef PARSER_DEBUG
    std::cout << "Tree pushed\n";
#endif
    ast = std::move(root);
}