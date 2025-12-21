#include "lexer/lexer.h"
#include "parser/parser.h"
#include "ast/print_ast.h"

int main(void) {
    lexer_init("x = 10 + 20 * 3;");
    ASTNode *tree = parse_statement();

    ast_print(tree, 0);

    return 0;
}
