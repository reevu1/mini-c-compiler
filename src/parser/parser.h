#ifndef PARSER_H
#define PARSER_H

#include "ast/ast.h"
#include "lexer/lexer.h"

/*
 * Initialize LL(1) parsing table
 */
void parser_init(void);

/*
 * Parse a complete program using
 * non-recursive predictive parsing
 */
ASTNode *parse_program(void);

/*
 * Parse a single statement
 * (e.g., id = expression ;)
 */
ASTNode *parse_statement(void);

/*
 * Parse arithmetic / logical expressions
 */
ASTNode *parse_expression(void);

/*
 * Print parsing steps (stack, input, action)
 * Used for assignment demonstration
 */
void parser_trace(int enable);

/*
 * Error recovery using SYNCH
 */
void parser_error_recovery(void);

#endif // PARSER_H