#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "lexer.h"

struct argument
{
    const char *val;
    struct argument *next;
};

int main(int argc, char **argv)
{
    const char *val = "echo '\'Hello, world!\''";
    struct lexer lexer = lexer_create(val);

    lex(&lexer);

    lexer_print(&lexer);

    // Use execvp()

    return(0);
}