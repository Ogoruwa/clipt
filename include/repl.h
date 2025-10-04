#ifndef REPL_H
#define REPL_H
#define REPL_BUFFER_SIZE 64
#define AT_END_OF_LINE(string) ((string)[REPL_BUFFER_SIZE - 2] == '\0' || (string)[REPL_BUFFER_SIZE - 2] == '\n')

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clipti.h"
#include "lexer.h"


_Static_assert(
    (REPL_BUFFER_SIZE >= 4) && (REPL_BUFFER_SIZE % 2 == 0),
    "Input buffer size for REPL must be a multiple of 2 and be >= 4"
);

void repl();

short int script(char* path);


#endif
