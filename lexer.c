#include "lexer.h"

/* Includes */

#include "token.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Functions Definitons */

struct lexer lexer_create(const char *val)
{
    return((struct lexer){.val = val, .len = strlen(val), .state = STATE_START, .tok_start = 0, .tok_end = 1, .tokens = NULL});
}

void lexer_print(const struct lexer *lexer)
{
    struct token *tmp = lexer->tokens;
    while(tmp != NULL)
    {
        printf("(%s, %s)\n", tmp->val, tok_to_string(tmp->type));
        tmp = tmp->next;
    }
}

void lex(struct lexer *lexer)
{
    char ch;
    for(int i = 0; i <= lexer->len; i++)
    {
        ch = lexer->val[i];
        switch (lexer->state)
        {
            case(STATE_START):
            {
                if(ch == '\'')
                {
                    lexer->state = STATE_SQ;
                }
                else if(isalnum(ch))
                {
                    lexer->tok_start = i;

                    lexer->state = STATE_REGULAR;
                }
                else if(isspace(ch))
                {
                    lexer->state = STATE_BLANK;
                }
                break;
            }
            case(STATE_BLANK):
            {
                if(ch == '\'')
                {
                    lexer->state = STATE_SQ;
                }
                else if(isalnum(ch))
                {
                    lexer->tok_start = i;

                    lexer->state = STATE_REGULAR; 
                }
                break;
            }
            case(STATE_REGULAR):
            {
                if(ch == '\0')
                {
                    lexer->tok_end = i;

                    tok_append(&lexer->tokens, tok_copy_val(lexer->val, lexer->tok_start, lexer->tok_end), TOKEN_WORD);
                }
                else if(isspace(ch))
                {
                    lexer->tok_end = i;
                    tok_append(&lexer->tokens, tok_copy_val(lexer->val, lexer->tok_start, lexer->tok_end), TOKEN_WORD);

                    lexer->state = STATE_BLANK;
                } 
                break;
            }
            case(STATE_SQ):
            {
                if(isalnum(ch))
                {
                    lexer->tok_start = i;

                    lexer->state = STATE_SQ_WORD;
                }
                else if(isspace(ch))
                {
                    lexer->state = STATE_BLANK;
                }
                break;
            }
            case(STATE_SQ_WORD):
            {
                if(ch == '\'')
                {
                    lexer->tok_end = i;
                    tok_append(&lexer->tokens, tok_copy_val(lexer->val, lexer->tok_start, lexer->tok_end), TOKEN_SQ_WORD);

                    lexer->state = STATE_SQ;
                }
                break;
            }
            default:
            {
                break;
            }
        }
    }
    lexer->state = STATE_END;
    tok_append(&lexer->tokens, "\0", TOKEN_EOF);
}