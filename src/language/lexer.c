#include <string.h>

#include "token.h"
#include "lexer.h"


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
    char character = *next_character(lexer);

    // TODO: Add chracter analysis to determine what token to create
    return add_next_token(lexer, TEOF, NULL);
};


Token *scan_tokens(Lexer *lexer) {
    Token *token = NULL;
    Token *first_token = NULL;
    Token *prev_token = NULL;

    while(lexer->current < lexer->slen){
        token = scan_token(lexer);

        if (prev_token == NULL){
            first_token = token;
        } else {
            prev_token->next_token = token;
        }

        prev_token = token;
    };

    prev_token = token = NULL;
    return first_token;
};
