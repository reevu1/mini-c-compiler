#include "semantic.h"
#include "symbol.h"
#include <stdio.h>
#include <stdlib.h>

static void analyze_node(ASTNode *node);

void semantic_analyze(ASTNode *node) {
    symbol_init();
    analyze_node(node);
}

/*
 * Recursive AST walk
 */
static void analyze_node(ASTNode *node) {
    if (!node) return;

    switch (node->kind) {

        case AST_ASSIGN_STMT:
            // variable is declared on first assignment
            if (!symbol_exists(node->assign.identifier)) {
                symbol_add(node->assign.identifier);
            }

            analyze_node(node->assign.value);
            break;

        case AST_IDENTIFIER:
            if (!symbol_exists(node->identifier)) {
                fprintf(stderr,
                        "Semantic error: use of undeclared variable '%s'\n",
                        node->identifier);
                exit(1);
            }
            break;

        case AST_BINARY_EXPR:
            analyze_node(node->binary.left);
            analyze_node(node->binary.right);
            break;

        case AST_INT_LITERAL:
            // always valid
            break;

        case AST_BLOCK:
            for (int i = 0; i < node->block.count; i++) {
                analyze_node(node->block.statements[i]);
            }
            break;

        default:
            break;
    }
}
