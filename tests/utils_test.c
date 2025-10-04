#include "utils_test.h"


bool compare_lexers(Lexer* a, Lexer* b) {
    return a->start == b->start && a->current == b->current && a->line == b->line && a->slen == b->slen &&
           strcmp(a->source, b->source) == 0;
};


void handle_test_error(void* handler, ErrorInfo* info) {};


Lexer* create_test_lexer(const char* source) {
    Lexer* lexer = new_lexer(source, strlen(source), handle_test_error, NULL);

    assert(lexer != NULL);
    assert(compare_lexers(lexer, &(Lexer){0, 0, 1, strlen(source), source, NoError}));

    return lexer;
};
