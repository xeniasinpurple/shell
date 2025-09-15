#include "lex.h"

void lex_words(const char *data)
{
    struct token tokens[1024];
    size_t token_cnt = 0;
    size_t token_length = 0;
    enum tstate state = STATE_START;
    for(int i = 0; data[i] != '\0'; i++)
    {
        char c = data[i];
        switch(state)
        {
            case(STATE_START):
            {
                if(isspace(c))
                {
                    state = STATE_BLANK;
                }
                else if(c == '\'')
                {
                    state = STATE_SINGLE_QUOTE;
                }
                else if(isprint(c))
                {
                    state = STATE_GENERAL;
                    tokens[token_cnt].data[token_length++] = c; 
                }
                break;
            }
            case(STATE_SINGLE_QUOTE):
            {
                if(c == '\'')
                {
                    tokens[token_cnt].data[token_length++] = ' ';
                }
                else if(isspace(c))
                {
                    state = STATE_BLANK;
                    token_cnt++;
                }                else
                {
                    state = STATE_SINGLE_QUOTE_WORD;
                    tokens[token_cnt].data[token_length++] = c;
                }
                break;
            }
            case(STATE_SINGLE_QUOTE_WORD):
            {
                if(c == '\'')
                {
                    state = STATE_SINGLE_QUOTE;
                }
                else
                {
                    tokens[token_cnt].data[token_length++] = c;
                }
                break;
            }
            case(STATE_GENERAL):
            {
                if(isspace(c))
                {
                    state = STATE_BLANK;
                    token_cnt++;
                    token_length = 0;
                }
                else
                {
                    tokens[token_cnt].data[token_length++] = c; 
                }
                break;
            }
            case(STATE_BLANK):
            {
                if(c == '\'')
                {
                    state = STATE_SINGLE_QUOTE;
                }
                else if(isprint(c))
                {
                    state = STATE_GENERAL;
                    tokens[token_cnt].data[token_length++] = c;
                }
                break;
            }
            default:
            {
                printf("Undefined Case at position %d.\n", i);
                break;
            }
        }
    }
    state = STATE_END;

    for(int i = 0; i <= token_cnt; i++)
    {
        printf("Token %d: %s\n", i + 1, tokens[i].data);
    }
}