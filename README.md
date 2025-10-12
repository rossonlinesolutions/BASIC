# 🧮 BASIC Interpreter in C++

Welcome to your very own retro computing adventure! This project is a minimalist interpreter for our own **BASIC** dialect, a simplified version of the BASIC programming language originally designed for early microcomputers. Written in modern C++, this interpreter brings vintage programming charm to today's systems.

## 🚀 Features

- 📝 Line-numbered program input
- 🔤 Single-letter variables (`A` to `Z`)
- 📤 Basic I/O: `PRINT`, `INPUT`
- 🔁 Control flow: `IF`, `GOTO`, `GOSUB`, `RETURN`
- 💬 Comments via `REM`
- 🧠 In-memory program storage and execution
- 🧪 Interactive REPL (Read-Eval-Print Loop)

## 📦 Getting Started

### Requirements

- C++17 or later
- A standard C++ compiler (e.g., `g++`, `clang++`, MSVC)
- Google test

### Build Instructions

```bash
git clone https://github.com/rossonlinesolutions/BASIC.git
cd BASIC
make
./build/basic
```

Or compile manually:

```bash
g++ -std=c++17 -o basic -Iinclude src/Main.cpp
```


## 🧑‍💻 Usage

Once launched, you'll enter the REPL. You can type Tiny BASIC commands directly or enter a full program line-by-line using line numbers.

## 📃 Example

A simple sorting algorithm example:

```basic
REM "Read 24 ascii characters"

LET A = 2
20 IF A = 26 THEN GOTO 100
INPUT VAR(A)
LET A = A + 1
GOTO 20

100 REM "Sorting..."

LET A = 2

REM "If reached end, everything is sorted."
110 IF A = 25 THEN GOTO 200
LET A = A + 1
IF VAR(A - 1) <= VAR(A) THEN GOTO 110

REM "Swap A-1"
LET B = VAR(A - 1)
LET VAR(A - 1) = VAR(A)
LET VAR(A) = B

REM "Restart from new"
LET A = 2
GOTO 110

200 REM "Print all variables in ascending order"
LET A = 2

210 IF A = 26 THEN END
PRINT VAR(A)
LET A = A + 1
GOTO 210

REM "Start execution:"
RUN

```

## 📚 Language Reference

| Command     | Description                             |
|-------------|-----------------------------------------|
| `LET`       | Assign value to variable                |
| `PRINT`     | Display a string or character sequences |
| `INPUT`     | Read user input                         |
| `IF ... THEN` | Conditional execution                 |
| `GOTO`      | Jump to a line number                   |
| `GOSUB`/`RETURN` | Subroutine call/return             |
| `REM`       | Comment                                 |
| `END`       | Terminate program                       |

See [the Language Specification](./Documentation/specification/01-Introduction-and-scope.md) for full language reference.


## 📜 License

This project is licensed under the MIT License. See `LICENSE` for details.
