#ifndef CODEGEN_H
#define CODEGEN_H

#include "ast/ast.h"

/*
 * Generate stack-based code for a single AST statement
 */
void codegen(ASTNode *node);

#endif // CODEGEN_H
