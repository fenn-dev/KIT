#pragma once
#include <string>
#include <variant>
#include <algorithm>
#include <cctype>

struct Wild {
    std::string binary_data;
    // Helper to get the pointer when you actually need to use it in your API
    void* get() const { return (void*)binary_data.data(); }
};

using VarType = std::variant<std::monostate, bool, int, unsigned int, float, char, std::string, Wild>;

inline VarType identifyType(const std::string& str) {
    if (str.empty()) return std::monostate{};

    // 1. Check Bool
    if (str == "true" || str == "1") return true;
    if (str == "false" || str == "0") return false;

    // 2. Check Char
    if (str.length() == 1 && !std::isdigit(static_cast<unsigned char>(str[0]))) return str[0];

    // 3. Check Numeric Types (Integers)
    try {
        size_t pos;
        if (str[0] == '-') {
            int i = std::stoi(str, &pos);
            if (pos == str.length()) return i;
        }
        else {
            unsigned long ul = std::stoul(str, &pos);
            // Ensure it fits in unsigned int and doesn't just wrap
            if (pos == str.length()) return static_cast<unsigned int>(ul);
        }
    }
    catch (...) {}

    // 3b. Check Numeric Types (Float)
    try {
        size_t pos;
        float f = std::stof(str, &pos);
        if (pos == str.length()) return f;
    }
    catch (...) {}

    // 4. Check for "Wild" (Binary/Non-printable)
    bool isWild = std::any_of(str.begin(), str.end(), [](unsigned char c) {
        return std::isprint(c) == 0 && !std::isspace(c);
        });

    if (isWild) {
        // Store the actual data inside the Wild struct
        return Wild{ str };
    }

    // 5. Default to string
    return str;
}