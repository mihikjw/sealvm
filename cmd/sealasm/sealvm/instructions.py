
class Instructions():
    "contains the instruction opcodes"
    # mov
    MOV_LIT_REG: int = 0x10
    MOV_REG_REG: int = 0x11
    MOV_REG_MEM: int = 0x12
    MOV_MEM_REG: int = 0x13
    MOV_LIT_MEM: int = 0x1D
    MOV_REG_PTR_REG: int = 0x1E
    MOV_LIT_OFF_REG: int = 0x1F

    # arithmetic
    ADD_REG_REG: int = 0x14
    ADD_LIT_REG: int = 0x20
    SUB_LIT_REG: int = 0x21
    SUB_REG_LIT: int = 0x22
    SUB_REG_REG: int = 0x23
    INC_REG: int = 0x24
    DEC_REG: int = 0x25
    MUL_LIT_REG: int = 0x26
    MUL_REG_REG: int = 0x27

    # logical
    LSF_REG_LIT: int = 0x28
    LSF_REG_REG: int = 0x29
    RSF_REG_LIT: int = 0x2A
    RSF_REG_REG: int = 0x2B
    AND_REG_LIT: int = 0x2C
    AND_REG_REG: int = 0x2D
    OR_REG_LIT: int = 0x2E
    OR_REG_REG: int = 0x2F
    XOR_REG_LIT: int = 0x30
    XOR_REG_REG: int = 0x31
    NOT: int = 0x32

    # branching
    JMP_NOT_EQ:  int = 0x15
    JNE_REG: int = 0x33
    JEQ_REG: int = 0x34
    JEQ_LIT: int = 0x35
    JLT_REG: int = 0x36
    JLT_LIT: int = 0x37
    JGT_REG: int = 0x38
    JGT_LIT: int = 0x39
    JLE_REG: int = 0x3A
    JLE_LIT: int = 0x3B
    JGE_REG: int = 0x3C
    JGE_LIT: int = 0x3D

    # misc
    PSH_LIT: int = 0x16
    PSH_REG: int = 0x17
    POP: int = 0x18
    CAL_LIT: int = 0x19
    CAL_REG: int = 0x1A
    RET: int = 0x1B
    HLT: int = 0x1C


class Type():
    "contains the type groups for instructions, e.g. MOV_LIT_REG and ADD_LIT_REG are the same instruction type group"
    LIT_REG: int = 0
    REG_LIT: int = 1
    REG_LIT_8: int = 2
    REG_REG: int = 3
    REG_MEM: int = 4
    MEM_REG: int = 5
    LIT_MEM: int = 6
    REG_PTR_REG: int = 7
    LIT_OFF_REG: int = 8
    NO_ARGS: int = 9
    SINGLE_REG: int = 10
    SINGLE_LIT: int = 11


class Size():
    "contains the instruction sizes for the type"
    LIT_REG: int = 4
    REG_LIT: int = 4
    REG_LIT_8: int = 3
    REG_REG: int = 3
    REG_MEM: int = 4
    MEM_REG: int = 4
    LIT_MEM: int = 5
    REG_PTR_REG: int = 3
    LIT_OFF_REG: int = 5
    NO_ARGS: int = 1
    SINGLE_REG: int = 2
    SINGLE_LIT: int = 3


class Mnemonic():
    "contains instruction types to group instructions, i.e. MOV_REG_LIT and MOV_REG_REG are the same 'MOV' group"
    MOV: int = 0
    ADD: int = 1
    SUB: int = 2
    INC: int = 3
    DEC: int = 4
    MUL: int = 5
    LSF: int = 6
    RSF: int = 7
    AND: int = 8
    OR: int = 9
    XOR: int = 10
    NOT: int = 11
    JNE: int = 12
    JEQ: int = 13
    JLT: int = 14
    JGT: int = 15
    JLE: int = 16
    JGE: int = 17
    PSH: int = 18
    POP: int = 19
    CAL: int = 20
    RET: int = 21
    HLT: int = 22
