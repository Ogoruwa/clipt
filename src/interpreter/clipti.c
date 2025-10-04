#include "clipti.h"


bool run(Interpreter* interpreter, char* source, uint64_t size) {
    Token* token = NULL;

    if (interpreter->had_error) {
        raise_error(interpreter, &(ErrorInfo){0, 0, 0, Exception, NULL});
        return false;
    };

    size = strrssize(source, size);
    if (size == 0) {
        return false;
    };

    reset_lexer(interpreter->lexer);

    interpreter->lexer->source = source;
    interpreter->lexer->slen = size;
    token = scan_tokens(interpreter->lexer);

    if (token == NULL || interpreter->had_error) {
        return false;
    };

    // TODO: Do stuff with parsed tokens
    Token* t = token;
    while (t != NULL) {
        print_token(t);
        printf(" ");
        t = t->next_token;
    };

    free_tokens(token);

    return true;
};


bool run_script(Interpreter* interpreter, char* path) {
    FILE* fp;
    fp = fopen(path, "r");

    if (fp == NULL) {
        perror("Error");
        return 1;
    };

    char buffer[FILE_BUFFER_SIZE];

    while (!interpreter->had_error && fgets(buffer, FILE_BUFFER_SIZE, fp) != NULL) {
        (void)run(interpreter, buffer, FILE_BUFFER_SIZE);
    };

    if (fclose(fp) == EOF) {
        perror("Error closing file");
    };

    return interpreter->had_error;
};


void raise_error(Interpreter* interpreter, ErrorInfo* info) {
    interpreter->had_error = true;
    handle_new_error(info);
};


Interpreter* new_interpreter() {
    Interpreter* interpreter = (Interpreter*)malloc(sizeof(Interpreter));
    if (interpreter == NULL) {
        perror("Failed to allocate memory for interpreter");
        oom();
    };

    Lexer* lexer = new_lexer(NULL, 0, (error_handler)raise_error, interpreter);

    interpreter->had_error = false;
    interpreter->lexer = lexer;


    return interpreter;
};
