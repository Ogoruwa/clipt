#include "repl.h"


void print_intro() {
    printf("\n");
    printf("Clipti v0.1.0\n");
};


void print_usage(char* name) {
    printf("Usage: %s [script]\n", name);
};


void repl() {
    bool eol = true;
    bool newline = false;
    char* fp = NULL;
    char buffer[REPL_BUFFER_SIZE] = {'\0'};

    Interpreter* interpreter = new_interpreter();
    print_intro();

    do {
        if (eol) {
            if (newline) {
                newline = false;
                printf("\n");
            };
            printf(">>> ");
            reset_lexer(interpreter->lexer);
        };

        fp = fgets(buffer, REPL_BUFFER_SIZE, stdin);
        if (ferror(stdin)) {
            perror("\n repl error");
            eol = newline = true;

        } else {
            newline = run(interpreter, buffer, strlen(buffer));
            eol = AT_END_OF_LINE(buffer);

            memset(buffer, '\0', REPL_BUFFER_SIZE);

            if (interpreter->had_error) {
                eol = true;
                newline = false;
                interpreter->had_error = false;
            };
        };
    } while (fp != NULL);

    printf("\n");
};


short int script(char* path) {
    short int result;

    Interpreter* interpreter = new_interpreter();

    result = run_script(interpreter, path);

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
