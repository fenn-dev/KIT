#pragma once
#include "Tokens.hpp"
#include "Helpers.hpp"
#include <string>
#include <any>
#include <vector>
#include <memory>

namespace Nodes {
    struct Node {
        unsigned int line = 0;
        unsigned int column = 0;
        Token::Type type = Token::Type::UNKNOWN;

        virtual ~Node() = default;
        Node() = default;

        // Disable copying, enable moving
        Node(const Node&) = delete;
        Node& operator=(const Node&) = delete;
        Node(Node&&) noexcept = default;
        Node& operator=(Node&&) noexcept = default;
    };

    using Nodeptr = std::unique_ptr<Node>;

    struct VariableNode : public Node {
        std::string name;
        Nodeptr value;
        bool isConst = false;
    };

    struct IdentifierNode : public Node {
        std::string name;
        Nodes::VariableNode* declaration = nullptr;
    };

    struct BinaryOpNode : public Node {
        Nodeptr left;
        Nodeptr right;
        Token::Type op;
    };

    struct UnaryOpNode : public Node {
        Nodeptr left;
        Token::Type op;
    };

    struct LiteralNode : public Node {
        VarType value;
    };

    struct ScopeNode : public Node {
        std::vector<Nodeptr> statements;

        ScopeNode() = default;
        ScopeNode(ScopeNode&&) noexcept = default;
        ScopeNode& operator=(ScopeNode&&) noexcept = default;
    };

    struct FunctionNode : public Node {
        std::string name;
        std::vector<std::string> parameters;
        ScopeNode body;
    };

    // Use Nodeptr instead of raw pointer to avoid lifetime issues
    struct CallNode : public Node {
        std::string functionName;
        std::vector<Nodeptr> arguments;
    };

    struct conditionalNode : public Node {
        Nodeptr condition;
        ScopeNode body;
    };

    struct loopNode : public Node {
        Nodeptr condition;
        ScopeNode body;
    };

    struct returnNode : public Node {
        Nodeptr value;
    };

    // Type alias for the root of the AST
    using mainNode = ScopeNode;

    /**
     * @brief Helper to create nodes with line/column info automatically.
     * Use: auto node = make_node<VariableNode>(token);
     */
    template<typename T, typename... Args>
    std::unique_ptr<T> make_node(const Token& token, Args&&... args) {
        auto node = std::make_unique<T>(std::forward<Args>(args)...);
        node->line = static_cast<unsigned int>(token.line);
        node->column = static_cast<unsigned int>(token.column);
        node->type = token.type;
        return node;
    }
}