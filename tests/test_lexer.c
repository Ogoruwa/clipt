#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "lexer.h"
#include "token.h"


void test_scan_tokens_empty_source(){
    Lexer lexer = {0, 0, 1, 0, ""};
    Token *token = scan_tokens(&lexer);
    assert(token == NULL);

    free_tokens(token);
    printf("test_scan_tokens_empty_source passed.\n");
};


void test_scan_tokens_single_character(){
    Lexer lexer = {0, 0, 1, 1, "("};
    Token *token = scan_tokens(&lexer);

    assert(token != NULL);
    assert(strcmp(token->lexeme, "(") == 0);
    assert(token->token_type == LEFT_BRACE);
    assert(token->next_token == NULL);

    free_tokens(token);
    printf("test_scan_tokens_single_character passed.\n");
};


void test_scan_tokens_multiple_characters(){
    Lexer lexer = {0, 0, 1, 3, "( )"};
    Token *token = scan_tokens(&lexer);
    Token *t = token;
    assert(token != NULL);

    assert(strcmp(token->lexeme, "(") == 0);
    assert(token->token_type == LEFT_BRACE);
    assert(token->next_token != NULL);

    assert(strcmp(token->next_token->lexeme, ")") == 0);
    assert(token->next_token->token_type == RIGHT_BRACE);
    assert(token->next_token->next_token == NULL);

    free_tokens(t);
    printf("test_scan_tokens_multiple_characters passed.\n");
};


void test_scan_tokens_multiple_lines(){
    char *source = "( (\n( (\n((";
    Lexer lexer = {0, 0, 1, strlen(source), source};
    Token *token = scan_tokens(&lexer);
    Token *t = token;

    assert(token != NULL);
    assert(lexer.line == 3);

    short int i = 0;
    while (token != NULL){
        assert(strcmp(token->lexeme, "(") == 0);
        assert(token->token_type == LEFT_BRACE);
        token = token->next_token;
        i++;
    };

    assert(i == 6);
    free_tokens(t);
    printf("test_scan_tokens_multiple_lines passed.\n");
};


void test_scan_tokens_comments(){
    char *source = "//( (\n( (\n()";
    Lexer lexer = {0, 0, 1, strlen(source), source};
    Token *token = scan_tokens(&lexer);
    Token *t = token;

    assert(token != NULL);
    assert(lexer.line == 3);

    while(token->next_token != NULL){
        token = token->next_token;
    };

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

    assert(token != NULL);
    assert(token->token_type == BANG_EQUAL);
    assert(strcmp(token->lexeme, "!=") == 0);

    while(token->next_token != NULL){
        token = token->next_token;
    };

    assert(token->token_type == GREATER_EQUAL);
    assert(strcmp(token->lexeme, ">=") == 0);

    free_tokens(t);
    printf("test_scan_tokens_two_character_lexemes passed.\n");
};


void test_scan_tokens_string_single_quote(){
    char *source = "['Hello World']";
    Lexer lexer = {0, 0, 1, strlen(source), source};
    Token *token = scan_tokens(&lexer);
    Token *t = token;
    assert(token != NULL);

    assert(token->token_type == LEFT_BRACKET);
    assert(strcmp(token->lexeme, "[") == 0);
    assert(token->next_token != NULL);

    token = token->next_token;
    assert(token->token_type == STRING);
    assert(strcmp(token->lexeme, "'Hello World'") == 0);
    assert(strcmp(token->literal, "Hello World") == 0);
    assert(token->next_token != NULL);

    token = token->next_token;
    assert(token->token_type == RIGHT_BRACKET);
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
    assert(token != NULL);

    assert(token->token_type == LEFT_BRACE);
    assert(strcmp(token->lexeme, "(") == 0);
    assert(token->next_token != NULL);

    token = token->next_token;
    assert(token->token_type == STRING);
    assert(strcmp(token->lexeme, "\"Quote\"") == 0);
    assert(strcmp(token->literal, "Quote") == 0);
    assert(token->next_token == NULL);

    free_tokens(t);
    printf("test_scan_tokens_string_double_quote passed.\n");
};


int test_lexer(){
    test_scan_tokens_empty_source();
    test_scan_tokens_single_character();

    test_scan_tokens_multiple_characters();
    test_scan_tokens_multiple_lines();

    test_scan_tokens_comments();
    test_scan_tokens_two_character_lexemes();

    test_scan_tokens_string_single_quote();

    printf("test_lexer passed.\n");

    return 0;
};
