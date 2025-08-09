#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "lexer.h"
#include "token.h"


void test_scan_tokens_empty_source() {
    Lexer lexer = {0, 0, 1, 0, ""};
    Token *tokens = scan_tokens(&lexer);
    assert(tokens == NULL);
    printf("test_scan_tokens_empty_source passed.\n");
}

void test_scan_tokens_single_character() {
    Lexer lexer = {0, 0, 1, 1, "("};
    Token *tokens = scan_tokens(&lexer);
    assert(tokens != NULL);
    assert(tokens->token_type == TEOF);
    assert(tokens->next_token == NULL);
    printf("test_scan_tokens_single_character passed.\n");
}

void test_scan_tokens_multiple_characters() {
    Lexer lexer = {0, 0, 1, 3, "( )"};
    Token *tokens = scan_tokens(&lexer);
    assert(tokens != NULL);

    assert(strcmp(tokens->lexeme, "(") == 0);
    assert(tokens->token_type == TEOF);
    assert(tokens->next_token != NULL);

    assert(strcmp(tokens->next_token->lexeme, " ") == 0);
    assert(tokens->next_token->token_type == TEOF);
    assert(tokens->next_token->next_token != NULL);

    assert(strcmp(tokens->next_token->next_token->lexeme, ")") == 0);
    assert(tokens->next_token->next_token->token_type == TEOF);
    assert(tokens->next_token->next_token->next_token == NULL);

    printf("test_scan_tokens_multiple_characters passed.\n");
}

int test_lexer() {
    test_scan_tokens_empty_source();
    test_scan_tokens_single_character();
    test_scan_tokens_multiple_characters();
    return 0;
}
