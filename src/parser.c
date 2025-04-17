#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

static int current = 0;
static const Token* tokens_ref;

static const Token* peek() {
    return &tokens_ref[current];
}

static const Token* advance() {
    return &tokens_ref[current++];
}

static int match(TokenType type) {
    if (peek()->type == type) {
        advance();
        return 1;
    }
    return 0;
}

ASTNode* parse_function() {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = AST_FUNCTION;

    // Assume return type is 'int'
    const Token* ret_type = advance(); // int
    const Token* name = advance();     // main
    advance(); // (
    advance(); // )
    advance(); // {

    // Parse return statement
    advance(); // return
    const Token* val = advance(); // 42
    advance(); // ;
    advance(); // }

    // Fill AST
    ASTNode* return_node = malloc(sizeof(ASTNode));
    return_node->type = AST_RETURN;
    return_node->return_stmt.value = strdup(val->lexeme);

    node->function.return_type = strdup(ret_type->lexeme);
    node->function.name = strdup(name->lexeme);
    node->function.body = return_node;

    return node;
}

ASTNode* parse(const Token* tokens, int token_count) {
    tokens_ref = tokens;
    current = 0;
    return parse_function();
}

void print_ast(const ASTNode* node) {
    if (node->type == AST_FUNCTION) {
        printf("Function: %s returns %s\n", node->function.name, node->function.return_type);
        print_ast(node->function.body);
    } else if (node->type == AST_RETURN) {
        printf("  Return: %s\n", node->return_stmt.value);
    }
}

void free_ast(ASTNode* node) {
    if (!node) return;
    if (node->type == AST_FUNCTION) {
        free(node->function.return_type);
        free(node->function.name);
        free_ast(node->function.body);
    } else if (node->type == AST_RETURN) {
        free(node->return_stmt.value);
    }
    free(node);
}
