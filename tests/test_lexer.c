#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "lexer.h"
#include "token.h"
#include "utils_test.h"


void test_scan_tokens_empty_source() {
    Lexer* lexer = create_test_lexer("");

    Token* token = scan_tokens(lexer);
    assert(token == NULL);

    free_tokens(token);
    free_lexer(lexer);
    printf("test_scan_tokens_empty_source passed.\n");
};


void test_scan_tokens_single_character() {
    Lexer* lexer = create_test_lexer("(");
    Token* token = scan_tokens(lexer);

    assert(token != NULL);
    assert(tokencmp_e(token, &(Token){"(", LEFT_BRACE, 1, NULL, NULL}));
    assert(token->next_token == NULL);

    free_tokens(token);
    free_lexer(lexer);
    printf("test_scan_tokens_single_character passed.\n");
};


void test_scan_tokens_spaced_characters() {
    Lexer* lexer = create_test_lexer("( )");
    Token* token = scan_tokens(lexer);
    Token* first_token = token;

    assert(token != NULL);
    assert(tokencmp_e(token, &(Token){"(", LEFT_BRACE, 1, NULL, NULL}));

    token = token->next_token;
    assert(token != NULL);
    assert(tokencmp_e(token, &(Token){")", RIGHT_BRACE, 1, NULL, NULL}));
    assert(token->next_token == NULL);

    free_tokens(first_token);
    free_lexer(lexer);
    printf("test_scan_tokens_spaced_characters passed.\n");
};


void test_scan_tokens_multiple_lines() {
    Lexer* lexer = create_test_lexer("( (\n(  (\n((");
    Token* token = scan_tokens(lexer);
    Token* first_token = token;

    assert(token != NULL);

    short int i = 1;
    while (token != NULL) {
        // TODO: check line number
        assert(tokencmp(token, &(Token){"(", LEFT_BRACE, i, NULL, NULL}));
        token = token->next_token;
        i++;
    };
    assert(i == 7);

    free_tokens(first_token);
    free_lexer(lexer);
    printf("test_scan_tokens_multiple_lines passed.\n");
};


void test_scan_tokens_comments() {
    Lexer* lexer = create_test_lexer("//( (\n( (\n()");
    Token* token = scan_tokens(lexer);
    Token* first_token = token;

    assert(token != NULL);

    while (token != NULL) {
        assert(
            tokencmp_e(token, &(Token){"(", LEFT_BRACE, 2, NULL, NULL}) ||
            tokencmp_e(token, &(Token){"(", LEFT_BRACE, 3, NULL, NULL}) ||
            tokencmp_e(token, &(Token){")", RIGHT_BRACE, 3, NULL, NULL})
        );
        token = token->next_token;
    };

    free_tokens(first_token);
    free_lexer(lexer);
    printf("test_scan_tokens_comments passed.\n");
};


void test_scan_tokens_two_character_lexemes() {
    Lexer* lexer = create_test_lexer("!===<=>=");
    Token* token = scan_tokens(lexer);
    Token* first_token = token;

    assert(token != NULL);
    assert(tokencmp_e(token, &(Token){"!=", BANG_EQUAL, 1, NULL, NULL}));

    token = token->next_token;
    assert(token != NULL);
    assert(tokencmp_e(token, &(Token){"==", EQUAL_EQUAL, 1, NULL, NULL}));

    token = token->next_token;
    assert(token != NULL);
    assert(tokencmp_e(token, &(Token){"<=", LESS_EQUAL, 1, NULL, NULL}));

    token = token->next_token;
    assert(token != NULL);
    assert(tokencmp_e(token, &(Token){">=", GREATER_EQUAL, 1, NULL, NULL}));
    assert(token->next_token == NULL);

    free_tokens(first_token);
    free_lexer(lexer);
    printf("test_scan_tokens_two_character_lexemes passed.\n");
};


void test_scan_tokens_string_single_quote() {
    Lexer* lexer = create_test_lexer("['Hello World']");
    Token* token = scan_tokens(lexer);
    Token* first_token = token;

    assert(token != NULL);
    assert(tokencmp_e(token, &(Token){"[", LEFT_BRACKET, 1, NULL, NULL}));

    token = token->next_token;
    assert(token != NULL);
    assert(tokencmp_e(token, &(Token){"'Hello World'", STRING, 1, &("Hello World"), NULL}));

    token = token->next_token;
    assert(token != NULL);
    assert(tokencmp_e(token, &(Token){"]", RIGHT_BRACKET, 1, NULL, NULL}));

    assert(token->next_token == NULL);

    free_tokens(first_token);
    free_lexer(lexer);
    printf("test_scan_tokens_string_single_quote passed.\n");
};


