#include "utils_test.h"


void test_create_test_lexer() {
    const char* source = "Hello World!";
    Lexer* lexer = create_test_lexer(source);

    assert(lexer != NULL);
    assert(lexer->start == 0);
    assert(lexer->current == 0);
    assert(lexer->line == 1);
    assert(lexer->slen == strlen(source));
    assert(strcmp(lexer->source, source) == 0);
    assert(lexer->raise_error == handle_test_error);
    assert(lexer->master == NULL);

    free_lexer(lexer);
    printf("test_create_test_lexer passed.\n");
};


int test_test_utils() {
    printf("test_test_utils started.\n");

    test_create_test_lexer();

    printf("test_test_utils passed.\n");

    return 0;
};
