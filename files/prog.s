iret
halt
push $56
pop simbol
pop %r5
push (%r7)
pop %r5l
pop %r5h
push (%r2)
jmp *%r2
call labela
jmp 54
jeq *54
jne *(%r6)
jgt *simbol(%r2)
jgt *simbol(%pc)
jgt *54(%r4)
pushw %r1
add 54, %r2
mul %r4, 54(%r3)
div simbol(%r5), simbol(%r5)
or $543, 54