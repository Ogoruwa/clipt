#ifndef INTERPRETER_H
#define INTERPRETER_H
#define FILE_BUFFER_SIZE 128

#include <stdio.h>

#include "error.h"
#include "lexer.h"
#include "token.h"


typedef struct Interpreter_s {
    bool had_error;
    Lexer* lexer;
} Interpreter;


bool run(Interpreter* interpreter, char* source, uint64_t size);

bool run_script(Interpreter* interpreter, char* path);

void raise_error(Interpreter* interpreter, ErrorInfo* info);

Interpreter* new_interpreter();


#endif
