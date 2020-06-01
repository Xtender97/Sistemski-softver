.global l3
.extern l4, l5

.equ const,  4- 6 -8 +10
.equ text_reloc, 10 + l1
.equ data_reloc, 10 + labela
.equ apsolut, l1-l3
.equ error, l1 + labela
.equ extern_err, l4 - l5
.equ extern, l4 + 4

.section data:
    mov l1(%pc), 5
    mov 5, l1(%pc)
    jmp *l1(%pc)
    movw $2, (%r4)
    .byte labela, l1, l3, l4
    labela:.word labela, l1, l3, l4, 15
.section text:
    push (%r2)
    l1: .byte 150
    l3:.word l3, 20
.end

