# 🧮 Tiny BASIC Interpreter in C++

Welcome to your very own retro computing adventure! This project is a minimalist interpreter for **Tiny BASIC**, a simplified version of the BASIC programming language originally designed for early microcomputers. Written in modern C++, this interpreter brings vintage programming charm to today's systems.

---

## 🚀 Features

- 📝 Line-numbered program input
- 🔤 Single-letter variables (`A` to `Z`)
- 📤 Basic I/O: `PRINT`, `INPUT`
- 🔁 Control flow: `IF`, `GOTO`, `GOSUB`, `RETURN`, `FOR`, `NEXT`
- 💬 Comments via `REM`
- 🧠 In-memory program storage and execution
- 🧪 Interactive REPL (Read-Eval-Print Loop)

---

## 📦 Getting Started

### Requirements

- C++17 or later
- A standard C++ compiler (e.g., `g++`, `clang++`, MSVC)

### Build Instructions

```bash
git clone https://github.com/rossonlinesolutions/tiny-basic.git
cd tiny-basic
make
./tinybasic
```

Or compile manually:

```bash
g++ -std=c++17 -o tinybasic main.cpp
```

---

## 🧑‍💻 Usage

Once launched, you'll enter the REPL. You can type Tiny BASIC commands directly or enter a full program line-by-line using line numbers.

### Example Program

```basic
10 REM Factorial calculator
20 INPUT N
30 LET F = 1
40 FOR I = 1 TO N
50 LET F = F * I
60 NEXT I
70 PRINT F
80 END
```

Type `RUN` to execute your program. Use `LIST` to view it, and `NEW` to clear memory.

---

## 📚 Language Reference

| Command     | Description                            |
|-------------|----------------------------------------|
| `LET`       | Assign value to variable               |
| `PRINT`     | Display value or string                |
| `INPUT`     | Read user input                        |
| `IF ... THEN` | Conditional execution                |
| `GOTO`      | Jump to a line number                  |
| `GOSUB`/`RETURN` | Subroutine call/return           |
| `FOR`/`NEXT` | Looping construct                     |
| `REM`       | Comment                                |
| `END`       | Terminate program                      |


## 📜 License

This project is licensed under the MIT License. See `LICENSE` for details.
