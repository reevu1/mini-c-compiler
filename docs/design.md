# Mini C Compiler – Design Overview

This project implements a compiler for a simplified subset of the C language.
The compiler is built in multiple well-defined stages, each responsible for a
specific transformation of the program.

## Compilation Pipeline

Source Code
→ Lexer
→ Parser
→ Abstract Syntax Tree (AST)
→ Semantic Analysis
→ Code Generation

## 1. Lexer (Lexical Analysis)

The lexer reads the input source code character by character and converts it
into a stream of tokens.

Responsibilities:
- Remove whitespace and comments
- Recognize identifiers, keywords, literals, and operators
- Track line numbers for error reporting

Output:
- A sequence of tokens (TokenType, lexeme, line number)

## 2. Parser (Syntax Analysis)

The parser consumes tokens from the lexer and checks whether they conform to
the grammar of the language. It uses recursive descent parsing.

Responsibilities:
- Enforce grammar rules
- Handle operator precedence and associativity
- Build an Abstract Syntax Tree (AST)

Output:
- An AST representing the hierarchical structure of the program

## 3. Abstract Syntax Tree (AST)

The AST is a tree representation of the program that captures its meaning
while ignoring syntactic details such as parentheses and formatting.

Responsibilities:
- Represent program structure in a machine-friendly way
- Serve as the input for semantic analysis and code generation

## 4. Semantic Analysis

Semantic analysis walks the AST and enforces rules that cannot be checked by
syntax alone.

Responsibilities:
- Track declared variables using a symbol table
- Detect use of undeclared variables
- Prevent variable redeclaration

## 5. Code Generation

The final stage translates the AST into target code (stack-based instructions).

Responsibilities:
- Traverse the AST
- Emit instructions for expressions and statements
- Manage evaluation order using a stack model
