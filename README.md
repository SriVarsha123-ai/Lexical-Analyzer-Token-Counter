# Lexical Analyzer & Token Counter

## 1. Title

Lexical Analyzer & Token Counter

## 2. Objective

The objective of this project is to develop a lexical analyzer in C that reads source code and identifies different types of tokens such as keywords, identifiers, operators, constants, separators, special symbols, comments, and string literals.

## 3. Problem Statement

Lexical analysis is the first phase of a compiler. It reads the source program and divides it into meaningful units called tokens.

This project implements a simple lexical analyzer that accepts source code as input and identifies different types of tokens.

The program also displays the token type for each identified token.

## 4. Algorithm

1. Start the program.
2. Read the source code.
3. Scan the source code character by character.
4. Ignore white spaces.
5. Identify keywords and identifiers.
6. Identify constants and literals.
7. Identify operators.
8. Identify separators and special symbols.
9. Identify comments.
10. Display each token along with its token type.
11. Count the different types of tokens.
12. Display the final token counts.
13. Stop the program.

## 5. Source Code

The source code is available in:

`lexical_analyzer.c`

The program is implemented using the C programming language.

## 6. Sample Input

```c
int sum = a + b;
float average = sum / 2;

// Calculate average

if (average > 50)
    printf("Pass");