10 GOTO 100

20 REM "modulo 10 function, input P, return in P"
IF P < 10 THEN RETURN
LET P = P - 10
GOSUB 20
RETURN

100 REM "Start execution"
LET A = 0
LET B = 0

INPUT X
LET P = X

REM "Get in P the input modulo 10 and put it in B"
GOSUB 20
LET B = P

REM "Get in P the input / 10 modulo 10 and put it in A"
LET P = X / 10
GOSUB 20
LET A = P

REM "Now add ascii 0 and print the number"
LET A = A + #0
LET B = B + #0

PRINT A, B
END

REM "Run four times"
RUN
RUN
RUN
RUN
