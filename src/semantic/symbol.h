#ifndef SYMBOL_H
#define SYMBOL_H

typedef struct Symbol {
    char *name;
    struct Symbol *next;
} Symbol;

/*
 * Symbol table API
 */
void symbol_init(void);
void symbol_add(const char *name);
int symbol_exists(const char *name);

#endif // SYMBOL_H
