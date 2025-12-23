#include "lexer/lexer.h"
#include "parser/parser.h"
#include "semantic/semantic.h"
#include "codegen/codegen.h"

int main(void) {
    lexer_init("x = 10 + 20 * 3;");
    ASTNode *tree = parse_statement();

    semantic_analyze(tree);
    codegen(tree);     // prints IR only

    return 0;
}
