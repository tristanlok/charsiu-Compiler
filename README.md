## Introduction

Charsiu is a high level programming language meant as a learning platform for me to discover the world of compilers and the theories required to implement a compiler.
The Dragon Book was used to assist me throughout the journey of developing a compiler.

Deeper explanation of the proccess can be found in the wiki -> journey

![Char_Siu_Fan](https://github.com/tristanlok/chasiu-Compiler/assets/157249099/bbeb56a4-79d0-40dd-af14-8a34c2d919c9)

## About the Project

This project is composed of several parts:

* **Lexer**: scans the Charsiu code and tokenizes it
* **Parser**: parses the Charsiu code and creates an AST (abstract syntax tree)
* **Optimizer**: descends the AST (abstract syntax tree) and optimizes any operations that can be performed at compile time
* **Assembler**: turns optimized Charsiu code from AST (abstract syntax tree) to Assembly x86-64 NASM code

### Lexer

The lexer takes the Charsiu program and tokenizes everything.
This step is useful to weed out any typos and makes the parser simpler.

### Parser

The parser takes the lexcial tokens and translates it into its corresponding AST (abstract syntax tree).
This step is crucial in enforcing the semantic rules of the charsiu language and in making the assembler simpler.

### Optimizer

The optimizer takes the AST (abstract syntax tree) and performs optimization to operations that have known values at compile time.
This step is important in making the later compiled program more efficient.

### Assembler

The assembler takes the parsed Charsiu program and creates assembly code which represents the program.
This assembly code is for x86-64 machines using Intel Syntax.
