# Code Generation

This compiler uses a simple stack-based execution model for code generation.

## Target Model

- Stack-based virtual machine
- Expressions push values onto the stack
- Operators pop operands and push results

## Instruction Set (Planned)

- PUSH <value>      ; push integer literal
- LOAD <name>       ; load variable value
- STORE <name>      ; store variable value
- ADD               ; addition
- SUB               ; subtraction
- MUL               ; multiplication
- DIV               ; division

## Example

Source:
x = 10 + 20;


Generated instructions:


PUSH 10
PUSH 20
ADD
STORE x


## Notes

- Code generation walks the AST recursively
- Evaluation order is determined by AST structure
- Future extensions may include registers or LLVM IR