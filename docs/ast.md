# Abstract Syntax Tree (AST)

The AST represents the hierarchical structure and meaning of a program.

## AST Node Kinds

- AST_INT_LITERAL
- AST_IDENTIFIER
- AST_BINARY_EXPR
- AST_ASSIGN_STMT

## AST Node Structure

Each AST node has:
- a kind (ASTKind)
- a union holding data relevant to that kind

## Node Descriptions

### Integer Literal
Represents numeric constants.
Example:
10

### Identifier
Represents variable names.
Example:
x

### Binary Expression
Represents arithmetic expressions.
Example:
a + b


### Assignment Statement
Represents variable assignment.
Example:
x = 10 + 20;


## Why AST?

- Removes syntactic noise
- Encodes operator precedence
- Enables semantic analysis
- Simplifies code generation