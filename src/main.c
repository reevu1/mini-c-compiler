#include "lexer/lexer.h"
#include "parser/parser.h"
#include "ast/print_ast.h"
#include "semantic/semantic.h"
#include "codegen/codegen.h"
#include <stdio.h>

int main(void) {
    lexer_init("x = 10 + 20 * 3;");
    ASTNode *tree = parse_statement();

    printf("=== AST ===\n");
    ast_print(tree, 0);

    semantic_analyze(tree);

    printf("\n=== CODEGEN ===\n");
    codegen(tree);

    return 0;
}
