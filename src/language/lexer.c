#include "lexer.h"


bool is_finished(Lexer *lexer){
    return lexer->current >= lexer->slen;
};


bool match_character(Lexer *lexer, char expected){
    if (is_finished(lexer)) {
        return false;
    };

    if (lexer->source[lexer->current] == expected){
        lexer->current++;
        return true;
    };

    return false;
};


char peek_character(Lexer *lexer) {
    if (is_finished(lexer)){
        return '\0';
    };
    return lexer->source[lexer->current];
};


char peek_next_character(Lexer *lexer) {
    if (lexer->current+1 >= lexer->slen){
        return '\0';
    };
    return lexer->source[lexer->current+1];
};


char next_character(Lexer *lexer){
    if (is_finished(lexer)){
        return '\0';
    };
    return lexer->source[lexer->current++];
};


Token *add_next_token(Lexer *lexer, TokenType token_type, void *literal){
    Token *token = NULL;
    uint64_t size = lexer->current - lexer->start;

    token = malloc(sizeof(Token));
    if (token == NULL){
        oom();
    };

    token->lexeme = calloc(size + 1, sizeof(char));
    strncpy(token->lexeme, &(lexer->source[lexer->start]), size);

    token->token_type = token_type;
    token->line = lexer->line;
    token->next_token = NULL;
    token->literal = literal;

    lexer->start = lexer->current;

    return token;
};


char *scan_string(Lexer *lexer, bool single){
    uint64_t size = 0;
    char *value = NULL;
    char quote = single ? '\'' : '"';

    while (!is_finished(lexer) && peek_character(lexer) != quote){
        if (peek_character(lexer) == '\n'){
            lexer->line++;
        };
        next_character(lexer);
    };

    // If source has been completely scanned, string was not terminated
    // The above loop is broken only if the source has been scanned or the next character is the terminator
    if (is_finished(lexer)){
        // TODO: Raise error
        return "";
    };

    next_character(lexer);
    size = (lexer->current-1) - (lexer->start+1) + 1;

    value = malloc(size);
    if(value == NULL){
        oom();
    };

    memset(value, '\0', size);
    // +1 and -1 to ignore the quotes
    strncpy(value, &(lexer->source[lexer->start+1]), size-1);

    return value;
};


double *scan_number(Lexer *lexer){
    uint64_t size;
    char *string = NULL;
    char *remainder = NULL;
    double *value = NULL;


    while (is_digit(peek_character(lexer))){
        next_character(lexer);
    };

    if (peek_character(lexer) == '.' && is_digit(peek_next_character(lexer))){
        next_character(lexer);
        while (is_digit(peek_character(lexer))){
            next_character(lexer);
        };
    };

    size = lexer->current - lexer->start + 1;
    string = malloc(size);
    if(string == NULL){
        oom();
    };

    memset(string, '\0', size);
    strncpy(string, &(lexer->source[lexer->start]), size-1);

    value = malloc(sizeof(double));
    if(value == NULL){
        oom();
    };

    *value = strtod(string, &remainder);
    free(string);

    return value;
};


Token *scan_token(Lexer *lexer){
    TokenType token_type;
    void *literal = NULL;
    char character = next_character(lexer);

    switch (character){
        case '\n':
            lexer->line++;
        case ' ':
        case '\r':
        case '\t': return NULL;

        case '/':
            if (match_character(lexer, '/')) {
                // Peek at next character, so comments are added to line count
                while (peek_character(lexer) != '\n' && !is_finished(lexer)){
                    next_character(lexer);
                };
                return NULL;

            } else {
                token_type = SLASH;
            };
            break;

        case '{': token_type = LEFT_PAREN; break;
        case '}': token_type = RIGHT_PAREN; break;
        case '(': token_type = LEFT_BRACE; break;
        case ')': token_type = RIGHT_BRACE; break;
        case '[': token_type = LEFT_BRACKET; break;
        case ']': token_type = RIGHT_BRACKET; break;

        case '!':
            token_type = BANG;
            token_type = match_character(lexer, '=') ? BANG_EQUAL : token_type;
            break;

        case '=':
            token_type = EQUAL;
            token_type = match_character(lexer, '=') ? EQUAL_EQUAL : token_type;
            break;

        case '<':
            token_type = LESS;
            token_type = match_character(lexer, '=') ? LESS_EQUAL : token_type;
            break;

        case '>':
            token_type = GREATER;
            token_type = match_character(lexer, '=') ? GREATER_EQUAL : token_type;
            break;

        case '+': token_type = PLUS; break;
        case '-': token_type = MINUS; break;
        case '*': token_type = STAR; break;

        case '.': token_type = DOT; break;
        case ',': token_type = COMMA; break;
        case ':': token_type = COLON; break;
        case ';': token_type = SEMICOLON; break;

        case '\'':
            token_type = STRING;
            literal = scan_string(lexer, true);
            break;

        case '"':
            token_type = STRING;
            literal = scan_string(lexer, false);
            break;

        default:
            if (is_digit(character)){
                token_type = NUMBER;
                literal = scan_number(lexer);
            } else {
                // TODO: Raise error
                return NULL;
            };
    };

    // TODO: Add chracter analysis to determine what token to create
    return add_next_token(lexer, token_type, literal);
};


Token *scan_tokens(Lexer *lexer){
    Token *token = NULL;
    Token *first_token = NULL;
    Token *prev_token = NULL;

    while(!is_finished(lexer)){
        lexer->start = lexer->current;
        token = scan_token(lexer);

        if(token == NULL){
            token = prev_token;
            continue;
        };

        if (prev_token == NULL){
            first_token = token;
        } else {
            prev_token->next_token = token;
        };

        prev_token = token;
    };

    prev_token = token = NULL;
    return first_token;
};


void reset_lexer(Lexer *lexer){
    memset(lexer, 0, sizeof *lexer);
    lexer->line = 1;
    lexer->source = NULL;
};
