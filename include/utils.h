#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


bool is_whitespace(char c);

bool is_digit(char c);

uint64_t strrssize(const char* s, uint64_t n);

_Noreturn void oom();
