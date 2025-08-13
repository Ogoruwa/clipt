#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "lexer.h"
#include "token.h"


void test_scan_tokens_empty_source(){
    Lexer lexer = {0, 0, 1, 0, ""};
    Token *tokens = scan_tokens(&lexer);

    assert(tokens == NULL);

    printf("test_scan_tokens_empty_source passed.\n");
};


void test_scan_tokens_single_character(){
    Lexer lexer = {0, 0, 1, 1, "("};
    Token *tokens = scan_tokens(&lexer);

    assert(tokens != NULL);
    assert(strcmp(tokens->lexeme, "(") == 0);
    assert(tokens->token_type == LEFT_BRACE);
    assert(tokens->next_token == NULL);

    printf("test_scan_tokens_single_character passed.\n");
};


void test_scan_tokens_multiple_characters(){
    Lexer lexer = {0, 0, 1, 3, "( )"};
    Token *tokens = scan_tokens(&lexer);
    assert(tokens != NULL);

    assert(strcmp(tokens->lexeme, "(") == 0);
    assert(tokens->token_type == LEFT_BRACE);
    assert(tokens->next_token != NULL);

    assert(strcmp(tokens->next_token->lexeme, ")") == 0);
    assert(tokens->next_token->token_type == RIGHT_BRACE);
    assert(tokens->next_token->next_token == NULL);

    printf("test_scan_tokens_multiple_characters passed.\n");
};


void test_scan_tokens_multiple_lines(){
    char *source = "( (\n( (\n((";
    Lexer lexer = {0, 0, 1, strlen(source), source};
    Token *tokens = scan_tokens(&lexer);

    assert(tokens != NULL);
    assert(lexer.line == 3);

    short int i = 0;
    while (tokens != NULL){
        assert(strcmp(tokens->lexeme, "(") == 0);
        assert(tokens->token_type == LEFT_BRACE);
        tokens = tokens->next_token;
        i++;
    };

    assert(i == 6);
    printf("test_scan_tokens_multiple_lines passed.\n");
};

void test_scan_tokens_comments(){
    char *source = "//( (\n( (\n()";
    Lexer lexer = {0, 0, 1, strlen(source), source};
    Token *tokens = scan_tokens(&lexer);

    assert(tokens != NULL);
    assert(lexer.line == 3);

    while(tokens->next_token != NULL){
        tokens = tokens->next_token;
    };

    assert(tokens->token_type == RIGHT_BRACE);
    assert(strcmp(tokens->lexeme, ")") == 0);

    printf("test_scan_tokens_comments passed.\n");
};


void test_scan_tokens_two_character_lexemes(){
    char *source = "!===<=>=";
    Lexer lexer = {0, 0, 1, strlen(source), source};
    Token *tokens = scan_tokens(&lexer);

    assert(tokens != NULL);
    assert(tokens->token_type == BANG_EQUAL);
    assert(strcmp(tokens->lexeme, "!=") == 0);

    while(tokens->next_token != NULL){
        tokens = tokens->next_token;
    };

    assert(tokens->token_type == GREATER_EQUAL);
    assert(strcmp(tokens->lexeme, ">=") == 0);

    printf("test_scan_tokens_two_character_lexemes passed.\n");
}


int test_lexer(){
    test_scan_tokens_empty_source();
    test_scan_tokens_single_character();

    test_scan_tokens_multiple_characters();
    test_scan_tokens_multiple_lines();

    test_scan_tokens_comments();
    test_scan_tokens_two_character_lexemes();

    return 0;
};
