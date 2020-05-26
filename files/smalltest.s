.global l3
.extern l4
.section data:
    ret
    jmp 4
    pushb l1
    push %r5
    mov l1, l3
    .word labela, l1, l3
.section text:
    l3: .byte 254
    l1:.word l3, 20
labela:
.end


