#ifndef LEXER_H
#define LEXER_H

/* Includes */

#include <stdlib.h>

/* Type Definitions */

enum lex_state
{
    STATE_START,
    STATE_BLANK,
    STATE_REGULAR,
    STATE_SQ,
    STATE_SQ_WORD,
    STATE_END,
};

struct lexer
{
    const char *val;
    const size_t len;
    enum lex_state state;
    size_t tok_start, tok_end;
    struct token *tokens;
};

/* Functions Definitons */

struct lexer lexer_create(const char *val);

void lexer_print(const struct lexer *lexer);

void lex(struct lexer *lexer);

#endif