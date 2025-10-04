#include "error.h"


Error* new_error(ErrorInfo* info, char* message) {
    Error* err;

    err = malloc(sizeof(Error));
    memcheck(err);

    err->start = info->start;
    err->end = info->end;
    err->line = info->line;
    err->error_type = info->error_type;
    err->source = info->source;
    err->message = message;

    return err;
};


bool errorcmp(Error* a, Error* b) {
    assert(a != NULL && b != NULL);

    return (a->start == b->start) && (a->end == b->end) && (a->line == b->line) && (a->error_type == b->error_type) &&
           (strcmp(a->message, b->message) == 0) && (a->source == b->source);
};


const char* get_error_name(ErrorType error_type) {
    const char* names[NO_OF_ERRORS] = {
        [NoError] = "NoError",
        [Exception] = "Exception",
        [SyntaxError] = "SyntaxError",
        [FileNotFoundError] = "FileNotFoundError",
        [ZeroDivisionError] = "ZeroDivisionError"
    };

    if (error_type < NO_OF_ERRORS && error_type >= 0) {
        return names[error_type];
    };

    return NULL;
};


char* format_error(Error* err) {
    char* text;
    const char* format = "\n[line %" PRIu64 ", %" PRIu64 ", %" PRIu64 ", %s]: %s\n";
    const char* name = get_error_name(err->error_type);

    size_t size = snprintf(NULL, 0, format, err->line, err->start, err->end, name, err->message) + 1;
    text = malloc(size);
    memcheck(text);
    (void)snprintf(text, size, format, err->line, err->start, err->end, name, err->message);

    return text;
};


void report_error(Error* err) {
    char* text = format_error(err);

    printf(text);
    free(text);
};


void free_error(Error* err) {
    free(err->message);
    free(err);
};


void handle_new_error(ErrorInfo* info) {
    Error* err;
    char* message = get_error_message(info);

    err = new_error(info, message);

    report_error(err);
    free_error(err);
};


char* get_error_message(ErrorInfo* info) {
    // TODO: Return detailed message about error, depending on the error type
    char* temp_message = "A grave error occured";
    char* message = calloc(strlen(temp_message) + 1, sizeof(char));

    strncpy(message, temp_message, strlen(temp_message));

    return message;
};
