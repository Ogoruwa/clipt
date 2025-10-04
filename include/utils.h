#ifndef UTILS_H
#define UTILS_H
#define memcheck(ptr)    \
    if ((ptr) == NULL) { \
        oom();           \
    }

#define RETURN_NULL_IF_NULL(value) \
    if ((value) == NULL) {         \
        return NULL;               \
    }

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


bool is_whitespace(char c);

bool is_digit(char c);

bool is_alpha(char c);

bool is_alphanumeric(char c);

uint64_t strrssize(const char* s, uint64_t n);

_Noreturn void oom();


#endif
