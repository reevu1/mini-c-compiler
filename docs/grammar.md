# Grammar Specification

This document describes the grammar of the supported C subset.

## Tokens

- IDENT     → identifier
- NUMBER    → integer literal
- '+' '-' '*' '/'
- '='
- ';'
- '(' ')'

## Grammar (EBNF)

statement  → IDENT '=' expression ';'

expression → term { ('+' | '-') term }

term       → factor { ('*' | '/') factor }

factor     → NUMBER
           | IDENT
           | '(' expression ')'

## Operator Precedence

Highest precedence:
1. '*' '/'
2. '+' '-'
3. '='

## Associativity

- '+' '-' '*' '/' are left-associative
- '=' is right-associative (handled at statement level)

## Example

Input:

x = 10 + 20 * 3;


Parsed as:


x = (10 + (20 * 3));
