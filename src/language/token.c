#include "token.h"


const char* get_token_type_name(TokenType token_type) {
    const char* names[NO_OF_TOKENS] = {
        [LEFT_PAREN] = "LEFT_PAREN",
        [RIGHT_PAREN] = "RIGHT_PAREN",
        [LEFT_BRACE] = "LEFT_BRACE",
        [RIGHT_BRACE] = "RIGHT_BRACE",
        [LEFT_BRACKET] = "LEFT_BRACKET",
        [RIGHT_BRACKET] = "RIGHT_BRACKET",
        [COMMA] = "COMMA",
        [DOT] = "DOT",
        [SEMICOLON] = "SEMICOLON",
        [COLON] = "COLON",
        [MINUS] = "MINUS",
        [PLUS] = "PLUS",
        [SLASH] = "SLASH",
        [STAR] = "STAR",
        [AND] = "AND",
        [OR] = "OR",
        [BANG] = "BANG",
        [BANG_EQUAL] = "BANG_EQUAL",
        [EQUAL] = "EQUAL",
        [EQUAL_EQUAL] = "EQUAL_EQUAL",
        [GREATER] = "GREATER",
        [GREATER_EQUAL] = "GREATER_EQUAL",
        [LESS] = "LESS",
        [LESS_EQUAL] = "LESS_EQUAL",
        [NIL] = "NIL",
        [FALSE] = "FALSE",
        [TRUE] = "TRUE",
        [IDENTIFIER] = "IDENTIFIER",
        [STRING] = "STRING",
        [NUMBER] = "NUMBER",
        [FOR] = "FOR",
        [WHILE] = "WHILE",
        [IF] = "IF",
        [ELSE] = "ELSE",
        [ELIF] = "ELIF",
        [CONTINUE] = "CONTINUE",
        [BREAK] = "BREAK",
        [RETURN] = "RETURN",
        [FN] = "FN",
        [CLASS] = "CLASS",
        [SUPER] = "SUPER",
        [SELF] = "SELF",
        [PRINT] = "PRINT",
    };

    if (token_type < NO_OF_TOKENS && token_type >= 0) {
        return names[token_type];
    };

    return NULL;
};


bool tokencmp(Token* a, Token* b) {
    bool literal;

    if ((a->token_type != b->token_type) || (strcmp(a->lexeme, b->lexeme) != 0)) {
        return false;
    };

    if ((a->literal == NULL) || (b->literal == NULL)) {
        literal = (a->literal == NULL) && (b->literal == NULL);
    } else {
        switch (a->token_type) {
            case (STRING): literal = strcmp((char*)a->literal, (char*)b->literal) == 0; break;

            case (NUMBER): literal = (*(double*)a->literal) == (*(double*)b->literal); break;

            default: literal = true; break;
        }
    };

    return literal;
};


Token* create_token(TokenType token_type, const char* lexeme, uint64_t lexeme_size, void* literal, uint64_t line) {
    Token* token = malloc(sizeof(Token));
    memcheck(token);

    token->lexeme = calloc(lexeme_size + 1, sizeof(char));
    strncpy(token->lexeme, lexeme, lexeme_size);

    token->token_type = token_type;
    token->line = line;
    token->next_token = NULL;
    token->literal = literal;

    return token;
};


void free_tokens(Token* token) {
    Token* t = NULL;

    while (token != NULL) {
        t = token->next_token;

        if (token->literal != NULL) {
            free(token->literal);
            token->literal = NULL;
        };

        free(token->lexeme);
        token->lexeme = NULL;

        free(token);
        token = t;
    };
};


void print_token(Token* token) {
    char* info = "";
    const char* token_name = get_token_type_name(token->token_type);
    assert(token_name != NULL);

    if (token->token_type == STRING) {
        info = token->literal;

    } else if (token->token_type == NUMBER) {
        double value = *((double*)token->literal);
        size_t size = snprintf(NULL, 0, "%f", value);
        info = malloc(size++);

        memset(info, '\0', size);
        snprintf(info, size, "%f", value);

    } else {
        printf("%s", token_name);
        return;
    };

    printf("%s(%s)", token_name, info);

    if (token->token_type == NUMBER) {
        free(info);
        info = NULL;
    };
};


uint64_t keyword_hash(const void* item, uint64_t seed0, uint64_t seed1) {
    const KeywordHash* hash = item;
    uint64_t hash_value = hashmap_xxhash3(hash->lexeme, strlen(hash->lexeme), seed0, seed1);
    return hash_value;
};


int keyword_hash_compare(const void* a, const void* b, void* udata) {
    const KeywordHash* hash_a = a;
    const KeywordHash* hash_b = b;
    return strcmp(hash_a->lexeme, hash_b->lexeme);
};


void initialize_keyword_hashmap(struct hashmap* map) {
    hashmap_set(map, &(KeywordHash){AND, "and"});
    hashmap_set(map, &(KeywordHash){OR, "or"});
    hashmap_set(map, &(KeywordHash){FALSE, "false"});
    hashmap_set(map, &(KeywordHash){TRUE, "true"});
    hashmap_set(map, &(KeywordHash){NIL, "nil"});

    hashmap_set(map, &(KeywordHash){IF, "if"});
    hashmap_set(map, &(KeywordHash){ELSE, "else"});
    hashmap_set(map, &(KeywordHash){ELIF, "elif"});

    hashmap_set(map, &(KeywordHash){FOR, "for"});
    hashmap_set(map, &(KeywordHash){WHILE, "while"});
    hashmap_set(map, &(KeywordHash){BREAK, "break"});
    hashmap_set(map, &(KeywordHash){CONTINUE, "continue"});
    hashmap_set(map, &(KeywordHash){RETURN, "return"});

    hashmap_set(map, &(KeywordHash){FN, "fn"});
    hashmap_set(map, &(KeywordHash){CLASS, "class"});
    hashmap_set(map, &(KeywordHash){SUPER, "super"});
    hashmap_set(map, &(KeywordHash){SELF, "self"});
};


struct hashmap* get_keyword_hashmap() {
    static struct hashmap* map = NULL;

    if (map == NULL) {
        struct hashmap* temp =
            hashmap_new(sizeof(KeywordHash), 0, 0, 0, keyword_hash, keyword_hash_compare, NULL, NULL);

        map = temp;
        temp = NULL;

        initialize_keyword_hashmap(map);
    };

    return map;
};
