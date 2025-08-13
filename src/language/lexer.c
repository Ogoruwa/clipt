#include <string.h>

#include "token.h"
#include "lexer.h"


bool is_finished(Lexer *lexer){
    return lexer->current >= lexer->slen;
};


char peek_character(Lexer *lexer) {
    if (is_finished(lexer)){
        return '\0';
    };
    return lexer->source[lexer->current];
};


bool match_character(Lexer *lexer, char expected){
    if (is_finished(lexer)) {
        return false;
    };

    if (lexer->source[lexer->current] == expected){
        lexer->current++;
        return true;
    } else {
        return false;
    };
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
    TokenType token_type;
    char character = *next_character(lexer);

    switch (character){
        case '\n':
            lexer->line++;
        case ' ':
        case '\r':
        case '\t': return NULL;

        case '/':
            if (match_character(lexer, '/')) {
                // Peek at next character, so comments are added to line count
                while (peek_character(lexer) != '\n' && !is_finished(lexer)){
                    next_character(lexer);
                };
                return NULL;
            } else {
                token_type = SLASH;
            };
            break;

        case '{': token_type = LEFT_PAREN; break;
        case '}': token_type = RIGHT_PAREN; break;
        case '(': token_type = LEFT_BRACE; break;
        case ')': token_type = RIGHT_BRACE; break;
        case '[': token_type = LEFT_BRACKET; break;
        case ']': token_type = RIGHT_BRACKET; break;

        case '!':
            token_type = BANG;
            token_type = match_character(lexer, '=') ? BANG_EQUAL : token_type;
            break;

        case '=':
            token_type = EQUAL;
            token_type = match_character(lexer, '=') ? EQUAL_EQUAL : token_type;
            break;

        case '<':
            token_type = LESS;
            token_type = match_character(lexer, '=') ? LESS_EQUAL : token_type;
            break;

        case '>':
            token_type = GREATER;
            token_type = match_character(lexer, '=') ? GREATER_EQUAL : token_type;
            break;

        case '+': token_type = PLUS; break;
        case '-': token_type = MINUS; break;
        case '*': token_type = STAR; break;

        case '.': token_type = DOT; break;
        case ',': token_type = COMMA; break;
        case ':': token_type = COLON; break;
        case ';': token_type = SEMICOLON; break;

        case '\'': token_type = SINGLE_QUOTE; break;
        case '"': token_type = DOUBLE_QUOTE; break;

        // TODO: Raise error
        default: return NULL;
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
