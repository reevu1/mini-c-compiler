#include "print_ast.h"
#include <stdio.h>

/*
 * Print indentation (2 spaces per level)
 */
static void print_indent(int indent) {
    for (int i = 0; i < indent; i++) {
        printf("  ");
    }
}

/*
 * Recursively print AST nodes
 */
void ast_print(ASTNode *node, int indent) {
    if (!node) return;

    print_indent(indent);

    switch (node->kind) {

        case AST_INT_LITERAL:
            printf("INT %d\n", node->int_value);
            break;

        case AST_IDENTIFIER:
            printf("IDENT %s\n", node->identifier);
            break;

        case AST_BINARY_EXPR:
            printf("BINARY %c\n", node->binary.op);
            ast_print(node->binary.left, indent + 1);
            ast_print(node->binary.right, indent + 1);
            break;

        case AST_ASSIGN_STMT:
            printf("ASSIGN\n");
            print_indent(indent + 1);
            printf("IDENT %s\n", node->assign.identifier);
            ast_print(node->assign.value, indent + 1);
            break;

        default:
            printf("UNKNOWN NODE\n");
            break;
    }
}
