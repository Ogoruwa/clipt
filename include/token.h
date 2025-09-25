#ifndef TOKEN_H
#define TOKEN_H
#define LEXEME_SIZE 5

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "hashmap.h"

#include "utils.h"


typedef enum TokenType {
    // Blocks
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    LEFT_BRACKET,
    RIGHT_BRACKET,

    // Separators
    COMMA,
    DOT,
    SEMICOLON,
    COLON,

    // Arithmetic operators
    MINUS,
    PLUS,
    SLASH,
    STAR,

    // Boolean operators.
    AND,
    OR,

    // Relational operators.
    BANG,
    BANG_EQUAL,
    EQUAL,
    EQUAL_EQUAL,
    GREATER,
    GREATER_EQUAL,
    LESS,
    LESS_EQUAL,

    // Literals
    NIL,
    FALSE,
    TRUE,
    IDENTIFIER,
    STRING,
    NUMBER,

    // Control flow
    FOR,
    WHILE,
    IF,
    ELSE,
    ELIF,
    CONTINUE,
    BREAK,
    RETURN,

    // Functions and classes
    FN,
    CLASS,
    SUPER,
    SELF,

    // Keywords
    PRINT,

    TEOF,
    NO_OF_TOKENS
} TokenType;


typedef struct Token_s {
    char* lexeme;
    TokenType token_type;
    uint64_t line;
    void* literal;
    struct Token_s* next_token;
} Token;


typedef struct KeywordHash_s {
    TokenType token_type;
    const char* lexeme;
} KeywordHash;


Token* create_token(TokenType token_type, const char* lexeme, uint64_t lexeme_size, void* literal, uint64_t line);

void free_tokens(Token* token);

bool tokencmp(Token* a, Token* b);

void print_token(Token* token);

const char* get_token_type_name(TokenType token_type);

struct hashmap* get_keyword_hashmap();


#endif
