# Chapter 5. Dynamic Semantics

## 5.1 Execution Model
- Program execution begins when the `RUN` statement is entered.
- Execution starts at the statement with the **lowest positive line number** and proceeds in ascending order of line numbers.
- If execution reaches a line number that has been deleted or does not exist, execution continues at the next higher line number.
- Execution proceeds strictly sequentially unless altered by control flow statements (`IF … THEN`, `GOTO`, `GOSUB`, `RETURN`).
- Execution is **deterministic** and strictly sequential. Concurrency is outside the scope of this specification.

## 5.2 Statement Execution
The runtime effects of each statement are as follows:

- **`LET`**: Evaluates the expression and assigns the result to the specified variable.
- **`PRINT`**: Evaluates each expression in the list and outputs the corresponding ASCII character. String literals are output verbatim. Afterwards, a newline is printed.
- **`INPUT`**: Reads characters from the input stream and assigns their ASCII codes to the listed variables in order. If insufficient input is available, the program aborts.
- **`IF ... THEN`**: Evaluates the relational expression. If true, executes the statement following `THEN`. If false, execution continues with the next line.
- **`GOTO`**: Evaluates the expression to an integer. Execution continues at the statement with the smallest line number greater than or equal to this value. If the result is `0`, execution continues with the next line.
- **`GOSUB`**: Evaluates the expression to an integer. The current line number is pushed onto the call stack. Execution continues at the statement with the smallest line number greater than or equal to this value. If the result is `0`, execution continues with the next line.
- **`RETURN`**: Pops the oldest line number from the call stack and resumes execution at the following line. If the call stack is empty, the program aborts.  
- **`CLEAR`**: Clears the call stack and resets all variables to an undefined state.
- **`RUN`**: Restarts execution from the lowest line number, including any newly entered lines.
- **`END`**: Terminates program execution. All variables are reset to undefined. The interpreter remains active and continues to accept input.
- **`EXIT` / `QUIT`**: Terminates the interpreter session. Variables are discarded. Whether the program text is discarded is implementation‑defined.
- **`REM`**: Has no runtime effect.

## 5.3 Control Flow
- If an `IF` condition evaluates to false, execution continues with the next line.
- `GOTO` and `GOSUB` must evaluate to a positive integer. If the result is negative, the program aborts.
- If the evaluated line number does not exist, execution continues at the next higher line number.
- If the evaluated line number is `0`, execution continues with the next line.

## 5.4 Call Stack
- The call stack is **LIFO (last in, first out)**.
- Each `GOSUB` pushes the current line number onto the stack.
- Each `RETURN` pops the newest line number and resumes execution at the following line.
- Maximum stack depth is not defined; implementations must provide sufficient depth for the specification test suite.
- Stack overflow is undefined behavior.

## 5.5 Program Termination
- Execution terminates normally when the next line number to execute is greater than all line numbers in the program.
- Execution also terminates when an `END` statement is executed. In this case, all variables are reset to undefined, but the interpreter remains active.
- Execution terminates abnormally if a runtime error occurs (see §5.6).
- The interpreter session terminates only when `EXIT` or `QUIT` is executed.
- The interpreter exits both in batch and interactive mode with `0` after a successfull run, else -1 on error

## 5.6 Runtime Errors
- Any runtime error causes **program execution to abort**, but the interpreter session remains active.
- Runtime errors include, but are not limited to:
  - Division by zero.
  - Reading a variable before assignment.
  - Executing `RETURN` with an empty call stack.
  - Insufficient input for an `INPUT` statement.
  - Negative line number in `GOTO` or `GOSUB`.
  - In `Var(e)` expression, the value of `e` is out of bounds of `0...25`.
- Aborting program execution returns control to the interpreter prompt.

## 5.7 Determinism
- Execution of a program of our BASIC dialect is strictly sequential and deterministic.
- No concurrency or nondeterministic behavior is defined by this specification.
