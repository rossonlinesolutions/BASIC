# Appendices

## Appendix A. Undefined Behavior

The following cases are explicitly defined as **undefined behavior** in BASIC, Ross Online Solutions flavored 1.0.0.
In these cases, the interpreter may behave in any manner, including continuing execution, aborting execution, or producing arbitrary results.
Undefined behavior does not affect conformance.

- Reading the value of a variable before it has been assigned.
- Using non‑ASCII characters in string or character literals.
- Numeric literals exceeding the 32‑bit signed integer range (unless the implementation supports wider variables).
- Printing values outside the ASCII range.
- Stack overflow caused by excessive nesting of `GOSUB` calls.
- Illegal usage of `REM` (e.g., not followed by valid tokens).

## Appendix B. Example Programs

The following examples are **informative only** and do not form part of the normative specification.
They illustrate typical usage of our BASIC dialect in both interactive (with line numbers) and batch (without line numbers) modes.

### B.1 Hello World (Interactive Mode)
```bas
10 PRINT "HELLO, WORLD"
20 END
RUN
```

### B.2 Simple Loop (Interactive Mode)
```bas
10 LET A = 65
20 IF A > 90 THEN END
30 PRINT A
40 LET A = A + 1
50 GOTO 20
RUN
```
This program prints the uppercase letters `A` through `Z`.

### B.3 Subroutine Example (Interactive Mode)
```bas
10 GOSUB 100
20 PRINT "DONE"
30 END
100 PRINT "IN SUBROUTINE"
110 RETURN
RUN
```

### B.4 Input and Echo (Interactive Mode)
```bas
10 INPUT A, B, C
20 PRINT A, B, C
30 END
RUN
```
If the user enters `XYZ`, the program prints `XYZ`.

### B.5 Batch Mode Example (No Line Numbers)
```bas
PRINT "BATCH EXECUTION"
END
```
When executed from a file, this program prints the message and terminates.

### B.6 VAR array example
```bas
LET B = #1
LET VAR(0) = VAR(1)
PRINT A
REM "Prints 1"
```
