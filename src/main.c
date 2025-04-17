#include <stdio.h>
#include "lexer.h"
#include "parser.h"

int main() {
    const char* source = "int main() { return 42; }";
    Token tokens[100];
    int index = 0;
    int token_count = 0;

    // Lex all tokens
    while (1) {
        Token token = get_next_token(source, &index);
        tokens[token_count++] = token;
        if (token.type == TOKEN_EOF) break;
    }

    // Parse
    ASTNode* ast = parse(tokens, token_count);
    print_ast(ast);

    // Clean up
    for (int i = 0; i < token_count; i++) {
        free_token(tokens[i]);
    }
    free_ast(ast);

    return 0;
}
