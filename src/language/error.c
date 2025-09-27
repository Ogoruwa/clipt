#include "error.h"


const char* get_error_name(ErrorType kind) {
    const char* names[NO_OF_ERRORS] = {
        [Exception] = "Exception",
        [SyntaxError] = "SyntaxError",
        [FileNotFoundError] = "FileNotFoundError",
        [ZeroDivisionError] = "ZeroDivisionError"
    };

    if (kind < NO_OF_ERRORS && kind >= 0) {
        return names[kind];
    };

    return NULL;
};


char* format_error(Error* err) {
    char* text;
    const char* name = get_error_name(err->kind);

    size_t size = snprintf(NULL, 0, "[line %" PRIu64 ", %s] Error: %s\n", err->line, name, err->message) + 1;
    text = malloc(size);
    memcheck(text);

    (void)snprintf(text, size, "[line %" PRIu64 ", %s] Error: %s\n", err->line, name, err->message);
    return text;
};


void report_error(Error* err) {
    char* text = format_error(err);

    printf(text, "");
    free(text);
};


Error* create_error(Lexer* lexer, ErrorType kind, const char* message) {
    Error* err;

    err = malloc(sizeof(Error));
    memcheck(err);

    err->start = lexer->start;
    err->end = lexer->current;
    err->line = lexer->line;
    err->source = lexer->source;
    err->message = message;
    err->kind = kind;

    return err;
};


void free_error(Error* err) {
    free(err);
};


void raise_error(Lexer* lexer, ErrorType kind, const char* message) {
    Error* err;

    err = create_error(lexer, kind, message);
    report_error(err);

    free_error(err);
};
