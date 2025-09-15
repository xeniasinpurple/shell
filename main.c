#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "lexer.h"

int main(int argc, char **argv)
{
    const char *val = "echo 'Hello, world!'";
    struct lexer lexer = lexer_create(val);

    lex(&lexer);

    lexer_print(&lexer);

    return(0);
}