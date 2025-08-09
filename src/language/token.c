#include "token.h"

void free_tokens(Token *token){
    Token *t = NULL;

    while (token != NULL){
        t = token->next_token;
        free(token);
        token = t;
    }
}
