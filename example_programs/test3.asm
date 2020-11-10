before_interrupt:
    MOV $01, r1
    MOV $02, r2
    PSH $0003

call_interrupt:
    INT $03

mask_interrupt_4:
    MOV $01, r3
    LSF r3, $03
    NOT r3
    AND im, acc
    MOV acc, im

call_interrupt_again:
    INT $03

this_should_run_instead:
    MOV $05, r5

exit:
    HLT