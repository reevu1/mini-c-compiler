#include "parser.h"
#include "lexer/lexer.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Current token the parser is looking at
 */
static Token current;

/*
 * Advance to next token
 */
static void advance(void) {
    current = lexer_next_token();
}

/*
 * Ensure current token is of expected type
 */
static void expect(TokenType type) {
    if (current.type != type) {
        fprintf(stderr,
                "Parser error at line %d: expected token %d, got %d\n",
                current.line, type, current.type);
        exit(1);
    }
    advance();
}

/*
 * Forward declarations (because of recursion)
 */
static ASTNode *parse_expr(void);
static ASTNode *parse_term(void);
static ASTNode *parse_factor(void);

/*
 * factor → NUMBER | IDENT | '(' expr ')'
 */
static ASTNode *parse_factor(void) {
    ASTNode *node = NULL;

    if (current.type == TOK_NUMBER) {
        int value = atoi(current.lexeme);
        node = ast_int_literal(value);
        advance();
        return node;
    }

    if (current.type == TOK_IDENT) {
        node = ast_identifier(current.lexeme);
        advance();
        return node;
    }

    if (current.type == TOK_LPAREN) {
        advance();                 // consume '('
        node = parse_expr();
        expect(TOK_RPAREN);        // consume ')'
        return node;
    }

    fprintf(stderr,
            "Parser error at line %d: unexpected token '%s'\n",
            current.line, current.lexeme);
    exit(1);
}

/*
 * term → factor ((* | /) factor)*
 */
static ASTNode *parse_term(void) {
    ASTNode *node = parse_factor();

    while (current.type == TOK_STAR || current.type == TOK_SLASH) {
        char op = current.lexeme[0];
        advance();
        ASTNode *right = parse_factor();
        node = ast_binary(node, op, right);
    }

    return node;
}

/*
 * expr → term ((+ | -) term)*
 */
static ASTNode *parse_expr(void) {
    ASTNode *node = parse_term();

    while (current.type == TOK_PLUS || current.type == TOK_MINUS) {
        char op = current.lexeme[0];
        advance();
        ASTNode *right = parse_term();
        node = ast_binary(node, op, right);
    }

    return node;
}

/*
 * stmt → IDENT '=' expr ';'
 */
ASTNode *parse_statement(void) {
    advance(); // load first token

    if (current.type != TOK_IDENT) {
        fprintf(stderr,
                "Parser error at line %d: expected identifier\n",
                current.line);
        exit(1);
    }

    char *name = current.lexeme;
    advance();

    expect(TOK_ASSIGN);

    ASTNode *value = parse_expr();

    expect(TOK_SEMI);

    return ast_assign(name, value);
}
