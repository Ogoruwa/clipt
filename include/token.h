#ifndef TOKEN_H
#define TOKEN_H
#define LEXEME_SIZE 5

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"


typedef enum TokenType {
    // Blocks
    LEFT_PAREN = 1,
    RIGHT_PAREN = 2,
    LEFT_BRACE = 3,
    RIGHT_BRACE = 4,
    LEFT_BRACKET = 5,
    RIGHT_BRACKET = 6,

    // Separators
    COMMA = 7,
    DOT = 8,
    SEMICOLON = 9,
    COLON = 10,

    // Arithmetic operators
    MINUS = 20,
    PLUS = 21,
    SLASH = 22,
    STAR = 23,

    // Boolean operators.
    AND = 30,
    OR = 31,

    // Relational operators.
    BANG = 40,
    BANG_EQUAL = 41,
    EQUAL = 42,
    EQUAL_EQUAL = 43,
    GREATER = 44,
    GREATER_EQUAL = 45,
    LESS = 46,
    LESS_EQUAL = 47,

    // Literals
    NIL = 60,
    FALSE = 61,
    TRUE = 62,
    VARIABLE = 63,
    CONSTANT = 64,
    STRING = 65,
    NUMBER = 66,

    // Control flow
    FOR = 70,
    WHILE = 71,
    IF = 72,
    ELSE = 73,
    ELIF = 74,
    CONTINUE = 75,
    BREAK = 76,
    RETURN = 77,

    // Functions and classes
    FN = 80,
    CLASS = 81,
    SUPER = 82,
    SELF = 83,

    // Keywords
    PRINT = 101,

    TEOF = 128,
} TokenType;


typedef struct Token_s {
    char* lexeme;
    TokenType token_type;
    uint64_t line;
    void* literal;
    struct Token_s* next_token;
} Token;


Token* create_token(TokenType token_type, const char* lexeme, uint64_t lexeme_size, void* literal, uint64_t line);

void free_tokens(Token* token);


#endif
