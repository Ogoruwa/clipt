#ifndef ERROR_H
#define ERROR_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "lexer.h"


typedef enum ErrorType {
    Exception,
    SyntaxError,
    FileNotFoundError,
    ZeroDivisionError,
    NO_OF_ERRORS,
} ErrorType;

typedef struct Error {
    uint64_t start;
    uint64_t end;
    uint64_t line;
    const char* source;
    const char* message;
    ErrorType kind;
} Error;


Error* error(Lexer *lexer, ErrorType kind, const char* message);

void free_error(Error *err);

const char* get_error_name(ErrorType kind);

char* format_error(Error *exception);

void report_error(Error *exception);

void raise_error(Lexer *lexer, ErrorType kind, const char* message);


#endif
