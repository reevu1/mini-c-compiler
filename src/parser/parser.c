#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer/lexer.h"

#define STACK_SIZE 200

/*
Terminals
*/
typedef enum {
    T_ID,
    T_NUM,
    T_PLUS,
    T_MINUS,
    T_STAR,
    T_SLASH,
    T_AND,
    T_OR,
    T_LPAREN,
    T_RPAREN,
    T_ASSIGN,
    T_SEMI,
    T_DOLLAR
} Terminal;

/*
Nonterminals
*/
typedef enum {
    NT_S,
    NT_E,
    NT_EP,
    NT_T,
    NT_TP,
    NT_F
} NonTerminal;

/*
Symbol type
*/
typedef struct {
    int is_terminal;
    int value;
} Symbol;

/*
Stack
*/
Symbol stack[STACK_SIZE];
int top = -1;

void push(Symbol s) {
    stack[++top] = s;
}

Symbol pop() {
    return stack[top--];
}

Symbol peek() {
    return stack[top];
}

/*
Token to terminal mapping
*/
Terminal token_to_terminal(Token t) {

    switch(t.type) {

        case TOK_IDENT: return T_ID;
        case TOK_NUMBER: return T_NUM;
        case TOK_PLUS: return T_PLUS;
        case TOK_MINUS: return T_MINUS;
        case TOK_STAR: return T_STAR;
        case TOK_SLASH: return T_SLASH;
        case TOK_AND: return T_AND;
        case TOK_OR: return T_OR;
        case TOK_LPAREN: return T_LPAREN;
        case TOK_RPAREN: return T_RPAREN;
        case TOK_ASSIGN: return T_ASSIGN;
        case TOK_SEMI: return T_SEMI;
        case TOK_EOF: return T_DOLLAR;

        default:
            printf("Unknown token\n");
            exit(1);
    }
}

/*
Push RHS in reverse
*/
void push_production(Symbol *rhs, int len) {

    for(int i=len-1;i>=0;i--)
        push(rhs[i]);
}

/*
LL(1) table lookup
*/

void apply_rule(NonTerminal nt, Terminal t) {

    Symbol rhs[5];
    int len = 0;

    switch(nt) {

    case NT_S:

        if(t==T_ID) {

            printf("S -> id = E ;\n");

            rhs[len++] = (Symbol){1,T_SEMI};
            rhs[len++] = (Symbol){0,NT_E};
            rhs[len++] = (Symbol){1,T_ASSIGN};
            rhs[len++] = (Symbol){1,T_ID};

            push_production(rhs,len);
        }
        break;

    case NT_E:

        if(t==T_ID || t==T_NUM || t==T_LPAREN) {

            printf("E -> T E'\n");

            rhs[len++] = (Symbol){0,NT_EP};
            rhs[len++] = (Symbol){0,NT_T};

            push_production(rhs,len);
        }
        break;

    case NT_EP:

        if(t==T_PLUS) {

            printf("E' -> + T E'\n");

            rhs[len++] = (Symbol){0,NT_EP};
            rhs[len++] = (Symbol){0,NT_T};
            rhs[len++] = (Symbol){1,T_PLUS};

            push_production(rhs,len);
        }

        else if(t==T_MINUS) {

            printf("E' -> - T E'\n");

            rhs[len++] = (Symbol){0,NT_EP};
            rhs[len++] = (Symbol){0,NT_T};
            rhs[len++] = (Symbol){1,T_MINUS};

            push_production(rhs,len);
        }

        else if(t==T_OR) {

            printf("E' -> || T E'\n");

            rhs[len++] = (Symbol){0,NT_EP};
            rhs[len++] = (Symbol){0,NT_T};
            rhs[len++] = (Symbol){1,T_OR};

            push_production(rhs,len);
        }

        else {

            printf("E' -> ε\n");
        }

        break;

    case NT_T:

        if(t==T_ID || t==T_NUM || t==T_LPAREN) {

            printf("T -> F T'\n");

            rhs[len++] = (Symbol){0,NT_TP};
            rhs[len++] = (Symbol){0,NT_F};

            push_production(rhs,len);
        }

        break;

    case NT_TP:

        if(t==T_STAR) {

            printf("T' -> * F T'\n");

            rhs[len++] = (Symbol){0,NT_TP};
            rhs[len++] = (Symbol){0,NT_F};
            rhs[len++] = (Symbol){1,T_STAR};

            push_production(rhs,len);
        }

        else if(t==T_SLASH) {

            printf("T' -> / F T'\n");

            rhs[len++] = (Symbol){0,NT_TP};
            rhs[len++] = (Symbol){0,NT_F};
            rhs[len++] = (Symbol){1,T_SLASH};

            push_production(rhs,len);
        }

        else if(t==T_AND) {

            printf("T' -> && F T'\n");

            rhs[len++] = (Symbol){0,NT_TP};
            rhs[len++] = (Symbol){0,NT_F};
            rhs[len++] = (Symbol){1,T_AND};

            push_production(rhs,len);
        }

        else {

            printf("T' -> ε\n");
        }

        break;

    case NT_F:

        if(t==T_ID) {

            printf("F -> id\n");

            rhs[len++] = (Symbol){1,T_ID};
            push_production(rhs,len);
        }

        else if(t==T_NUM) {

            printf("F -> num\n");

            rhs[len++] = (Symbol){1,T_NUM};
            push_production(rhs,len);
        }

        else if(t==T_LPAREN) {

            printf("F -> ( E )\n");

            rhs[len++] = (Symbol){1,T_RPAREN};
            rhs[len++] = (Symbol){0,NT_E};
            rhs[len++] = (Symbol){1,T_LPAREN};

            push_production(rhs,len);
        }

        break;
    }
}

/*
Predictive parser
*/

void parse() {

    Token token = lexer_next_token();

    push((Symbol){1,T_DOLLAR});
    push((Symbol){0,NT_S});

    while(top>=0) {

        Symbol X = peek();
        Terminal a = token_to_terminal(token);

        printf("Token: %s\n", token.lexeme);

        if(X.is_terminal) {

            if(X.value == a) {

                pop();
                token = lexer_next_token();
            }

            else {

                printf("Error: token mismatch\n");
                token = lexer_next_token();
            }
        }

        else {

            pop();
            apply_rule(X.value, a);
        }
    }

    printf("Parsing finished\n");
}