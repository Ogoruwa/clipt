#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "lexer.h"
#include "token.h"


void test_scan_tokens_empty_source() {
    Lexer lexer = {0, 0, 1, 0, ""};
    Token* token = scan_tokens(&lexer);

    assert(token == NULL);
    assert(lexer.line == 1);

    free_tokens(token);
    printf("test_scan_tokens_empty_source passed.\n");
};


void test_scan_tokens_single_character() {
    Lexer lexer = {0, 0, 1, 1, "("};
    Token* token = scan_tokens(&lexer);

    assert(token != NULL);
    assert(lexer.line == 1);

    assert(strcmp(token->lexeme, "(") == 0);
    assert(token->token_type == LEFT_BRACE);
    assert(token->literal == NULL);
    assert(token->next_token == NULL);
    assert(token->line == 1);

    free_tokens(token);
    printf("test_scan_tokens_single_character passed.\n");
};


void test_scan_tokens_multiple_characters() {
    Lexer lexer = {0, 0, 1, 3, "( )"};
    Token* token = scan_tokens(&lexer);
    Token* t = token;

    assert(token != NULL);
    assert(lexer.line == 1);

    assert(strcmp(token->lexeme, "(") == 0);
    assert(token->token_type == LEFT_BRACE);
    assert(token->literal == NULL);
    assert(token->line == 1);

    token = token->next_token;

    assert(token != NULL);
    assert(strcmp(token->lexeme, ")") == 0);
    assert(token->token_type == RIGHT_BRACE);
    assert(token->next_token == NULL);
    assert(token->literal == NULL);
    assert(token->line == 1);

    free_tokens(t);
    printf("test_scan_tokens_multiple_characters passed.\n");
};


void test_scan_tokens_multiple_lines() {
    const char* source = "( (\n(  (\n((";
    Lexer lexer = {0, 0, 1, strlen(source), source};
    Token* token = scan_tokens(&lexer);
    Token* t = token;

    assert(token != NULL);
    assert(lexer.line == 3);

    short int i = 1;
    while (token != NULL) {
        assert(strcmp(token->lexeme, "(") == 0);
        assert(token->token_type == LEFT_BRACE);
        assert(token->literal == NULL);
        token = token->next_token;
        i++;
    };
    assert(i == 7);

    free_tokens(t);
    printf("test_scan_tokens_multiple_lines passed.\n");
};


void test_scan_tokens_comments() {
    const char* source = "//( (\n( (\n()";
    Lexer lexer = {0, 0, 1, strlen(source), source};
    Token* token = scan_tokens(&lexer);
    Token* t = token;

    assert(token != NULL && lexer.line == 3);

    // Skip all the way to the last token
    while (token->next_token != NULL) {
        token = token->next_token;
    };

    assert(token->line == 3);
    assert(token->literal == NULL);
    assert(token->token_type == RIGHT_BRACE);
    assert(strcmp(token->lexeme, ")") == 0);

    free_tokens(t);
    printf("test_scan_tokens_comments passed.\n");
};


void test_scan_tokens_two_character_lexemes() {
    const char* source = "!===<=>=";
    Lexer lexer = {0, 0, 1, strlen(source), source};
    Token* token = scan_tokens(&lexer);
    Token* t = token;

    assert(token != NULL);
    assert(lexer.line == 1);

    assert(token->token_type == BANG_EQUAL);
    assert(token->literal == NULL);
    assert(strcmp(token->lexeme, "!=") == 0);

    token = token->next_token;
    assert(token != NULL);
    assert(token->token_type == EQUAL_EQUAL);
    assert(token->literal == NULL);
    assert(strcmp(token->lexeme, "==") == 0);

    token = token->next_token;
    assert(token != NULL);
    assert(token->token_type == LESS_EQUAL);
    assert(token->literal == NULL);
    assert(strcmp(token->lexeme, "<=") == 0);

    token = token->next_token;
    assert(token != NULL);
    assert(token->token_type == GREATER_EQUAL);
    assert(token->literal == NULL);
    assert(strcmp(token->lexeme, ">=") == 0);

    free_tokens(t);
    printf("test_scan_tokens_two_character_lexemes passed.\n");
};


void test_scan_tokens_string_single_quote() {
    const char* source = "['Hello World']";
    Lexer lexer = {0, 0, 1, strlen(source), source};
    Token* token = scan_tokens(&lexer);
    Token* t = token;

    assert(token != NULL);
    assert(lexer.line == 1);

    assert(token->token_type == LEFT_BRACKET);
    assert(token->line == 1);
    assert(token->literal == NULL);
    assert(strcmp(token->lexeme, "[") == 0);
    token = token->next_token;

    assert(token != NULL);
    assert(token->token_type == STRING);
    assert(token->line == 1);
    assert(strcmp(token->lexeme, "'Hello World'") == 0);
    assert(strcmp(token->literal, "Hello World") == 0);
    token = token->next_token;

    assert(token != NULL);
    assert(token->token_type == RIGHT_BRACKET);
    assert(token->line == 1);
    assert(token->literal == NULL);
    assert(strcmp(token->lexeme, "]") == 0);
    assert(token->next_token == NULL);

    free_tokens(t);
    printf("test_scan_tokens_string_single_quote passed.\n");
};