void test_scan_tokens_string_double_quote() {
    Lexer* lexer = create_test_lexer("{\n\"Quote\"");
    Token* token = scan_tokens(lexer);
    Token* first_token = token;

    assert(token != NULL);
    tokencmp_e(token, &(Token){"{", LEFT_PAREN, 1, NULL, NULL});

    token = token->next_token;
    assert(token != NULL);
    assert(tokencmp_e(token, &(Token){"\"Quote\"", STRING, 2, &("Quote"), NULL}));

    assert(token->next_token == NULL);

    free_tokens(first_token);
    free_lexer(lexer);
    printf("test_scan_tokens_string_double_quote passed.\n");
};


void test_scan_tokens_numbers() {
    double* temp_n = malloc(sizeof(double));
    Lexer* lexer = create_test_lexer("10.1 900\n007 \n000301 201.1870.0");

    Token* token = scan_tokens(lexer);
    Token* first_token = token;

    *temp_n = 10.1;
    assert(token != NULL);
    assert(tokencmp_e(token, &(Token){"10.1", NUMBER, 1, temp_n, NULL}));

    *temp_n = 900;
    token = token->next_token;
    assert(token != NULL);
    assert(tokencmp_e(token, &(Token){"900", NUMBER, 1, temp_n, NULL}));

    *temp_n = 7;
    token = token->next_token;
    assert(token != NULL);
    assert(tokencmp_e(token, &(Token){"007", NUMBER, 2, temp_n, NULL}));

    *temp_n = 301;
    token = token->next_token;
    assert(token != NULL);
    assert(tokencmp_e(token, &(Token){"000301", NUMBER, 3, temp_n, NULL}));

    // 201.1870 is not scanned due to invalid syntax
    token = token->next_token;
    assert(token != NULL);
    assert(tokencmp_e(token, &(Token){".", DOT, 3, NULL, NULL}));

    *temp_n = 0;
    token = token->next_token;
    assert(token != NULL);
    assert(tokencmp_e(token, &(Token){"0", NUMBER, 3, temp_n, NULL}));
    assert(token->next_token == NULL);

    free(temp_n);
    free_tokens(first_token);
    free_lexer(lexer);
    printf("test_scan_tokens_numbers passed.\n");
};


void test_scan_tokens_identifiers() {
    double* temp_n = malloc(sizeof(double));
    Lexer* lexer = create_test_lexer("var1 _no2 _3 06 9r");
    Token* token = scan_tokens(lexer);
    Token* first_token = token;

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

    // 9 gets ignored because the syntax is invalid
    token = token->next_token;
    assert(token != NULL);
    assert(tokencmp(token, &(Token){"r", IDENTIFIER, 1, NULL}));
    assert(token->next_token == NULL);

    free(temp_n);
    free_tokens(first_token);
    free_lexer(lexer);
    printf("test_scan_tokens_identifiers passed.\n");
};


void test_scan_tokens_keywords() {
    Lexer* lexer = create_test_lexer("if and or for while self else elif return break continue class super fn");
    Token* token = scan_tokens(lexer);
    Token* first_token = token;

    assert(token != NULL);
    assert(tokencmp_e(token, &(Token){"if", IF, 1, NULL, NULL}));

    while (token->next_token != NULL) {
        assert(token->literal == NULL);
        assert(token->line == 1);
        token = token->next_token;
    };

    assert(tokencmp_e(token, &(Token){"fn", FN, 1, NULL, NULL}));

    free_tokens(first_token);
    free_lexer(lexer);
    printf("test_scan_tokens_keywords passed.\n");
};


int test_lexer() {
    printf("\ntest_lexer started.\n");
    printf("Offsets =================>\n");
    printf("  start       ->   %zu bytes\n", offsetof(Lexer, start));
    printf("  current     ->   %zu bytes\n", offsetof(Lexer, current));
    printf("  line        ->  %zu bytes\n", offsetof(Lexer, line));
    printf("  slen        ->  %zu bytes\n", offsetof(Lexer, slen));
    printf("  source      ->  %zu bytes\n", offsetof(Lexer, source));
    printf("  raise_error ->  %zu bytes\n", offsetof(Lexer, raise_error));
    printf("  master      ->  %zu bytes\n", offsetof(Lexer, master));
    printf("Lexer         ->  %zu bytes\n", sizeof(Lexer));

    test_scan_tokens_empty_source();
    test_scan_tokens_single_character();

    test_scan_tokens_spaced_characters();
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
