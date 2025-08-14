#include "token.h"

void free_tokens(Token *token){
    Token *t = NULL;

    while (token != NULL){
        t = token->next_token;

        if (token->literal != NULL){
            free(token->literal);
        };

        free(token->lexeme);
        free(token);

        token = t;
    };
};
