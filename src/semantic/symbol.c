#include "symbol.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static Symbol *symbol_table = NULL;

void symbol_init(void) {
    symbol_table = NULL;
}

int symbol_exists(const char *name) {
    Symbol *curr = symbol_table;
    while (curr) {
        if (strcmp(curr->name, name) == 0)
            return 1;
        curr = curr->next;
    }
    return 0;
}

void symbol_add(const char *name) {
    if (symbol_exists(name)) {
        fprintf(stderr, "Semantic error: redeclaration of '%s'\n", name);
        exit(1);
    }

    Symbol *sym = malloc(sizeof(Symbol));
    sym->name = strdup(name);
    sym->next = symbol_table;
    symbol_table = sym;
}
