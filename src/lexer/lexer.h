#ifndef LEXER_H
#define LEXER_H

#include "token.h"

// Initialize lexer with source code
void lexer_init(const char *source);

// Get next token from input
Token lexer_next_token(void);

#endif // LEXER_H
