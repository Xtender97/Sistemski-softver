.global l1, l3
.extern l4
.section data:
    labela: .word 255, 3
    .byte 34, 5
    .word labela, l1, l3
.section text:
    l3: .byte 254
    .word l3, 20
.end


