# Chapter 1. Introduction and Scope

## 1.1 Name of the Language
The programming language described in this specification is called **BASIC**, Ross Online Solutions flavored.

## 1.2 Purpose and Philosophy
This BASIC dialect was created as an experimental dialect of BASIC with the dual purpose of:
- Exploring interpreter construction techniques in C++.
- Providing a retro‑style programming environment inspired by early microcomputer BASICs.

The guiding principles of the language are:
- **Simplicity**: The language design favors clarity and ease of understanding.
- **Minimalism**: Only essential constructs are included, avoiding unnecessary complexity.
- **Experimental usage**: The language serves as a platform for experimentation in both language design and interpreter implementation.

## 1.3 Intended Audience
This specification is intended for:
- **Implementors**, who wish to build interpreters or compilers for our BASIC dialect.
- **Testers**, who require a precise definition of the language for specification‑based testing.
- **Users**, who seek a formal description of the language’s syntax and semantics.

## 1.4 Scope of the Specification
This specification defines:
- The **lexical structure** of our BASIC dialect's programs.
- The **syntax** of the language, expressed in a formal grammar.
- The **semantics** of language constructs.
- The **execution model** governing program behavior.

This specification does **not** define:
- Implementation details of interpreters or compilers.
- Performance characteristics or resource usage.
- Platform‑specific extensions or behaviors.

## 1.5 Relationship to Other Languages
Our BASIC dialect is inspired by **Tiny BASIC**, as described in publicly available sources. While it shares the minimalist spirit of Tiny BASIC, Our BASIC dialect is defined independently and without a requirement for compatibility.

## 1.6 Conformance
An implementation of our BASIC dialect is said to **conform** to this specification if:
- It implements all features described herein.
- It passes the system test suite derived from this specification.
- It may provide extensions, provided that such extensions do not cause any program conforming to this specification to fail the conformance tests.

## 1.7 Structure of this Specification
The remainder of this specification is organized as follows:

- [Chapter 2. Lexical Structure](02-lexical-structure.md)
- [Chapter 3. Syntax and Grammar](03-syntax-and-grammar.md)
- [Chapter 4. Static Semantics](04-static-semantics.md)
- [Chapter 5. Dynamic Semantics](05-dynamic-semantics.md)
- [Chapter 6. Conformance](06-conformance.md)
- [Appendices](appendices.md)

Each chapter is normative unless explicitly marked otherwise. Examples and explanatory notes are informative and do not form part of the normative specification.
