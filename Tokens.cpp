#include "LangCoreAPI.hpp"

#define TOKEN_LIST(T)                   \
    /* --INTEGERS-- */                  \
    T(I8, "i8")                         \
    T(I16, "i16")                       \
    T(I32, "i32")                       \
    T(I64, "i64")                       \
    T(INT, "int")                       \
    /* --UNSIGNED INTEGERS-- */         \
    T(U8, "u8")                         \
    T(U16, "u16")                       \
    T(U32, "u32")                       \
    T(U64, "u64")                       \
    T(UINT, "uint")                     \
    /* --FLOATS-- */                    \
    T(F32, "f32")                       \
    T(FLOAT, "float")                   \
    T(F64, "f64")                       \
    T(DOUBLE, "double")                 \
    /* --WILDCARDS-- */                 \
    T(W8, "w8")                         \
    T(W16, "w16")                       \
    T(W32, "w32")                       \
    T(W64, "w64")                       \
    T(WILD, "wild")                     \
    /* --STRINGS/CHARS-- */             \
    T(CHAR, "char")                     \
    T(STRING, "string")                 \
    T(OSTRING, "ostring")               \
    /* --BOOLEAN-- */                   \
    T(BOOL, "bool")                     \
    T(BIT, "bit")                       \
    /* --CONTROL FLOW-- */              \
    T(IF, "if")                         \
    T(ELSE, "else")                     \
    T(ELIF, "elif")                     \
    T(WHILE, "while")                   \
    T(FOR, "for")                       \
    T(RETURN, "return")                 \
    T(BREAK, "break")                   \
    T(CONTINUE, "continue")             \
    T(SWITCH, "switch")                 \
    T(CASE, "case")                     \
    /* --FUNCTIONS-- */                 \
    T(FN, "fn")                         \
    /* --LITERALS-- */                  \
    T(TRUE, "true")                     \
    T(FALSE, "false")                   \
    T(LITERAL_INT, "literal_int")       \
    T(LITERAL_UINT, "literal_uint")     \
    T(LITERAL_FLOAT, "literal_float")   \
    T(LITERAL_CHAR, "literal_char")     \
    T(LITERAL_STRING, "literal_string") \
    /* --OPERATORS-- */                 \
    T(PLUS, "+")                        \
    T(MINUS, "-")                       \
    T(MULTIPLY, "*")                    \
    T(DIVIDE, "/")                      \
    T(MODULO, "%")                      \
    T(ASSIGN, "=")                      \
    T(EQUAL, "==")                      \
    T(NOT_EQUAL, "!=")                  \
    T(LESS_THAN, "<")                   \
    T(GREATER_THAN, ">")                \
    T(LESS_EQUAL, "<=")                 \
    T(GREATER_EQUAL, ">=")              \
    T(LOGICAL_AND_OP, "&&")             \
    T(LOGICAL_OR_OP, "||")              \
    T(LOGICAL_NOT_OP, "!")              \
    T(BITWISE_AND_OP, "&")              \
    T(BITWISE_OR_OP, "|")               \
    T(BITWISE_XOR_OP, "^")              \
    T(LOGICAL_AND, "and")               \
    T(LOGICAL_OR, "or")                 \
    T(LOGICAL_NOR, "nor")               \
    T(LOGICAL_NAND, "nand")             \
    T(LOGICAL_XOR, "xor")               \
    T(SHIFT_LEFT, "<<")                 \
    T(SHIFT_RIGHT, ">>")                \
    /* --SEPARATORS-- */                \
    T(LEFT_PAREN, "(")                  \
    T(RIGHT_PAREN, ")")                 \
    T(LEFT_BRACE, "{")                  \
    T(RIGHT_BRACE, "}")                 \
    T(LEFT_BRACKET, "[")                \
    T(RIGHT_BRACKET, "]")               \
    T(SEMICOLON, ";")                   \
    T(COMMA, ",")                       \
    T(DOT, ".")                         \
    T(COLON, ":")                       \
    /* --COMMENTS-- */                  \
    T(COMMENT, "//-")                   \
    T(QUESTION, "//?")                  \
    T(WARNING, "//!")                   \
    T(TODO, "//@")                      \
    T(ANSWER, "//^")                    \
    T(MULTI_COMMENT_START, "/*")        \
    T(MULTI_COMMENT_END, "*/")          \
    /* --LINKS & IMPORTS-- */           \
    T(IMPORT, "import")                 \
    T(EXPORT, "export")                 \
    T(LINK, "link")                     \
    /* --PROGRAM PROPERTIES-- */        \
    T(PROGRAM, "program")               \
    T(VERSION, "version:")              \
    T(OS, "os:")                        \
    T(ARCH, "arch:")                    \
    T(AUTHOR, "author:")                \
    T(DESCRIPTION, "description:")      \
    T(LICENSE, "license:")              \
    /* --MISCELLANEOUS-- */             \
    T(IDENTIFIER, "identifier")         \
    /* --INCREMENT/DECREMENT-- */       \
    T(INC, "++")                        \
    T(DEC, "--")                        \
    T(MULCREMENT, "**")                 \
    T(DIVCREMENT, "//")



enum class Token {
#define AS_ENUM(enum_name, str_name) enum_name,
    TOKEN_LIST(AS_ENUM)
#undef AS_ENUM
};

inline std::map<std::string_view, Token> string_to_token = {
#define AS_MAP(enum_name, str_name) { str_name, Token::enum_name },
    TOKEN_LIST(AS_MAP)
#undef AS_MAP
};