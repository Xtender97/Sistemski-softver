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

.end
         
.section text: 

lonelyLabel:

labela: .word 2, 3, simbol
.global simbol1 , simbol2
.extern simbol
.equ simbol, 2+3-4
.skip 100


int *SIMBOL(%pc) 
int *55(%pc)    
int *55(%r7)  
int *55(%r6)
int *sim(%r6)
int 55
int *55  
call simbol
jmp *%r4
jgt *(%r8)
jgt *(%r7)
jne $sd

mov %r5, %r3
add 44, %r5
sub $simbol, simbol2
mul simbol, %(r4)
div $5, %pc
div $1231, (%pc)
xchg 123, simbol(%pc)
xchg 123, 4(%pc)
xor 5%r5, a(r4)
xor 5(%r5), a(r4)