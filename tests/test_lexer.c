#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "lexer.h"
#include "token.h"


void test_scan_tokens_empty_source(){
    Lexer lexer = {0, 0, 1, 0, ""};
    Token *token = scan_tokens(&lexer);

    assert(token == NULL && lexer.line == 1);
    free_tokens(token);
    printf("test_scan_tokens_empty_source passed.\n");
};


void test_scan_tokens_single_character(){
    Lexer lexer = {0, 0, 1, 1, "("};
    Token *token = scan_tokens(&lexer);

    assert(token != NULL && lexer.line == 1);
    assert(strcmp(token->lexeme, "(") == 0);
    assert(token->token_type == LEFT_BRACE);
    assert(token->literal == NULL);
    assert(token->next_token == NULL);
    assert(token->line == 1 && lexer.line == 1);

    free_tokens(token);
    printf("test_scan_tokens_single_character passed.\n");
};


void test_scan_tokens_multiple_characters(){
    Lexer lexer = {0, 0, 1, 3, "( )"};
    Token *token = scan_tokens(&lexer);
    Token *t = token;

    assert(token != NULL && lexer.line == 1);

    assert(strcmp(token->lexeme, "(") == 0);
    assert(token->token_type == LEFT_BRACE);
    assert(token->literal == NULL && token->line == 1);
    assert((token = token->next_token) != NULL);

    assert(strcmp(token->lexeme, ")") == 0);
    assert(token->token_type == RIGHT_BRACE);
    assert(token->next_token == NULL);
    assert(token->literal == NULL && token->line == 1);

    free_tokens(t);
    printf("test_scan_tokens_multiple_characters passed.\n");
};


void test_scan_tokens_multiple_lines(){
    char *source = "( (\n(  (\n((";
    Lexer lexer = {0, 0, 1, strlen(source), source};
    Token *token = scan_tokens(&lexer);
    Token *t = token;

    assert(token != NULL);
    assert(lexer.line == 3);

    short int i = 1;
    while (token != NULL){
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


void test_scan_tokens_comments(){
    char *source = "//( (\n( (\n()";
    Lexer lexer = {0, 0, 1, strlen(source), source};
    Token *token = scan_tokens(&lexer);
    Token *t = token;

    assert(token != NULL && lexer.line == 3);

    // Skip all the way to the last token
    while(token->next_token != NULL){
        token = token->next_token;
    };

    assert(token->line == 3);
    assert(token->literal == NULL);
    assert(token->token_type == RIGHT_BRACE);
    assert(strcmp(token->lexeme, ")") == 0);

    free_tokens(t);
    printf("test_scan_tokens_comments passed.\n");
};


void test_scan_tokens_two_character_lexemes(){
    char *source = "!===<=>=";
    Lexer lexer = {0, 0, 1, strlen(source), source};
    Token *token = scan_tokens(&lexer);
    Token *t = token;

    assert(token != NULL && lexer.line == 1);
    assert(token->token_type == BANG_EQUAL && token->literal == NULL);
    assert(strcmp(token->lexeme, "!=") == 0);

    while(token->next_token != NULL){
        token = token->next_token;
    };

    assert(token->token_type == GREATER_EQUAL);
    assert(token->literal == NULL && lexer.line == 1);
    assert(strcmp(token->lexeme, ">=") == 0);

    free_tokens(t);
    printf("test_scan_tokens_two_character_lexemes passed.\n");
};


void test_scan_tokens_string_single_quote(){
    char *source = "['Hello World']";
    Lexer lexer = {0, 0, 1, strlen(source), source};
    Token *token = scan_tokens(&lexer);
    Token *t = token;

    assert(token != NULL && lexer.line == 1);

    assert(token->token_type == LEFT_BRACKET);
    assert(token->line == 1 && token->literal == NULL);
    assert(strcmp(token->lexeme, "[") == 0);
    assert((token = token->next_token) != NULL);

    assert(token->token_type == STRING && token->line == 1);
    assert(strcmp(token->lexeme, "'Hello World'") == 0);
    assert(strcmp(token->literal, "Hello World") == 0);
    assert((token = token->next_token) != NULL);

    assert(token->token_type == RIGHT_BRACKET);
    assert(token->line == 1 && token->literal == NULL);
    assert(strcmp(token->lexeme, "]") == 0);
    assert(token->next_token == NULL);

    free_tokens(t);
    printf("test_scan_tokens_string_single_quote passed.\n");
};


void test_scan_tokens_string_double_quote(){
    char *source = "(\n\"Quote\"";
    Lexer lexer = {0, 0, 1, strlen(source), source};
    Token *token = scan_tokens(&lexer);
    Token *t = token;

    assert(token != NULL && lexer.line == 2);

    assert(token->token_type == LEFT_BRACE);
    assert(token->line == 1 && token->literal == NULL);
    assert(strcmp(token->lexeme, "(") == 0);
    assert((token = token->next_token) != NULL);

    assert(token->token_type == STRING && token->line == 2);
    assert(strcmp(token->lexeme, "\"Quote\"") == 0);
    assert(strcmp(token->literal, "Quote") == 0);
    assert(token->next_token == NULL);

    free_tokens(t);
    printf("test_scan_tokens_string_double_quote passed.\n");
};


void test_scan_tokens_numbers(){
    char *source = "10.1 900\n007 \n0301 201.187.0";
    Lexer lexer = {0, 0, 1, strlen(source), source};
    Token *token = scan_tokens(&lexer);
    Token *t = token;

    assert(token != NULL && lexer.line == 3);

    assert(token->token_type == NUMBER && token->line == 1);
    assert(strcmp(token->lexeme, "10.1") == 0);
    assert(*((double *)token->literal) == 10.1);
    assert((token=token->next_token) != NULL);

    assert(token->token_type == NUMBER && token->line == 1);
    assert(strcmp(token->lexeme, "900") == 0);
    assert(*((double *)token->literal) == 900);
    assert((token=token->next_token) != NULL);

    assert(token->token_type == NUMBER && token->line == 2);
    assert(strcmp(token->lexeme, "007") == 0);
    assert(*((double *)token->literal) == 7);
    assert((token=token->next_token) != NULL);

    assert(token->token_type == NUMBER && token->line == 3);
    assert(strcmp(token->lexeme, "0301") == 0);
    assert(*((double *)token->literal) == 301);
    assert((token=token->next_token) != NULL);

    assert(token->token_type == NUMBER && token->line == 3);
    assert(strcmp(token->lexeme, "201.187") == 0);
    assert(*((double *)token->literal) == 201.187);
    assert((token=token->next_token) != NULL);

    assert(token->token_type == DOT && token->line == 3);
    assert(strcmp(token->lexeme, ".") == 0);
    assert((token=token->next_token) != NULL);

    assert(token->token_type == NUMBER && token->line == 3);
    assert(strcmp(token->lexeme, "0") == 0);
    assert(*((double *)token->literal) == 0);
    assert((token=token->next_token) == NULL);

    free_tokens(t);
    printf("test_scan_tokens_numbers passed.\n");
};


int test_lexer(){
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

    printf("test_lexer passed.\n");

    return 0;
};
