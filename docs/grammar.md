# Mini C Compiler - Grammar Specification

## Tokens
- Keywords: int, if, else, while
- Identifiers
- Numbers (integer literals)
- Symbols: = + - * / ; ( ) { }

## Grammar

program       → decl* stmt*
decl          → "int" IDENT ";"
stmt          → assign_stmt
              | if_stmt
              | while_stmt
              | block

assign_stmt   → IDENT "=" expr ";"

if_stmt       → "if" "(" expr ")" stmt ("else" stmt)?

while_stmt    → "while" "(" expr ")" stmt

block         → "{" stmt* "}"

expr          → term (("+"|"-") term)*
term          → factor (("*"|"/") factor)*
factor        → NUMBER | IDENT | "(" expr ")"
