#include <stdio.h>
#include <stdlib.h>


void print_usage(char* name) {
    printf("Usage: %s [script]", name);
}


short run_repl(){
    return 0;
}


short run_script(char* path){
    printf("%s ", path);
    return 0;
}


int main(int argc, char** args) {
    short error_code = 0;

    switch (argc){
        case 0:
            error_code = run_repl();
            break;

        case 1:
            error_code = run_script(args[1]);
            break;

        default:
            print_usage(args[0]);
            error_code = 1;
    };

    exit(error_code);
}
