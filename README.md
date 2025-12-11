# Mini C Compiler

A small C compiler for a simplified subset of the C language, built from scratch in C.

## Features
- Lexical Analysis (Lexer)
- Recursive Descent Parser
- AST Construction
- Semantic Analysis (Symbol Table, Type Checking)
- Stack-Based Code Generation
- Mini Virtual Machine (optional)

## Project Structure
- `src/` – source code
- `docs/` – design documents and grammar
- `tests/` – unit tests
- `examples/` – sample programs the compiler can compile

## How to Build
```bash
make
./mini-c program.c
