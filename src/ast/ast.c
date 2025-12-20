#include "ast.h"
#include <stdlib.h>
#include <string.h>

/*
 * Allocate and initialize a generic AST node
 */
static ASTNode *alloc_node(ASTKind kind) {
    ASTNode *node = (ASTNode *)malloc(sizeof(ASTNode));
    if (!node) {
        return NULL; // out of memory (can improve later)
    }
    node->kind = kind;
    return node;
}

/*
 * Integer literal node
 * Example: 10
 */
ASTNode *ast_int_literal(int value) {
    ASTNode *node = alloc_node(AST_INT_LITERAL);
    if (!node) return NULL;

    node->int_value = value;
    return node;
}

/*
 * Identifier node
 * Example: x
 */
ASTNode *ast_identifier(char *name) {
    ASTNode *node = alloc_node(AST_IDENTIFIER);
    if (!node) return NULL;

    node->identifier = strdup(name);  // copy identifier name
    return node;
}

/*
 * Binary expression node
 * Example: a + b
 */
ASTNode *ast_binary(ASTNode *left, char op, ASTNode *right) {
    ASTNode *node = alloc_node(AST_BINARY_EXPR);
    if (!node) return NULL;

    node->binary.left = left;
    node->binary.right = right;
    node->binary.op = op;
    return node;
}

/*
 * Assignment statement node
 * Example: x = expr;
 */
ASTNode *ast_assign(char *name, ASTNode *value) {
    ASTNode *node = alloc_node(AST_ASSIGN_STMT);
    if (!node) return NULL;

    node->assign.identifier = strdup(name); // copy variable name
    node->assign.value = value;
    return node;
}
