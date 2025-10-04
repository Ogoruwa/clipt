#include "lexer.h"


bool is_finished(Lexer* lexer) {
    return lexer->current >= lexer->slen;
};


bool match_character(Lexer* lexer, char expected) {
    if (is_finished(lexer)) {
        return false;
    };

    if (lexer->source[lexer->current] == expected) {
        lexer->current++;
        return true;
    };

    return false;
};


char peek_character(Lexer* lexer) {
    if (is_finished(lexer)) {
        return '\0';
    };
    return lexer->source[lexer->current];
};


char peek_next_character(Lexer* lexer) {
    if (lexer->current + 1 >= lexer->slen) {
        return '\0';
    };
    return lexer->source[lexer->current + 1];
};


char next_character(Lexer* lexer) {
    if (is_finished(lexer)) {
        return '\0';
    };
    return lexer->source[lexer->current++];
};


Token* add_next_token(Lexer* lexer, TokenType token_type, void* literal) {
    Token* token =
        create_token(token_type, &(lexer->source[lexer->start]), lexer->current - lexer->start, literal, lexer->line);

    lexer->start = lexer->current;

    return token;
};


void scan_comment(Lexer* lexer) {
    // Peek at next character, so new line is detected and comments are added to line count
    while (peek_character(lexer) != '\n' && !is_finished(lexer)) {
        next_character(lexer);
    };
};


char* scan_string(Lexer* lexer, bool single) {
    uint64_t size = 0;
    char* literal = NULL;
    char quote = single ? '\'' : '"';

    while (!is_finished(lexer) && peek_character(lexer) != quote) {
        if (peek_character(lexer) == '\n') {
            lexer->line++;
        };
        next_character(lexer);
    };

    // If source has been completely scanned, string was not terminated
    // The above loop is broken only if the source has been scanned or the next character is the terminator
    if (is_finished(lexer)) {
        lexer->raise_error(lexer->master, &CAST_TO_ERROR_INFO(lexer, SyntaxError));
        return NULL;
    };

    next_character(lexer);
    // -1 and +1 to ignore the quotes
    size = (lexer->current - 1) - (lexer->start + 1) + 1;

    literal = malloc(size);
    memcheck(literal);

    memset(literal, '\0', size);
    strncpy(literal, &(lexer->source[lexer->start + 1]), --size);

    return literal;
};


double* scan_number(Lexer* lexer) {
    uint64_t size;
    char* string = NULL;
    char* remainder = NULL;
    double* literal = NULL;


    while (is_digit(peek_character(lexer))) {
        next_character(lexer);
    };

    if (peek_character(lexer) == '.' && is_digit(peek_next_character(lexer))) {
        next_character(lexer);
        while (is_digit(peek_character(lexer))) {
            next_character(lexer);
        };
    };

    if (!is_finished(lexer) && !is_whitespace(peek_character(lexer))) {
        lexer->raise_error(lexer->master, &CAST_TO_ERROR_INFO(lexer, SyntaxError));
        return NULL;
    };

    size = lexer->current - lexer->start + 1;
    string = malloc(size);
    memcheck(string);

    memset(string, '\0', size);
    strncpy(string, &(lexer->source[lexer->start]), --size);

    literal = malloc(sizeof(double));
    memcheck(literal);

    *literal = strtod(string, &remainder);
    free(string);

    return literal;
};


TokenType scan_identifier(Lexer* lexer) {
    uint64_t size = 0;
    char* lexeme = NULL;
    struct hashmap* map = NULL;
    const KeywordHash* hash = NULL;
    TokenType token_type = IDENTIFIER;

    while (is_alphanumeric(peek_character(lexer))) {
        next_character(lexer);
    };

    size = lexer->current - lexer->start + 1;
    lexeme = malloc(size);
    memcheck(lexeme);

    memset(lexeme, '\0', size);
    strncpy(lexeme, &(lexer->source[lexer->start]), --size);

    map = get_keyword_hashmap();
    hash = hashmap_get(map, &(KeywordHash){.lexeme = lexeme});
    token_type = hash ? hash->token_type : IDENTIFIER;

    free(lexeme);
    hash = NULL;
    lexeme = NULL;

    return token_type;
};


Token* scan_token(Lexer* lexer) {
    TokenType token_type;
    void* literal = NULL;
    char character = next_character(lexer);

    switch (character) {
        case '\n': lexer->line++;
        case ' ':
        case '\r':
        case '\t': return NULL;

        case '/':
            if (match_character(lexer, '/')) {
                scan_comment(lexer);
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
            RETURN_NULL_IF_NULL(literal);
            break;

        case '"':
            token_type = STRING;
            literal = scan_string(lexer, false);
            RETURN_NULL_IF_NULL(literal);
            break;

        default:
            if (is_digit(character)) {
                token_type = NUMBER;
                literal = scan_number(lexer);
                RETURN_NULL_IF_NULL(literal);

            } else if (is_alpha(character)) {
                token_type = scan_identifier(lexer);

            } else {
                lexer->raise_error(lexer->master, &CAST_TO_ERROR_INFO(lexer, SyntaxError));
                return NULL;
            };
    };

    return add_next_token(lexer, token_type, literal);
};


Token* scan_tokens(Lexer* lexer) {
    Token* token = NULL;
    Token* first_token = NULL;
    Token* prev_token = NULL;

    while (!is_finished(lexer)) {
        lexer->start = lexer->current;
        token = scan_token(lexer);

        if (token == NULL) {
            continue;
        };

        if (prev_token == NULL) {
            first_token = token;
        } else {
            prev_token->next_token = token;
        };

        prev_token = token;
    };

    prev_token = token = NULL;
    return first_token;
};


void reset_lexer(Lexer* lexer) {
    lexer->start = 0;
    lexer->current = 0;
    lexer->slen = 0;
    lexer->source = NULL;
};


Lexer* new_lexer(const char* source, uint64_t slen, error_handler err_handler, void* master) {
    assert(err_handler != NULL);

    Lexer* lexer = (Lexer*)malloc(sizeof(Lexer));
    if (lexer == NULL) {
        perror("Failed to allocate memory for lexer");
        oom();
    };

    reset_lexer(lexer);
    lexer->line = 1;
    lexer->slen = slen;
    lexer->source = source;
    lexer->raise_error = err_handler;
    lexer->master = master;

    return lexer;
};


void free_lexer(Lexer* lexer) {
    free(lexer);
};
