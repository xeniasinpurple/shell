#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "token.h"
#include "lexer.h"

struct argument
{
    const char *val;
    struct argument *next;
};

char const**create_args(struct token *tokens)
{
    size_t cnt = 0;
    struct token *tmp = tokens;

    while(tmp->type != TOKEN_EOF)
    {
        cnt++;
        tmp = tmp->next;
    }

    char const**args = malloc(cnt * sizeof(char *));

    tmp = tokens;
    for(int i = 0; i < cnt; i++)
    {
        args[i] = tmp->val;
        tmp = tmp->next;
    }

    return(args);
}

int main(int argc, char **argv)
{
    char val[255];
    fgets(val, sizeof(val), stdin);
    
    struct lexer lexer = lexer_create(val);

    lex(&lexer);

    char const **args = create_args(lexer.tokens);

    return(0);
}

/* 
    Create Child Process (with <unistd.h>)

    int pid = fork();
    char *cmd = "ls";
    char *args[] = {"ls", "-la", NULL};

    switch(pid)
    {
        case(-1):
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        case(0):
        {
            if(execvp(cmd, args) == -1)
            {
                perror("execvp error");
                exit(EXIT_FAILURE);
            }
            exit(EXIT_SUCCESS);
        }
        default:
        {
            printf("Parent existing.\n");
            exit(EXIT_SUCCESS);
        }
    }
*/