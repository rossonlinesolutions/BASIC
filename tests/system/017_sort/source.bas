10 REM "Read all variables except A and B"

LET A = 2

20 IF A = 26 THEN GOTO 100
INPUT VAR(A)
LET A = A + 1
GOTO 20

100 REM "Now sort them"

LET A = 2

110 IF A = 25 THEN GOTO 200
LET A = A + 1
IF VAR(A - 1) <= VAR(A) THEN GOTO 110

REM "Swap A-1 and A"
LET B = VAR(A - 1)
LET VAR(A - 1) = VAR(A)
LET VAR(A) = B

REM "Start new"
LET A = 2
GOTO 110

200 REM "Print all variables in ascending order"
LET A = 2

210 IF A = 26 THEN END
PRINT VAR(A)
LET A = A + 1
GOTO 210

RUN
