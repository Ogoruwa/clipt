#include "repl.h"


bool end_of_line(char *string){
    uint64_t size = strlen(string);
    if (size == 0){
        return true;
    };

    return string[size - 1] == '\n';
};



void print_intro(){
    printf("\n");
    printf("Clipti v0.1.0\n");
};


void run_repl(){
    bool eol = true;
    char* fp = NULL;
    char buffer[REPL_BUFFER_SIZE] = {'\0'};

    Lexer lexer = {0, 0, 1, 0, NULL};
    Interpreter interpreter = {
        &lexer,
    };

    print_intro();

    do {
        if (eol){
            printf("> ");
            reset_lexer(&lexer);
        };

        fp = fgets(buffer, REPL_BUFFER_SIZE, stdin);
        if (ferror(stdin)){
            perror("\n repl error");
            eol = true;

        } else {
            run(&interpreter, buffer, strlen(buffer));
            eol = end_of_line(buffer);
        };
    } while(fp != NULL);

    printf("\n");
};
