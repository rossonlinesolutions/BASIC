# Chapter 2. Lexical Structure

## 2.1 Character Set
Our BASIC dialect's programs are defined over the **7‑bit ASCII character set**.
- Characters outside the 7‑bit ASCII range may appear in string or character literals, but their behavior is **undefined**.
- Identifiers and keywords are restricted to **uppercase letters A–Z**. Lowercase letters are not part of the lexical structure, except within string and character literals.
- Implementations may optionally treat identifiers and keywords case‑insensitively, but this is not required. The reference test suite assumes uppercase only.

## 2.2 Whitespace
Whitespace consists of all characters for which the C standard library function `isspace` returns true.
- Whitespace may separate tokens but is not otherwise significant.
- Line breaks are **mandatory** for statement separation.
- A line break is any of the following sequences: `\n`, `\r\n`, or `\r`.
- Whitespace characters are not permitted inside string or character literals.
- Newline characters are not permitted inside string or character literals.

## 2.3 Comments
Comments are introduced by the keyword `REM`.
- A comment must appear as the **only statement** on a line.
- A line number may precede the `REM` keyword.
- The `REM` keyword must be followed by valid tokens, typically string literals.
- Comments are not executable statements and cannot appear conditionally (e.g., inside an `IF` branch).
- Any other usage of `REM` is undefined behavior.

**Example:**
```
10 REM "This is a comment"
```

## 2.4 Identifiers
Identifiers in our BASIC dialect are limited to the single uppercase letters `A` through `Z`.
- Each identifier denotes a global variable.
- The initial value of each variable is undefined.
- All identifiers are of type **32‑bit signed integer**.
- Support for wider integer types is optional and outside the scope of this specification.
- Identifiers do not intersect with reserved keywords.
- Lowercase identifiers (`a`–`z`) may be supported by implementations but are not part of this specification.

**EBNF:**
```
Identifier ::= "A" | "B" | "C" | ... | "Z"
```

## 2.5 Keywords
The following words are reserved keywords in our BASIC dialect. They must appear in uppercase. Implementations may optionally accept lowercase or mixed case, but this is not required.

| Keyword  | Purpose                      |
| -------- | ---------------------------- |
| `LET`    | Assignment statement         |
| `PRINT`  | Output statement             |
| `INPUT`  | Input statement              |
| `IF`     | Conditional statement        |
| `THEN`   | Conditional branch           |
| `GOTO`   | Unconditional jump           |
| `GOSUB`  | Subroutine call              |
| `RETURN` | Subroutine return            |
| `REM`    | Comment                      |
| `RUN`    | Start execution              |
| `END`    | End execution                |
| `CLEAR`  | Clear all entered statements |

## 2.6 Literals

### 2.6.1 Numeric Literals
- Numeric literals are decimal integers, optionally signed.
- Only base‑10 is supported.
- Arbitrary length is permitted, but usage of values exceeding 32‑bit signed integer range is undefined unless the implementation supports wider variables.

**EBNF:**
```
IntegerLiteral ::= ["+" | "-"] Digit { Digit }
Digit           ::= "0"…"9"
```

### 2.6.2 String Literals
- A string literal is enclosed in double quotes (`"`).
- All characters between the quotes are captured verbatim.
- Newline characters are not permitted inside string literals.
- Escape sequences are not supported.

**EBNF:**
```
StringLiteral ::= '"' { StringCharacter } '"'
StringCharacter ::= /* any 7-bit ASCII character except '"' or newline */
```

### 2.6.3 Character Literals
- A character literal is written as `#c`, where `c` is a single 7‑bit ASCII character.
- The sequence `##` represents the literal `#`.
- Escape sequences are not supported.
- Non‑ASCII characters are undefined behavior.

**EBNF:**
```
CharLiteral ::= "#" ( ASCIICharacter | "#" )
```

### 2.6.4 Boolean Literals
- Our BASIC dialect does not define boolean literals.  
- Boolean values are represented by integer expressions (zero = false, nonzero = true).

## 2.7 Operators and Delimiters
The following operators are defined:

- **Comparison operators** (usable only in `IF` statements):
  `<`, `>`, `<>`, `=`, `<=`, `>=`

- **Arithmetic operators**:
  Unary: `+`, `-`
  Binary: `+`, `-`, `*`, `/`

- **Assignment operator**:
  `=` (used in `LET` statements)

Delimiters include:
- Parentheses `(` `)`
- Comma `,`
- Semicolon `;`
- Colon `:` (for statement separation)

## 2.8 Line Numbers
- Line numbers are optional.
- If the first token of a line is an integer, it is interpreted as a line number.
- If no line number is specified, the line number is implicitly the previous line number plus one.
- Line numbers need not be sequential or unique; entering a line with an existing number overwrites the previous line.

**EBNF:**
```
LineNumber ::= Digit { Digit }
```

## 2.9 End of Input
The end of a program is defined by:
- The end of the input file, or
- An explicit `EXIT` or `QUIT` statement.

The keyword `END` terminates program execution but does not mark the end of input.
