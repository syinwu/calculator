#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <calculator.h>

static unsigned symhash(char *sym)
{
    unsigned int hash = 0;
    unsigned c;

    while (c = *sym++)
    {
        hash = hash * 9 ^ c;
    }
    return hash;
}

struct symbol *lookup(char *sym)
{
    struct symbol *sp = &symtab[symhash(sym) % NHASH];
    int scount = NHASH;

    while (--scount >= 0)
    {
        if (sp->name && !strcmp(sp->name, sym))
        {
            return sp;
        }

        if (!sp->name)
        {
            sp->name = strdup(sym);
            sp->value = 0;
            sp->func = NULL;
            sp->syms = NULL;
            return sp;
        }

        if (++sp >= symtab + NHASH)
        {
            sp = symtab;
        }
    }

    yyerror("symbol table overflow\n");
    abort();
}