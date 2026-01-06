#include "lexer/lexer.h"
#include "parser/parser.h"
#include "semantic/semantic.h"
#include "codegen/codegen.h"

#include <stdio.h>
#include <stdlib.h>

/*
 * Read entire stdin into a buffer
 */
static char *read_stdin(void) {
    fseek(stdin, 0, SEEK_END);
    long size = ftell(stdin);
    rewind(stdin);

    char *buffer = malloc(size + 1);
    if (!buffer) return NULL;

    fread(buffer, 1, size, stdin);
    buffer[size] = '\0';
    return buffer;
}

int main(void) {
    char *source = read_stdin();
    if (!source) {
        fprintf(stderr, "Failed to read input\n");
        return 1;
    }

    lexer_init(source);

    ASTNode *tree = parse_statement();

    semantic_analyze(tree);

    codegen(tree);

    free(source);
    return 0;
}
