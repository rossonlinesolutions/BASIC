# Chapter 6. Conformance

## 6.1 Definition of Conformance
An implementation of **BASIC, Ross Online Solution flavored 1.0.0** is said to conform to this specification if:

- It implements all features described in this document.
- It executes all conforming programs in a manner consistent with this specification.
- It does not alter the behavior of conforming programs.
- It may provide extensions, provided that such extensions do not conflict with this specification and do not cause conforming programs to fail.

## 6.2 Extensions
- Extensions to the language are permitted. Examples include additional statements, operators, or support for lowercase identifiers.
- Conforming programs must behave identically on all conforming implementations, regardless of extensions.
- Extensions must not interfere with the execution of conforming programs or cause them to fail the conformance test suite.

## 6.3 Undefined Behavior
- Certain constructs are explicitly defined as **undefined behavior** (see Appendix A).
- In cases of undefined behavior, the interpreter may choose any behavior, including continuing execution, aborting execution, or producing arbitrary results.
- Undefined behavior does not affect conformance.
- Undefined behavior is not required to abort execution.

## 6.4 Testing and Validation
- Conformance is not defined solely by passing the reference test suite.
- However, passing the test suite is a **sufficient indication** of conformance.
- Failure to pass the test suite is a strong indication of non‑conformance.
- In cases of doubt, this specification and the reference implementation serve as the authoritative basis for determining conformance.
- Testing demonstrates the presence of conformance, not the absence of defects.

## 6.5 Error Handling
- Runtime errors must abort program execution but must not terminate the interpreter session.
- Examples of runtime errors include division by zero, invalid input, or executing `RETURN` with an empty call stack.
- Memory leaks, interpreter crashes, or uncontrolled termination (e.g., segmentation faults) are **illegal** and render an implementation non‑conforming.
- Division by zero is explicitly defined as a runtime error that aborts execution.

## 6.6 Interpreter Behavior
- A conforming implementation must support interactive entry of lines and execution via the `RUN` statement.
- Batch execution from a file is permitted but not required.
- End‑of‑file in a source file is treated as if an `EXIT` statement were encountered.
- The execution model is otherwise identical between interactive and batch modes.
- No minimum requirements for input/output handling are specified in this chapter.

## 6.7 Versioning
- This specification defines **BASIC, Ross Online Solution flavored 1.0.0**.
- Conforming implementations must state the version of the specification to which they conform.

## 6.8 Compliance Checklist
The following checklist provides a summary of requirements for conformance:

- [ ] Implements all features described in this specification.
- [ ] Executes conforming programs identically to the reference implementation.
- [ ] Supports interactive entry of lines and execution via `RUN`.
- [ ] Treats EOF in batch mode as `EXIT`.
- [ ] Aborts program execution on runtime errors without terminating the interpreter session.
- [ ] Does not crash or leak memory on runtime errors.
- [ ] Handles undefined behavior in any manner without affecting conformance.
- [ ] May provide extensions, but conforming programs must remain unaffected.
- [ ] States the version of the specification it conforms to (BASIC, Ross Online Solution flavored 1.0.0).
