# Chapter 3. Syntax and Grammar

## 3.1 Programs
A **program** of our BASIC dialect is a sequence of lines. Each line consists of an optional line number followed by a statement, or a comment introduced by `REM`.

- Empty lines are permitted.
- Empty lines with a line number are **illegal**.
- Multiple statements on a single line are **not permitted**, except when a statement follows `THEN` in an `IF` statement.
- Execution begins with the statement having the lowest positive line number and proceeds in ascending order of line numbers.
- Program execution is initiated by entering the `RUN` statement.
- Re‑entering `RUN` restarts execution from the beginning, including any newly entered lines.

**EBNF:**
```
Program       ::= { Line }
Line          ::= [ LineNumber ] Statement LineBreak
                | [ LineNumber ] "REM" { Token } LineBreak
LineNumber    ::= Digit { Digit }
LineBreak     ::= '\n' | '\r\n' | '\r'
```

## 3.2 Statements
The following statements are defined in our BASIC dialect:

```
Statement     ::= PrintStatement
                | IfStatement
                | GotoStatement
                | InputStatement
                | LetStatement
                | GosubStatement
                | ReturnStatement
                | ClearStatement
                | RunStatement
                | EndStatement
                | ExitStatement
```

### 3.2.1 `PRINT`
```
PrintStatement ::= "PRINT" ExprList
ExprList       ::= ( StringLiteral | Expression )
                   { "," ( StringLiteral | Expression ) }
```
- Each expression is evaluated to an integer and output as the corresponding ASCII character.
- String literals are output verbatim.
- Outputting values outside the ASCII range is undefined behavior.
- Only comma separators are permitted.

### 3.2.2 `IF … THEN`
```
IfStatement   ::= "IF" Expression RelOp Expression "THEN" Statement
RelOp         ::= "<" [ ">" | "=" ]
                | ">" [ "<" | "=" ]
                | "="
```
- The relational operators `<`, `>`, `<=`, `>=`, `=`, and `<>` are supported.
- The `THEN` clause must contain exactly one statement, written on the same line.
- Jumping to another line requires an explicit `GOTO` or `GOSUB`.

### 3.2.3 `GOTO`
```
GotoStatement ::= "GOTO" Expression
```
- The expression is evaluated to an integer.
- Execution continues at the statement with the smallest line number greater than or equal to this value.

### 3.2.4 `INPUT`
```
InputStatement ::= "INPUT" VarList
VarList        ::= Variable { "," Variable }
```
- Reads input values into one or more variables.
- At least one variable must be specified.

### 3.2.5 `LET`
```
LetStatement  ::= "LET" Variable "=" Expression
```
- Assigns the value of the expression to the specified variable.

### 3.2.6 `GOSUB` and `RETURN`
```
GosubStatement ::= "GOSUB" Expression
ReturnStatement ::= "RETURN"
```
- `GOSUB` pushes the current line number onto the call stack and transfers control to the line number determined by the expression.
- `RETURN` pops the top of the call stack and resumes execution at the following line.
- If `RETURN` is executed with an empty call stack, the program aborts.
- Nested subroutine calls are permitted.

### 3.2.7 `CLEAR`
```
ClearStatement ::= "CLEAR"
```
- Clears all variables, resetting them to an undefined state.

### 3.2.8 `RUN`
```
RunStatement ::= "RUN"
```
- Starts execution of the program from the lowest line number.
- May be entered multiple times; each invocation restarts execution.

### 3.2.9 `END`
```
EndStatement ::= "END"
```
- Terminates execution of the program initiated by `RUN`.
- The interpreter remains active and continues to accept input.

### 3.2.10 `EXIT` and `QUIT`
```
ExitStatement ::= "EXIT" | "QUIT"
```
- Terminates the interpreter session and ends input.
- `EXIT` and `QUIT` are aliases.

## 3.3 Expressions
```
Expression    ::= [ "+" | "-" ] Term { ( "+" | "-" ) Term }
Term          ::= Factor { ( "*" | "/" ) Factor }
Factor        ::= Variable | Number | "(" Expression ")"
Variable      ::= "A" | "B" | "C" | ... | "Y" | "Z" | "VAR" "(" Expression ")"
```

- Standard precedence applies: multiplication and division bind tighter than addition and subtraction.
- Parentheses may be used for grouping.
- Only integer expressions are defined.

## 3.4 Numbers
```
Number        ::= Digit { Digit } | # /* any 7-bit ASCII character except newline */
Digit         ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
```
- Numbers are decimal integers.
- Arbitrary length is permitted, but behavior is undefined if values exceed the implementation’s integer capacity.

## 3.5 Strings
```
StringLiteral ::= '"' { StringCharacter } '"'
StringCharacter ::= /* any 7-bit ASCII character except '"' or newline */
```
- Strings are enclosed in double quotes.
- Newlines are not permitted inside string literals.
- Escape sequences are not supported.

## 3.6 Program Termination
- `END` terminates execution but not the interpreter.
- `EXIT` and `QUIT` terminate the interpreter session.
