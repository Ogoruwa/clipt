#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "clipti.h"
#include "repl.h"


void print_usage(char* name) {
    printf("Usage: %s [script]\n", name);
};


void repl() {
    run_repl();
};


short int script(char* path) {
    short int result;
    Lexer lexer = {0, 0, 1, 0, NULL};
    Interpreter interpreter = {
        &lexer,
    };

    reset_lexer(&lexer);
    result = run_script(&interpreter, path);

    return result;
};


int main(int argc, char* argv[]) {
    switch (argc) {
    case 1: repl(); break;

    case 2: script(argv[1]); break;

    default: print_usage(argv[0]); return EXIT_FAILURE;
    };

    return EXIT_SUCCESS;
};
