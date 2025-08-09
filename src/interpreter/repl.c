#include "repl.h"
#include "clipti.h"


bool end_of_line(char *string){
    uint64_t size = strlen(string);
    if (size == 0) {
        return 1;
    };

    return string[size - 1] == '\n';
}

void print_intro(){
    printf("\n");
    printf("Clipti v0.1.0\n");
}

void run_repl(){
    bool eol = 1;
    char* fp = NULL;
    char buffer[REPL_BUFFER_SIZE];

    memset(buffer, '\0', REPL_BUFFER_SIZE);
    print_intro();

    do {
        if (eol){
            printf("> ");
        };

        fp = fgets(buffer, REPL_BUFFER_SIZE, stdin);

        if (ferror(stdin)){
            perror("\n repl error");
            eol = 1;

        } else {
            run(buffer, strlen(buffer));
            eol = end_of_line(buffer);
        };
    } while(fp != NULL);

    printf("\n");
}
