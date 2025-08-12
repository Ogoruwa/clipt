#include <string.h>

#include "token.h"
#include "lexer.h"
#include "utils.h"


bool is_finished(Lexer *lexer){
    return lexer->current >= lexer->slen;
};


char *next_character(Lexer *lexer){
    if (lexer->current < lexer->slen){
        return &(lexer->source[lexer->current++]);
    } else {
        return NULL;
    };
};


Token *add_next_token(Lexer *lexer, TokenType token_type, void *literal){
    Token *token = NULL;
    token = malloc(sizeof(Token));

    memset(token->lexeme, '\0', sizeof token->lexeme);
    strncpy( token->lexeme, &(lexer->source[lexer->start]), (lexer->current - lexer->start) );

    token->token_type = token_type;
    token->line = lexer->line;
    token->next_token = NULL;
    token->literal = literal;

    lexer->start = lexer->current;

    return token;
};


Token *scan_token(Lexer *lexer){
    TokenType token_type = TEOF;
    char character = *next_character(lexer);

    if (is_whitespace(character)){
        return NULL;
    };

    switch (character){
        case '{': token_type = LEFT_PAREN; break;
        case '}': token_type = RIGHT_PAREN; break;
        case '(': token_type = LEFT_BRACE; break;
        case ')': token_type = RIGHT_BRACE; break;
        case '[': token_type = LEFT_BRACKET; break;
        case ']': token_type = RIGHT_BRACKET; break;

        case '!': token_type = BANG; break;
        case '=': token_type = EQUAL; break;

        case '+': token_type = PLUS; break;
        case '-': token_type = MINUS; break;
        case '*': token_type = STAR; break;
        case '/': token_type = SLASH; break;

        case '.': token_type = DOT; break;
        case ',': token_type = COMMA; break;
        case ':': token_type = COLON; break;
        case ';': token_type = SEMICOLON; break;

        case '\'': token_type = SINGLE_QUOTE; break;
        case '"': token_type = DOUBLE_QUOTE; break;

        default: return NULL; break;
    };

    // TODO: Add chracter analysis to determine what token to create
    return add_next_token(lexer, token_type, NULL);
};


Token *scan_tokens(Lexer *lexer){
    Token *token = NULL;
    Token *first_token = NULL;
    Token *prev_token = NULL;

    while(!is_finished(lexer)){
        lexer->start = lexer->current;
        token = scan_token(lexer);

        if(token == NULL){
            token = prev_token;
            continue;
        };

        if (prev_token == NULL){
            first_token = token;
        } else {
            prev_token->next_token = token;
        };

        prev_token = token;
    };

    prev_token = token = NULL;
    return first_token;
};


void reset_lexer(Lexer *lexer){
    memset(lexer, 0, sizeof *lexer);
    lexer->line = 1;
    lexer->source = NULL;
};
