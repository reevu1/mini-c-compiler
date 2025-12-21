#include "lexer/lexer.h"
#include "parser/parser.h"
#include <stdio.h>

int main(void) {
    lexer_init("x = 10 + 20;");
    ASTNode *tree = parse_statement();
    printf("Parsed successfully!\n");
    return 0;
}
