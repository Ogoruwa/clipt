#ifndef LEXER_H
#define LEXER_H

#include <stdint.h>
#include <string.h>

#include "token.h"
#include "utils.h"


typedef struct Lexer_s {
    uint64_t start;
    uint64_t current;
    uint64_t line;
    uint64_t slen;
    const char* source;
} Lexer;


Token* scan_tokens(Lexer* lexer);

void reset_lexer(Lexer* lexer);


#endif
