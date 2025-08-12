#ifndef INTERPRETER_H
#define INTERPRETER_H
#define FILE_BUFFER_SIZE 128

#include <stdint.h>

#include "lexer.h"
#include "utils.h"


typedef struct Interpreter {
    Lexer lexer;
} Interpreter;


short int run(Interpreter *interpreter, char* string, uint64_t size);

short int run_script(Interpreter *interpreter, char* path);


#endif
