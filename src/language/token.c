#include "token.h"


Token* create_token(TokenType token_type, const char* lexeme, uint64_t lexeme_size, void* literal, uint64_t line) {
    Token* token = malloc(sizeof(Token));
    if (token == NULL) {
        oom();
    };

    token->lexeme = calloc(lexeme_size + 1, sizeof(char));
    strncpy(token->lexeme, lexeme, lexeme_size);

    token->token_type = token_type;
    token->line = line;
    token->next_token = NULL;
    token->literal = literal;

    return token;
};


void free_tokens(Token* token) {
    Token* t = NULL;

    while (token != NULL) {
        t = token->next_token;

        if (token->literal != NULL) {
            free(token->literal);
        };

        free(token->lexeme);
        free(token);

        token = t;
    };
};
