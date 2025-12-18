#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    // Special
    TOK_EOF,
    TOK_ERROR,

    // Keywords
    TOK_INT,
    TOK_IF,
    TOK_ELSE,
    TOK_WHILE,

    // Identifiers and literals
    TOK_IDENT,
    TOK_NUMBER,

    // Operators
    TOK_PLUS,
    TOK_MINUS,
    TOK_STAR,
    TOK_SLASH,
    TOK_ASSIGN,

    // Symbols
    TOK_SEMI,
    TOK_LPAREN,
    TOK_RPAREN,
    TOK_LBRACE,
    TOK_RBRACE
} TokenType;

typedef struct {
    TokenType type;
    char *lexeme;   // actual text
    int line;       // line number
} Token;

#endif // TOKEN_H
