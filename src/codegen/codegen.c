#include "codegen.h"
#include <stdio.h>

/*
 * Internal recursive code generator
 */
static void gen_node(ASTNode *node);

void codegen(ASTNode *node) {
    gen_node(node);
}

/*
 * Generate code by walking the AST
 */
static void gen_node(ASTNode *node) {
    if (!node) return;

    switch (node->kind) {

        case AST_INT_LITERAL:
            /*
             * Push integer literal onto stack
             */
            printf("PUSH %d\n", node->int_value);
            break;

        case AST_IDENTIFIER:
            /*
             * Load variable value onto stack
             */
            printf("LOAD %s\n", node->identifier);
            break;

        case AST_BINARY_EXPR:
            /*
             * Evaluate left, then right, then apply operator
             */
            gen_node(node->binary.left);
            gen_node(node->binary.right);

            switch (node->binary.op) {
                case '+': printf("ADD\n"); break;
                case '-': printf("SUB\n"); break;
                case '*': printf("MUL\n"); break;
                case '/': printf("DIV\n"); break;
            }
            break;

        case AST_ASSIGN_STMT:
            /*
             * Generate RHS value, then store in variable
             */
            gen_node(node->assign.value);
            printf("STORE %s\n", node->assign.identifier);
            break;

        case AST_BLOCK:
            for (int i = 0; i < node->block.count; i++) {
                gen_node(node->block.statements[i]);
            }
            break;

        default:
            break;
    }
}
