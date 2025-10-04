#ifndef ERROR_H
#define ERROR_H
#define CAST_TO_ERROR_INFO(obj, err_type)                                                          \
    (ErrorInfo) {                                                                                  \
        .start = (obj)->start, .end = (obj)->current, .line = (obj)->line, .error_type = err_type, \
        .source = (obj)->source                                                                    \
    }

#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"


typedef enum ErrorType {
    NoError,
    Exception,
    SyntaxError,
    FileNotFoundError,
    ZeroDivisionError,
    NO_OF_ERRORS,
} ErrorType;


typedef struct ErrorInfo_s {
    uint64_t start;
    uint64_t end;
    uint64_t line;
    ErrorType error_type;
    const char* source;
} ErrorInfo;


typedef struct Error_s {
    uint64_t start;
    uint64_t end;
    uint64_t line;
    ErrorType error_type;
    char* message;
    const char* source;
} Error;


Error* new_error(ErrorInfo* info, char* message);

const char* get_error_name(ErrorType error_type);

char* get_error_message(ErrorInfo* info);

char* format_error(Error* err);

void report_error(Error* err);

void handle_new_error(ErrorInfo* info);

bool errorcmp(Error* a, Error* b);

void free_error(Error* err);

typedef void (*error_handler)(void* handler, ErrorInfo* info);

#endif
