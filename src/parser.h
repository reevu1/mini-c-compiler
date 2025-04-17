#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

typedef enum {
    AST_FUNCTION,
    AST_RETURN
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;

    union {
        struct {
            char* return_type;
            char* name;
            struct ASTNode* body;
        } function;

        struct {
            char* value;
        } return_stmt;
    };
} ASTNode;

ASTNode* parse(const Token* tokens, int token_count);
void print_ast(const ASTNode* node);
void free_ast(ASTNode* node);

#endif
