#ifndef TOKEN_H
#define TOKEN_H

/* Include */

#include <stdlib.h>

/* Type Definitions */

enum tok_type
{
    TOKEN_NONE,
    TOKEN_WORD,
    TOKEN_SQ_WORD,
    TOKEN_EOF,
};

struct token
{
    const char *val;
    enum tok_type type;
    struct token *next;
};

/* Function Definitions */

char *tok_copy_val(const char *val, const size_t start, const size_t end);

struct token *tok_create(const char *val, const enum tok_type type);

void tok_append(struct token **tokens, const char *val, const enum tok_type type);

char *tok_to_string(const enum tok_type token);

#endif