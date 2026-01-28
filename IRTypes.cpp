#include "LangCoreAPI.hpp"
enum class IRTypes {
    // Arithmetic
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,

    // Bitwise
    SHIFT_LEFT,
    SHIFT_RIGHT,
    AND,
    OR,
    XOR,
    NOT,

    // Memory
    LOAD,
    STORE,
    ALLOC,
    PUSH,
    POP,

    // Control Flow
    LABEL,
    JUMP,
    JUMP_IF_ZERO,
    JUMP_IF_NOT_ZERO,
    CALL,
    RETURN,

    // Comparison
    CMP_EQ,
    CMP_NE,
    CMP_LT,
    CMP_GT,

    // System/Meta
    SYSCALL,
    NOP
};