void test_scan_tokens_string_double_quote() {
    const char* source = "(\n\"Quote\"";
    Lexer lexer = {0, 0, 1, strlen(source), source};
    Token* token = scan_tokens(&lexer);
    Token* t = token;

    assert(token != NULL);
    assert(lexer.line == 2);

    assert(token->token_type == LEFT_BRACE);
    assert(token->line == 1);
    assert(token->literal == NULL);
    assert(strcmp(token->lexeme, "(") == 0);
    token = token->next_token;

    assert(token != NULL);
    assert(token->token_type == STRING);
    assert(token->line == 2);
    assert(strcmp(token->lexeme, "\"Quote\"") == 0);
    assert(strcmp(token->literal, "Quote") == 0);
    assert(token->next_token == NULL);

    free_tokens(t);
    printf("test_scan_tokens_string_double_quote passed.\n");
};


void test_scan_tokens_numbers() {
    const char* source = "10.1 900\n007 \n0301 201.187.0";
    Lexer lexer = {0, 0, 1, strlen(source), source};
    Token* token = scan_tokens(&lexer);
    Token* t = token;

    assert(token != NULL);
    assert(lexer.line == 3);

    assert(token->token_type == NUMBER);
    assert(token->line == 1);
    assert(strcmp(token->lexeme, "10.1") == 0);
    assert(*((double*)token->literal) == 10.1);
    token = token->next_token;

    assert(token != NULL);
    assert(token->token_type == NUMBER);
    assert(token->line == 1);
    assert(strcmp(token->lexeme, "900") == 0);
    assert(*((double*)token->literal) == 900);
    token = token->next_token;

    assert(token != NULL);
    assert(token->token_type == NUMBER);
    assert(token->line == 2);
    assert(strcmp(token->lexeme, "007") == 0);
    assert(*((double*)token->literal) == 7);
    token = token->next_token;

    assert(token != NULL);
    assert(token->token_type == NUMBER);
    assert(token->line == 3);
    assert(strcmp(token->lexeme, "0301") == 0);
    assert(*((double*)token->literal) == 301);
    token = token->next_token;

    assert(token != NULL);
    assert(token->token_type == NUMBER);
    assert(token->line == 3);
    assert(strcmp(token->lexeme, "201.187") == 0);
    assert(*((double*)token->literal) == 201.187);
    token = token->next_token;

    assert(token != NULL);
    assert(token->token_type == DOT);
    assert(token->line == 3);
    assert(strcmp(token->lexeme, ".") == 0);
    token = token->next_token;

    assert(token != NULL);
    assert(token->token_type == NUMBER);
    assert(token->line == 3);
    assert(strcmp(token->lexeme, "0") == 0);
    assert(*((double*)token->literal) == 0);
    token = token->next_token;
    assert(token == NULL);

    free_tokens(t);
    printf("test_scan_tokens_numbers passed.\n");
};


void test_scan_tokens_identifiers() {
    const char* source = "var1 _no2 _3 06 9r";
    Lexer lexer = {0, 0, 1, strlen(source), source};
    Token* token = scan_tokens(&lexer);
    Token* t = token;
    double* temp_n = malloc(sizeof(double));

    assert(token->token_type == IDENTIFIER);
    assert(strcmp(token->lexeme, "var1") == 0);

    token = token->next_token;
    assert(token != NULL);
    assert(tokencmp(token, &(Token){"_no2", IDENTIFIER, 1, NULL}));

    token = token->next_token;
    assert(token != NULL);
    assert(tokencmp(token, &(Token){"_3", IDENTIFIER, 1, NULL}));

    token = token->next_token;
    *temp_n = 6;
    assert(token != NULL);
    assert(tokencmp(token, &(Token){"06", NUMBER, 1, temp_n}));

    token = token->next_token;
    *temp_n = 9;
    assert(token != NULL);
    assert(tokencmp(token, &(Token){"9", NUMBER, 1, temp_n}));

    token = token->next_token;
    assert(token != NULL);
    assert(tokencmp(token, &(Token){"r", IDENTIFIER, 1, NULL}));
    assert(token->next_token == NULL);

    free(temp_n);
    free_tokens(t);
    printf("test_scan_tokens_identifiers passed.\n");
};


void test_scan_tokens_keywords() {
    const char* source = "if and or for while self else elif return break continue class super fn";
    Lexer lexer = {0, 0, 1, strlen(source), source};
    Token* token = scan_tokens(&lexer);
    Token* t = token;

    assert(token != NULL);
    assert(token->token_type == IF);
    assert(strcmp(token->lexeme, "if") == 0);

    while (token->next_token != NULL) {
        assert(token->literal == NULL);
        assert(token->line == 1);
        token = token->next_token;
    };

    assert(token->token_type == FN);
    assert(strcmp(token->lexeme, "fn") == 0);

    free_tokens(t);
    printf("test_scan_tokens_keywords passed.\n");
};


int test_lexer() {
    printf("\ntest_lexer started.\n");
    printf("Size of a token -> %lu bytes\n", sizeof(Token));

    test_scan_tokens_empty_source();
    test_scan_tokens_single_character();

    test_scan_tokens_multiple_characters();
    test_scan_tokens_multiple_lines();

    test_scan_tokens_comments();
    test_scan_tokens_two_character_lexemes();

    test_scan_tokens_string_single_quote();
    test_scan_tokens_string_double_quote();
    test_scan_tokens_numbers();

    test_scan_tokens_identifiers();
    test_scan_tokens_keywords();

    printf("test_lexer passed.\n");

    return 0;
};
