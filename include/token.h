#ifndef TOKEN_H
#define TOKEN_H
#define LEXEME_SIZE 4

#include <stdlib.h>
#include <stdint.h>


typedef enum TokenType {
    LEFT_PAREN = 1,
    RIGHT_PAREN = 2,
    LEFT_BRACE = 3,
    RIGHT_BRACE = 4,
    LEFT_BRACKET = 5,
    RIGHT_BRACKET = 6,
    COMMA = 7,
    DOT = 8,
    SEMICOLON = 9,
    COLON = 10,
    SINGLE_QUOTE = 11,
    DOUBLE_QUOTE = 12,

    // Arithmetic operators
    MINUS = 20,
    PLUS = 21,
    SLASH = 22,
    STAR = 23,

    // Relational operators.
    BANG = 30,
    BANG_EQUAL = 31,
    EQUAL = 32,
    EQUAL_EQUAL = 33,
    GREATER = 34,
    GREATER_EQUAL = 35,
    LESS = 36,
    LESS_EQUAL = 37,

    /* Literals */
    IDENTIFIER = 50,
    STRING = 51,
    NUMBER = 52,
    COMMENT = 57,

    /* Keywords */
    // Boolean operators.
    AND = 60,
    OR = 61,

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

    // Literals
    FALSE = 90,
    NIL = 91,
    TRUE = 92,

    // Variables
    VAR = 100,
    CONST = 101,

    PRINT = 110,

    TEOF = 128,
} TokenType;


typedef struct Token {
    char lexeme[LEXEME_SIZE];
    TokenType token_type;
    uint64_t line;
    void *literal;
    struct Token *next_token;
} Token;


void free_tokens(Token *token);


#endif
