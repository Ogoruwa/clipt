#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


bool is_whitespace(char c);

bool is_digit(char c);

uint64_t strrssize(const char *s, uint64_t n);

_Noreturn void oom();
