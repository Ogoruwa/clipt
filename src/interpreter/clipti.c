#include <errno.h>
#include <stdio.h>

#include "clipti.h"
#include "lexer.h"


short int run(char *source, uint64_t size){
    Token *token = NULL;

    size = strrssize(source, size);
    if (size == 0){
        return 0;
    }

    Lexer lexer = {0, 0, 1, size, source};
    token = scan_tokens(&lexer);

    Token *t = token;
    while (1){
        printf("%s", t->lexeme);
        t = t->next_token;
        if (t == NULL) {break;}
    };
    printf("\n");

    free_tokens(token);
    return 0;
};


short int run_script(char* path){
    FILE *fp;
    fp = fopen(path, "r");

    if (fp == NULL) {
        perror("Error");
        return 1;

    } else {
        char buffer[FILE_BUFFER_SIZE];

        while (fgets(buffer, FILE_BUFFER_SIZE, fp) != NULL) {
            run(buffer, FILE_BUFFER_SIZE);
        };

        fclose(fp);
    }

    return 0;
};
