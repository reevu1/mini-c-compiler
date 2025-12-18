#include <stdio.h>
#include "lexer/lexer.h"

int main() {
    const char *code = "int x = 10 + 20;";
    lexer_init(code);

    Token t;
    do {
        t = lexer_next_token();
        printf("Token: %d, Lexeme: '%s', Line: %d\n", t.type, t.lexeme, t.line);
    } while (t.type != TOK_EOF);

    return 0;
}
