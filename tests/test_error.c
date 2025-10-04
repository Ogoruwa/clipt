#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "error.h"
#include "lexer.h"
#include "utils_test.h"


void test_error_names() {
    assert(strcmp(get_error_name(NoError), "NoError") == 0);
    assert(strcmp(get_error_name(Exception), "Exception") == 0);
    assert(strcmp(get_error_name(SyntaxError), "SyntaxError") == 0);
    assert(strcmp(get_error_name(ZeroDivisionError), "ZeroDivisionError") == 0);
    assert(strcmp(get_error_name(FileNotFoundError), "FileNotFoundError") == 0);

    // An error here means an error name was not set
    for (ErrorType i = 0; i < NO_OF_ERRORS; i++) {
        assert(get_error_name(i) != NULL);
    };

    assert(get_error_name(NO_OF_ERRORS) == NULL);
    printf("test_error_names passed.\n");
};


void test_error_messages() {
    Lexer* lexer = create_test_lexer("Error test");

    for (int i = 0; i < NO_OF_ERRORS - 1; i++) {
        char* message = get_error_message(&CAST_TO_ERROR_INFO(lexer, (ErrorType)i));
        assert(message != NULL);
        assert(strlen(message) > 0);
        free(message);
    };

    free(lexer);
    printf("test_error_messages passed.\n");
}


void test_error_creation() {
    const char* source = "Hello World !";
    const char* temp_s = "World not found";

    char* message = calloc(strlen(temp_s) + 1, sizeof(char));
    strncpy(message, temp_s, strlen(temp_s));

    Lexer lexer = {0, 0, 1, strlen(source), source};
    Error* err = new_error(&CAST_TO_ERROR_INFO(&lexer, FileNotFoundError), message);

    assert(errorcmp(err, &(Error){0, 0, 1, FileNotFoundError, "World not found", source}));

    free_error(err);
    printf("test_error_creation passed.\n");
};


void test_error_handling() {
    Lexer* lexer = create_test_lexer("An error occured here.");
    ErrorInfo info = CAST_TO_ERROR_INFO(lexer, Exception);

    handle_new_error(&info);
    free_lexer(lexer);
    printf("test_error_handling passed.\n");
};


int test_error() {
    printf("test_error started.\n");
    printf("Offsets ================>\n");
    printf("  start      ->   %zu bytes\n", offsetof(Error, start));
    printf("  end        ->   %zu bytes\n", offsetof(Error, end));
    printf("  line       ->  %zu bytes\n", offsetof(Error, line));
    printf("  error_type ->  %zu bytes\n", offsetof(Error, error_type));
    printf("  message    ->  %zu bytes\n", offsetof(Error, message));
    printf("  source     ->  %zu bytes\n", offsetof(Error, source));
    printf("Error        ->  %zu bytes\n", sizeof(Error));

    test_error_names();
    test_error_messages();

    test_error_creation();

    test_error_handling();

    printf("test_error passed.\n");

    return 0;
};
