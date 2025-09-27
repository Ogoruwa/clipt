#ifndef ERROR_H
#define ERROR_H

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"
#include "utils.h"


typedef enum ErrorType {
    Exception,
    SyntaxError,
    FileNotFoundError,
    ZeroDivisionError,
    NO_OF_ERRORS,
} ErrorType;


typedef struct Error_s {
    uint64_t start;
    uint64_t end;
    uint64_t line;
    const char* source;
    const char* message;
    ErrorType kind;
} Error;


Error* create_error(Lexer* lexer, ErrorType kind, const char* message);

void free_error(Error* err);

const char* get_error_name(ErrorType kind);

char* format_error(Error* err);

void report_error(Error* err);

void raise_error(Lexer* lexer, ErrorType kind, const char* message);


#endif
