# Chapter 4. Static Semantics

## 4.1 Variables
- The identifiers `A` through `Z` denote global variables.
- All variables exist implicitly; no declaration is required.
- The initial value of each variable is **undefined**.
- Reading the value of a variable before it has been assigned results in undefined behavior (see Appendix A).
- `Var(n)` denote the n-th variable, where n is an expression.

## 4.2 Types
- All variables are of type **32‑bit signed integer**.
- All expressions evaluate to integers.
- String literals are not values of a type; they are only valid in the contexts of `PRINT` and `REM`.

## 4.3 Scope
- All variables share a single **global scope**.
- Subroutines invoked by `GOSUB` and exited by `RETURN` share the same global scope.
- No local or nested scopes exist.

## 4.4 Well‑Formedness
- Any program that is syntactically valid according to [Chapter 3](03-syntax-and-grammar.md) is also semantically valid, except where undefined behavior is explicitly noted.
- Undefined behaviors are collected in [Appendix A](appendices.md).

## 4.5 Control Flow Constraints
- A `RETURN` statement is only valid if preceded by a `GOSUB`.
  - If `RETURN` is executed with an empty call stack, the program aborts.
- A `GOTO` or `GOSUB` expression must evaluate to a positive integer.
  - If the result is negative, the program aborts.

## 4.6 Input Semantics
- The `INPUT` statement assigns the ASCII codes of entered characters to the specified variables in order.
- If more variables are listed than characters available in the input stream, the program aborts.
- Example:
  ```
  INPUT A, B, A
  ```
  With input `cba`, results in `A = 'a'`, `B = 'b'`.

## 4.7 Output Semantics
- The `PRINT` statement outputs the ASCII character corresponding to the integer value of each expression.
- String literals are output verbatim.
- Outputting values outside the ASCII range is undefined behavior (see Appendix A).

## 4.8 Clear Semantics
- Clears the program entered before.
- Resets all variables to undefined.
