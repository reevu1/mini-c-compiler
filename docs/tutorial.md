# Extending the Mini C Compiler

This document explains how to add new features to the compiler.

## Adding a New Operator

1. Add token in TokenType enum
2. Update lexer to recognize the operator
3. Extend grammar rules in the parser
4. Add AST node support if required
5. Update code generation logic

## Adding a New Statement (e.g., if)

1. Extend grammar
2. Add new AST node kind
3. Update parser to build new AST nodes
4. Add semantic checks
5. Generate corresponding code

## Debugging Tips

- Use the AST printer to verify parsing
- Add semantic checks incrementally
- Test small programs first

## Suggested Extensions

- Variable declarations (`int x;`)
- Conditional statements (`if`, `else`)
- Loops (`while`)
- Type checking
- Function definitions
