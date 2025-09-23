#include "repl.h"


bool end_of_line(char* string) {
    uint64_t size = strlen(string);
    if (size == 0) {
        return true;
    };

    return string[size - 1] == '\n';
};


void print_intro() {
    printf("\n");
    printf("Clipti v0.1.0\n");
};


void print_usage(char* name) {
    printf("Usage: %s [script]\n", name);
};


void repl() {
    bool eol = true;
    char* fp = NULL;
    char buffer[REPL_BUFFER_SIZE] = {'\0'};

    Interpreter* interpreter = create_interpreter();
    print_intro();

    do {
        if (eol) {
            printf("> ");
            reset_lexer(interpreter->lexer);
        };

        fp = fgets(buffer, REPL_BUFFER_SIZE, stdin);
        if (ferror(stdin)) {
            perror("\n repl error");
            eol = true;

        } else {
            run(interpreter, buffer, strlen(buffer));
            eol = end_of_line(buffer);
        };
    } while (fp != NULL);

    printf("\n");
};


short int script(char* path) {
    short int result;

    Interpreter* interpreter = create_interpreter();

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
