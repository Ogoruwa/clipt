#include <stdint.h>

#include "utils.h"



/**
 * @brief Returns whether a character is whitespace.
 *
 * Checks if a character is one of the following: a space, a tab, a carriage
 * return, or a newline.
 *
 * @param c The character to check.
 *
 * @return True if the character is whitespace, false otherwise.
 */
bool is_whitespace(char c){
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

/**
 * @brief Returns the size of a string with no trailing whitespace.
 *
 * @param s The string to remove trailing whitespace from.
 * @param n The length of the string.
 *
 * @return Size of the stripped string.
 */

uint64_t strrssize(const char *s, uint64_t n){
    uint64_t i = n;

    while(i >= 1){
        if (!is_whitespace(s[--i])){
            i++;
            break;
        }
    };

    return i;
}
