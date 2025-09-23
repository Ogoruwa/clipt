#ifndef REPL_H
#define REPL_H
#define REPL_BUFFER_SIZE 64

#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "clipti.h"
#include "lexer.h"


void repl();

short int script(char* path);


#endif
