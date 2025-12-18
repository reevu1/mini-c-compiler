#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "lexer.h"

// Lexer state
static const char *src;
static int pos;
static int line;

// ---------- Helper Functions ----------

static char peek(void) {
    return src[pos];
}

static char advance(void) {
    char c = src[pos++];
    if (c == '\n') line++;
    return c;
}

static int is_alpha(char c) {
    return isalpha(c) || c == '_';
}

static int is_digit(char c) {
    return isdigit(c);
}

static void skip_whitespace(void) {
    while (peek() == ' ' || peek() == '\t' || peek() == '\n' || peek() == '\r') {
        advance();
    }
}

static Token make_token(TokenType type, const char *start, int length) {
    Token token;
    token.type = type;
    token.lexeme = (char *)malloc(length + 1);
    strncpy(token.lexeme, start, length);
    token.lexeme[length] = '\0';
    token.line = line;
    return token;
}

static Token error_token(const char *message) {
    Token token;
    token.type = TOK_ERROR;
    token.lexeme = strdup(message);
    token.line = line;
    return token;
}

// ---------- Keyword Check ----------

static TokenType keyword_type(const char *text) {
    if (strcmp(text, "int") == 0) return TOK_INT;
    if (strcmp(text, "if") == 0) return TOK_IF;
    if (strcmp(text, "else") == 0) return TOK_ELSE;
    if (strcmp(text, "while") == 0) return TOK_WHILE;
    return TOK_IDENT;
}

// ---------- Token Readers ----------

static Token identifier(void) {
    int start = pos - 1;
    while (is_alpha(peek()) || is_digit(peek())) {
        advance();
    }
    int length = pos - start;
    char *text = strndup(src + start, length);
    TokenType type = keyword_type(text);
    free(text);
    return make_token(type, src + start, length);
}

static Token number(void) {
    int start = pos - 1;
    while (is_digit(peek())) {
        advance();
    }
    return make_token(TOK_NUMBER, src + start, pos - start);
}

// ---------- Public API ----------

void lexer_init(const char *source) {
    src = source;
    pos = 0;
    line = 1;
}

Token lexer_next_token(void) {
    skip_whitespace();

    char c = advance();

    if (c == '\0') {
        return make_token(TOK_EOF, "", 0);
    }

    if (is_alpha(c)) return identifier();
    if (is_digit(c)) return number();

    switch (c) {
        case '+': return make_token(TOK_PLUS, "+", 1);
        case '-': return make_token(TOK_MINUS, "-", 1);
        case '*': return make_token(TOK_STAR, "*", 1);
        case '/': return make_token(TOK_SLASH, "/", 1);
        case '=': return make_token(TOK_ASSIGN, "=", 1);
        case ';': return make_token(TOK_SEMI, ";", 1);
        case '(': return make_token(TOK_LPAREN, "(", 1);
        case ')': return make_token(TOK_RPAREN, ")", 1);
        case '{': return make_token(TOK_LBRACE, "{", 1);
        case '}': return make_token(TOK_RBRACE, "}", 1);
    }

    return error_token("Unexpected character");
}
