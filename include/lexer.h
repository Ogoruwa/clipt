#ifndef LEXER_H
#define LEXER_H

#include "token.h"


typedef struct Lexer {
    uint64_t start;
    uint64_t current;
    uint64_t line;
    uint64_t slen;
    char *source;
} Lexer;


Token *scan_tokens(Lexer *lexer);

void reset_lexer(Lexer *lexer);


#endif
