start:
    MOV $0A, &0050
loop:
    MOV &0050, acc
    DEC acc
    MOV acc, &0050
    INC r2
    INC r2
    INC r2
    JNE $00, &[ !loop ]
end:
    HLT