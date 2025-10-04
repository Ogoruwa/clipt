#ifndef UTILS_TEST_H
#define UTILS_TEST_H

#include "error.h"
#include "lexer.h"


bool compare_lexers(Lexer* a, Lexer* b);

void handle_test_error(void* handler, ErrorInfo* info);

Lexer* create_test_lexer(const char* source);


#endif
