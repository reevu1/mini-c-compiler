#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer.h"

char* strndup(const char* src, size_t len) {
    char* dest = (char*)malloc(len + 1);
    if (!dest) return NULL;
    strncpy(dest, src, len);
    dest[len] = '\0';
    return dest;
}


const char* keywords[] = {"int", "return"};
const TokenType keyword_types[] = {TOKEN_INT, TOKEN_RETURN};

int is_keyword(const char* str) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); ++i) {
        if (strcmp(str, keywords[i]) == 0)
            return keyword_types[i];
    }
    return -1;
}

void skip_whitespace(const char* source, int* index) {
    while (isspace(source[*index])) (*index)++;
}

Token make_token(TokenType type, const char* lexeme) {
    Token token;
    token.type = type;
    token.lexeme = strdup(lexeme);
    return token;
}

void free_token(Token token) {
    free(token.lexeme);
}

Token get_next_token(const char* source, int* index) {
    skip_whitespace(source, index);
    char c = source[*index];

    if (c == '\0') return make_token(TOKEN_EOF, "EOF");

    // Single-character tokens
    switch (c) {
        case '+': (*index)++; return make_token(TOKEN_PLUS, "+");
        case '-': (*index)++; return make_token(TOKEN_MINUS, "-");
        case '=': (*index)++; return make_token(TOKEN_ASSIGN, "=");
        case ';': (*index)++; return make_token(TOKEN_SEMICOLON, ";");
        case '(': (*index)++; return make_token(TOKEN_LPAREN, "(");
        case ')': (*index)++; return make_token(TOKEN_RPAREN, ")");
        case '{': (*index)++; return make_token(TOKEN_LBRACE, "{");
        case '}': (*index)++; return make_token(TOKEN_RBRACE, "}");
    }

    // Identifiers and keywords
    if (isalpha(c) || c == '_') {
        int start = *index;
        while (isalnum(source[*index]) || source[*index] == '_') (*index)++;
        int length = *index - start;
        char* str = strndup(&source[start], length);

        int kw_type = is_keyword(str);
        Token token = make_token((kw_type != -1) ? kw_type : TOKEN_IDENTIFIER, str);
        free(str);
        return token;
    }

    // Numbers
    if (isdigit(c)) {
        int start = *index;
        while (isdigit(source[*index])) (*index)++;
        int length = *index - start;
        char* str = strndup(&source[start], length);
        Token token = make_token(TOKEN_NUMBER, str);
        free(str);
        return token;
    }

    // Unknown token
    (*index)++;
    return make_token(TOKEN_UNKNOWN, "?");
}

const char* token_type_to_string(TokenType type) {
    switch (type) {
        case TOKEN_INT: return "INT_KEYWORD";
        case TOKEN_RETURN: return "RETURN_KEYWORD";
        case TOKEN_IDENTIFIER: return "IDENTIFIER";
        case TOKEN_NUMBER: return "NUMBER";
        case TOKEN_PLUS: return "PLUS";
        case TOKEN_MINUS: return "MINUS";
        case TOKEN_ASSIGN: return "ASSIGN";
        case TOKEN_SEMICOLON: return "SEMICOLON";
        case TOKEN_LPAREN: return "LPAREN";
        case TOKEN_RPAREN: return "RPAREN";
        case TOKEN_LBRACE: return "LBRACE";
        case TOKEN_RBRACE: return "RBRACE";
        case TOKEN_EOF: return "EOF";
        case TOKEN_UNKNOWN: return "UNKNOWN";
        default: return "INVALID";
    }
}
