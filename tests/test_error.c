#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "lexer.h"
#include "error.h"


void test_error_names(){
    // Seg fault is raised if error name is not set
    assert(strcmp(get_error_name(Exception), "Exception") == 0);
    assert(strcmp(get_error_name(SyntaxError), "SyntaxError") == 0);
    assert(strcmp(get_error_name(ZeroDivisionError), "ZeroDivisionError") == 0);
    assert(strcmp(get_error_name(FileNotFoundError), "FileNotFoundError") == 0);

    assert(get_error_name(NO_OF_ERRORS) == NULL);
    printf("test_error_names passed.\n");
};


void test_error_creation(){
    const char* source = "Hello World !";
    Lexer lexer = {0, 0, 1, strlen(source), source};
    Error* err = create_error(&lexer, FileNotFoundError, "File not found");

    assert(err->start == 0);
    assert(err->end == 0);
    assert(err->line == 1);
    assert(err->source == source);
    assert(strcmp(err->message, "File not found") == 0);
    assert(err->kind == FileNotFoundError);

    free_error(err);
    printf("test_error_raise passed.\n");
};


void test_error_raise(){
    const char* source = "An error occured here.";
    Lexer lexer = {0, 0, strlen(source), strlen(source), source};
    raise_error(&lexer, Exception, "Oops");

    printf("test_error_raise passed.\n");
};


int test_error(){
    test_error_names();

    test_error_creation();

    test_error_raise();

    return 0;
};
