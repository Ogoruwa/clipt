#include "clipti.h"


short int run(Interpreter* interpreter, char* source, uint64_t size) {
    Token* token = NULL;

    size = strrssize(source, size);
    if (size == 0) {
        return 0;
    };

    interpreter->lexer->source = source;
    interpreter->lexer->slen = size;
    token = scan_tokens(interpreter->lexer);

    // Do stuff with parsed tokens
    Token* t = token;
    while (t != NULL) {
        printf("%s", t->lexeme);
        t = t->next_token;
    };

    printf("\n");
    free_tokens(token);

    return 0;
};


short int run_script(Interpreter* interpreter, char* path) {
    FILE* fp;
    fp = fopen(path, "r");

    if (fp == NULL) {
        perror("Error");
        return 1;
    };

    char buffer[FILE_BUFFER_SIZE];

    while (fgets(buffer, FILE_BUFFER_SIZE, fp) != NULL) {
        run(interpreter, buffer, FILE_BUFFER_SIZE);
    };

    if (fclose(fp) == EOF) {
        perror("Error closing file");
    };

    return 0;
};


Interpreter* create_interpreter() {
    Lexer* lexer = (Lexer*)malloc(sizeof(Lexer));
    if (lexer == NULL) {
        perror("Failed to allocate memory for lexer");
        oom();
    };
    reset_lexer(lexer);

    Interpreter* interpreter = (Interpreter*)malloc(sizeof(Interpreter));
    if (interpreter == NULL) {
        perror("Failed to allocate memory for interpreter");
        free(lexer);
        oom();
    };

    interpreter->lexer = lexer;

    return interpreter;
};
