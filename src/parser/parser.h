#ifndef PARSER_H
#define PARSER_H

#include "ast/ast.h"

/*
 * Parse a single statement and return its AST
 */
ASTNode *parse_statement(void);

ASTNode *parse_program(void);


#endif // PARSER_H
