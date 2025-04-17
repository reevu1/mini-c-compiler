#include <stdio.h>
#include "lexer.h"

int main() {
    const char* source = "int main() { return 42; }";
    int index = 0;
    Token token;

    printf("Lexing: %s\n", source);
    do {
        token = get_next_token(source, &index);
        printf("Token: %-15s Lexeme: '%s'\n", token_type_to_string(token.type), token.lexeme);
        free_token(token);
    } while (token.type != TOKEN_EOF);

    return 0;
}
