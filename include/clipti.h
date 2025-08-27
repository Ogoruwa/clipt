#ifndef INTERPRETER_H
#define INTERPRETER_H
#define FILE_BUFFER_SIZE 128

#include <stdio.h>

#include "token.h"
#include "lexer.h"


typedef struct Interpreter {
    Lexer* lexer;
} Interpreter;


short int run(Interpreter* interpreter, char* source, uint64_t size);

short int run_script(Interpreter* interpreter, char* path);


#endif
