# Compiler

A small compiler written in C++ that translates a minimal programming language into ARM64 assembly, then assembles and links it into a native executable.

This is a learning project whose goal is to understand the entire compilation pipeline, from tokenization to code generation and assembly, before moving on to more advanced compiler concepts.

## Current Features

The language currently supports a single instruction:

```text
exit <code>;
```

Example (`test.txt`):

```text
exit 42;
```

Compiling this file produces an executable that exits with status code `42`.

## How It Works

1. **Tokenizer** (`src/tokenization.hpp`): splits the source code into tokens (`exit`, an integer literal, and `;`).
2. **Code Generation** (`tokens_to_asm` in `src/main.cpp`): walks through the token stream and generates the ARM64 assembly corresponding to `exit N;` (using the `exit` system call with exit code `N`).
3. **Assembly and Linking**: the generated `.s` file is assembled with `as` and linked with `ld` to produce a native executable.

## Requirements

* A C++ compiler (C++17 or later)
* ARM64 cross-compilation tools:

  * `aarch64-linux-gnu-as`
  * `aarch64-linux-gnu-ld`

On Debian/Ubuntu:

```bash
sudo apt install g++ binutils-aarch64-linux-gnu
```

## Building

```bash
g++ -std=c++17 -o comp src/main.cpp
```

## Usage

```bash
./comp test.txt
./exec
echo $?   # Prints the exit status defined by "exit N;"
```

## Current Limitations

* Only one instruction is supported (`exit`).
* No syntax error handling. Invalid input silently produces an empty program.
* ARM64 is the only supported target architecture (cross-compilation tools are required on non-ARM64 hosts).
* No Abstract Syntax Tree (AST) yet. Code generation operates directly on the token stream.

## Roadmap

* Add arithmetic operations (`+`, `-`, etc.)
* Add variables
* Replace the flat token stream with a proper parser and an Abstract Syntax Tree (AST)
* Improve syntax error reporting

