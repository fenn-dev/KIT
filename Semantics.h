#include <variant>
#include <vector>
#include <string>
#include <map>
#include "Tokens.hpp"

struct NodeValue {
    using variant_type = std::variant<
        std::monostate,
        long long,
        double,
        std::string,
        std::vector<NodeValue>,
        std::map<std::string, NodeValue>
    >;

    variant_type data;

    NodeValue& operator[](const std::string& key) {
        if (!std::holds_alternative<std::map<std::string, NodeValue>>(data)) {
            data = std::map<std::string, NodeValue>{};
        }
        return std::get<std::map<std::string, NodeValue>>(data)[key];
    }

    template<typename T>
    NodeValue& operator=(T&& value) {
        data = std::forward<T>(value);
        return *this;
    }

    NodeValue& operator=(long long i) {
        data = i;
        return *this;
    }

    NodeValue& operator=(Token::Type t) {
        data = static_cast<long long>(t);
        return *this;
    }

    NodeValue& operator=(std::string s) {
        data = std::move(s);
        return *this;
    }

    NodeValue& operator=(std::vector<NodeValue> v) {
        data = std::move(v);
        return *this;
    }

    NodeValue(Token::Type t) : data(static_cast<long long>(t)) {}

    NodeValue(const char* s) : data(std::string(s)) {}
    NodeValue(long long i) : data(i) {}
    NodeValue() : data(std::monostate{}) {}

    void push_back(const NodeValue& value) {
        if (!std::holds_alternative<std::vector<NodeValue>>(data)) {
            data = std::vector<NodeValue>{};
        }
        std::get<std::vector<NodeValue>>(data).push_back(value);
    }
};

NodeValue semantics;

NodeValue varSyntax;
using T = Token::Type;

void ExpressionSyntax() {
    NodeValue expr;
    expr["kind"] = "CHOICE";
    expr["options"] = std::vector<NodeValue>{
        "FUNCTION_CALL",
        "IF_BLOCK",
        "BINARY_OP",
        T::NUMBER,
        T::IDENTIFIER
    };

    semantics["EXPRESSION"] = expr;
}

void LetSyntax() {
    NodeValue rule;
    rule["kind"] = "SEQUENCE";
    rule["trigger"] = T::LET;

    NodeValue steps;

    NodeValue s1;
    s1["type"] = T::IDENTIFIER;
    s1["optional"] = false;

    NodeValue s2;
    s2["kind"] = "GROUP";
    s2["sequence"] = std::vector<NodeValue>{ T::COLON, T::TYPE_KEYWORD };
    s2["optional"] = true;

    NodeValue s3;
    s3["kind"] = "GROUP";
    s3["sequence"] = std::vector<NodeValue>{ T::ASSIGN, "EXPRESSION" };
    s3["optional"] = true;

    NodeValue s4;
    s4["type"] = T::SEMICOLON;
    s4["optional"] = false;

    steps.push_back(s1);
    steps.push_back(s2);
    steps.push_back(s3);
    steps.push_back(s4);

    rule["steps"] = steps;

    semantics["LET_STATEMENT"] = rule;
}

void ConstSyntax() {
    NodeValue rule;
    rule["kind"] = "SEQUENCE";
    rule["trigger"] = T::CONST;

    NodeValue steps;

    NodeValue s1;
    s1["type"] = T::IDENTIFIER;
    s1["optional"] = false;

    NodeValue s2;
    s2["kind"] = "GROUP";
    s2["sequence"] = std::vector<NodeValue>{ T::COLON, T::TYPE_KEYWORD };
    s2["optional"] = true;

    NodeValue s3;
    s3["kind"] = "GROUP";
    s3["sequence"] = std::vector<NodeValue>{ T::ASSIGN, "EXPRESSION" };
    s3["optional"] = true;

    NodeValue s4;
    s4["type"] = T::SEMICOLON;
    s4["optional"] = false;

    steps.push_back(s1);
    steps.push_back(s2);
    steps.push_back(s3);
    steps.push_back(s4);

    rule["steps"] = steps;

    semantics["CONST_STATEMENT"] = rule;
}

void InitSyntax() {
    ExpressionSyntax();
    LetSyntax();
    ConstSyntax();

}
