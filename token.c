#include "token.h"

/* Includes */

#include <string.h>

/* Functions Definitons */

char *tok_copy_val(const char *val, const size_t start, const size_t end)
{
    char *tmp = (char *)malloc((end - start) + 1);
    strncpy(tmp, val + start, (end - start));
    tmp[(end - start)] = '\0';

    return(tmp);
}

struct token *tok_create(const char *val, const enum tok_type type)
{
    struct token *tok = (struct token *)malloc(sizeof(struct token));

    if(!tok) return(NULL);

    tok->val = val;
    tok->type = type;
    tok->next = NULL;

    return(tok);
}

void tok_append(struct token **tokens, const char *val, const enum tok_type type)
{
    if(!*tokens) *tokens = tok_create(val, type);
    else
    {
        struct token *tmp = *tokens;
        while(tmp->next != NULL) tmp = tmp->next;

        tmp->next = tok_create(val, type);
    }
}

char *tok_to_string(const enum tok_type token)
{
    switch (token)
    {
    case (TOKEN_EOF):
        return("TOK_EOF");
    case (TOKEN_WORD):
        return("TOK_WORD");
    case (TOKEN_SQ_WORD):
        return("TOK_SQ_WORD");
    default:
        return("TOK_NONE");
    }
}
