#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "lexer.h"
#include "token.h"


void test_token_creation() {
    Token* t;
    Token* token;
    Token* first_token;

    char* temp_s0 = "'Hello World!'";
    double* temp_n = malloc(sizeof(double));
    double* temp_n2 = malloc(sizeof(double));
    char* temp_s = calloc(sizeof(char), strlen(temp_s0) - 1);
    char* temp_s2 = calloc(sizeof(char), strlen(temp_s0) - 1);

    *temp_n = *temp_n2 = 1001.007;
    strncpy(temp_s, &(temp_s0[1]), strlen(temp_s0) - 2);
    strncpy(temp_s2, &(temp_s0[1]), strlen(temp_s0) - 2);

    first_token = t = create_token(IDENTIFIER, "first_variable", strlen("first_variable"), NULL, 1);
    token = create_token(AND, "and", 3, NULL, 2);
    t->next_token = token;

    t = create_token(NUMBER, "1001.007", strlen("1001.007"), (void*)temp_n, 3);
    token->next_token = t;

    token = create_token(OR, "or", 2, NULL, 4);
    t->next_token = token;

    t = create_token(STRING, temp_s0, strlen(temp_s0), (void*)temp_s, 4);
    token->next_token = t;

    token = first_token;
    assert(tokencmp(token, &(Token){"first_variable", IDENTIFIER, 1, NULL}));

    token = token->next_token;
    assert(tokencmp(token, &(Token){"and", AND, 2, NULL}));

    token = token->next_token;
    assert(tokencmp(token, &(Token){"1001.007", NUMBER, 3, (void*)temp_n2}));

    token = token->next_token;
    assert(tokencmp(token, &(Token){"or", OR, 4, NULL}));

    token = token->next_token;
    assert(tokencmp(token, &(Token){temp_s0, STRING, 4, (void*)temp_s2}));

    free(temp_s2);
    free(temp_n2);
    free_tokens(first_token);
    printf("test_scan_tokens_empty_source passed.\n");
};


void test_token_memory() {
    Token* token;
    char* temp_s = "'TEST'";

    for (short i = 1; i < 255; i++) {
        // length - 2 for the quotes, + 1 for the null terminator
        char* literal = calloc(strlen(temp_s) - 1, sizeof(char));

        memcheck(literal);
        strncpy(literal, &(temp_s[1]), strlen(temp_s) - 2);

        token = create_token(STRING, temp_s, strlen(temp_s), literal, i);

        assert(tokencmp(token, &(Token){"'TEST'", STRING, i - 1, literal}));
        free_tokens(token);
        literal = NULL;
    };

    token = NULL;
    printf("test_token_memory finished.\n");
}


void test_token_type_names() {
    assert(strcmp(get_token_type_name(LEFT_PAREN), "LEFT_PAREN") == 0);
    assert(strcmp(get_token_type_name(RIGHT_PAREN), "RIGHT_PAREN") == 0);
    assert(strcmp(get_token_type_name(LEFT_BRACKET), "LEFT_BRACKET") == 0);
    assert(strcmp(get_token_type_name(RIGHT_BRACKET), "RIGHT_BRACKET") == 0);
    assert(strcmp(get_token_type_name(COMMA), "COMMA") == 0);
    assert(strcmp(get_token_type_name(DOT), "DOT") == 0);
    assert(strcmp(get_token_type_name(SEMICOLON), "SEMICOLON") == 0);
    assert(strcmp(get_token_type_name(COLON), "COLON") == 0);
    assert(strcmp(get_token_type_name(MINUS), "MINUS") == 0);
    assert(strcmp(get_token_type_name(PLUS), "PLUS") == 0);
    assert(strcmp(get_token_type_name(SLASH), "SLASH") == 0);
    assert(strcmp(get_token_type_name(STAR), "STAR") == 0);
    assert(strcmp(get_token_type_name(AND), "AND") == 0);
    assert(strcmp(get_token_type_name(OR), "OR") == 0);
    assert(strcmp(get_token_type_name(BANG), "BANG") == 0);
    assert(strcmp(get_token_type_name(BANG_EQUAL), "BANG_EQUAL") == 0);
    assert(strcmp(get_token_type_name(EQUAL), "EQUAL") == 0);
    assert(strcmp(get_token_type_name(EQUAL_EQUAL), "EQUAL_EQUAL") == 0);
    assert(strcmp(get_token_type_name(GREATER), "GREATER") == 0);
    assert(strcmp(get_token_type_name(GREATER_EQUAL), "GREATER_EQUAL") == 0);
    assert(strcmp(get_token_type_name(LESS), "LESS") == 0);
    assert(strcmp(get_token_type_name(LESS_EQUAL), "LESS_EQUAL") == 0);
    assert(strcmp(get_token_type_name(NIL), "NIL") == 0);
    assert(strcmp(get_token_type_name(FALSE), "FALSE") == 0);
    assert(strcmp(get_token_type_name(TRUE), "TRUE") == 0);
    assert(strcmp(get_token_type_name(IDENTIFIER), "IDENTIFIER") == 0);
    assert(strcmp(get_token_type_name(STRING), "STRING") == 0);
    assert(strcmp(get_token_type_name(NUMBER), "NUMBER") == 0);
    assert(strcmp(get_token_type_name(FOR), "FOR") == 0);
    assert(strcmp(get_token_type_name(WHILE), "WHILE") == 0);
    assert(strcmp(get_token_type_name(IF), "IF") == 0);
    assert(strcmp(get_token_type_name(ELSE), "ELSE") == 0);
    assert(strcmp(get_token_type_name(ELIF), "ELIF") == 0);
    assert(strcmp(get_token_type_name(CONTINUE), "CONTINUE") == 0);
    assert(strcmp(get_token_type_name(BREAK), "BREAK") == 0);
    assert(strcmp(get_token_type_name(RETURN), "RETURN") == 0);
    assert(strcmp(get_token_type_name(FN), "FN") == 0);
    assert(strcmp(get_token_type_name(CLASS), "CLASS") == 0);
    assert(strcmp(get_token_type_name(SUPER), "SUPER") == 0);
    assert(strcmp(get_token_type_name(SELF), "SELF") == 0);
    assert(strcmp(get_token_type_name(PRINT), "PRINT") == 0);

    assert(get_token_type_name(NO_OF_TOKENS) == NULL);

    printf("test_token_type_names passed.\n");
};


int test_token() {
    test_token_creation();
    test_token_memory();
    test_token_type_names();

    printf("test_token passed.\n");

    return 0;
};
