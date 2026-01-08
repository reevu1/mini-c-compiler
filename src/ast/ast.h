#ifndef AST_H
#define AST_H

#include <stdlib.h>

/*
 * AST node kinds
 * Each value represents a different syntactic construct
 */
typedef enum {
    AST_INT_LITERAL,
    AST_IDENTIFIER,
    AST_BINARY_EXPR,
    AST_ASSIGN_STMT,
    AST_BLOCK            
} ASTKind;


/*
 * Forward declaration
 */
typedef struct ASTNode ASTNode;

/*
 * AST node structure
 */
typedef struct ASTNode {
    ASTKind kind;
    union {
        int int_value;
        char *identifier;

        struct {
            char op;
            struct ASTNode *left;
            struct ASTNode *right;
        } binary;

        struct {
            char *identifier;
            struct ASTNode *value;
        } assign;

        struct {
            struct ASTNode **statements;
            int count;
        } block;          
    };
} ASTNode;


/*
 * AST node constructor functions
 */
ASTNode *ast_int_literal(int value);
ASTNode *ast_identifier(char *name);
ASTNode *ast_binary(ASTNode *left, char op, ASTNode *right);
ASTNode *ast_assign(char *name, ASTNode *value);

/* Block (multiple statements) */
ASTNode *ast_make_block(void);
void ast_block_add(ASTNode *block, ASTNode *stmt);

#endif // AST_H
