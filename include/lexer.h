#ifndef LEXER_H
#define LEXER_H


#include <assert.h>
#include <stdint.h>
#include <string.h>

#include "error.h"
#include "token.h"
#include "utils.h"


typedef struct Lexer_s {
    uint64_t start;
    uint64_t current;
    uint64_t line;
    uint64_t slen;
    const char* source;
    error_handler raise_error;
    void* master;
} Lexer;


Lexer* new_lexer(const char* source, uint64_t slen, error_handler err_handler, void* master);

Token* scan_tokens(Lexer* lexer);

void reset_lexer(Lexer* lexer);

void free_lexer(Lexer* lexer);


#endif
