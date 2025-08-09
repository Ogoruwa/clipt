#ifndef LEXER_H

#include "token.h"

#define LEXER_H


typedef struct {
    uint64_t start;
    uint64_t current;
    uint64_t line;
    uint64_t slen;
    char *source;
} Lexer;


Token *scan_tokens(Lexer *lexer);

#endif
