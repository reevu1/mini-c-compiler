#ifndef AST_H
#define AST_H

#include <stdlib.h>

/*
 * AST node kinds
 * Each value represents a different syntactic construct
 */
typedef enum {
    AST_INT_LITERAL,     // e.g. 10
    AST_IDENTIFIER,      // e.g. x
    AST_BINARY_EXPR,     // e.g. a + b
    AST_ASSIGN_STMT      // e.g. x = expr;
} ASTKind;

/*
 * Forward declaration
 */
typedef struct ASTNode ASTNode;

/*
 * AST node structure
 */
struct ASTNode {
    ASTKind kind;

    union {
        // Integer literal
        int int_value;

        // Identifier
        char *identifier;

        // Binary expression
        struct {
            ASTNode *left;
            ASTNode *right;
            char op;   // '+', '-', '*', '/'
        } binary;

        // Assignment statement
        struct {
            char *identifier;
            ASTNode *value;
        } assign;
    };
};

/*
 * AST node constructor functions
 */
ASTNode *ast_int_literal(int value);
ASTNode *ast_identifier(char *name);
ASTNode *ast_binary(ASTNode *left, char op, ASTNode *right);
ASTNode *ast_assign(char *name, ASTNode *value);

#endif // AST_H
