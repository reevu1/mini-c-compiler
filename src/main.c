#include "lexer/lexer.h"
#include "parser/parser.h"
#include "ast/print_ast.h"
#include "semantic/semantic.h"

int main(void) {
    lexer_init("x = 10 + 20;");
    ASTNode *tree = parse_statement();

    ast_print(tree, 0);

    semantic_analyze(tree);

    printf("Semantic analysis passed!\n");
    return 0;
}
