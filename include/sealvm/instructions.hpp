#ifndef SEALVM_SEALVM_INSTRUCTIONS
#define SEALVM_SEALVM_INSTRUCTIONS

namespace SealVM {

// Instructions contains the hex values for all the instructions the CPU supports
enum Instructions {

    // move values
    MOV_LIT_REG = 0x10,     // MOV 0x1234, r1
    MOV_REG_REG = 0x11,     // MOV r1, r2
    MOV_REG_MEM = 0x12,     // MOV r1, #0xABCD
    MOV_MEM_REG = 0x13,     // MOV #0xABCD, r1
    MOV_LIT_MEM = 0x1D,     // MOV 0x1234 #0xABCD
    MOV_REG_PTR_REG = 0x1E, // MOV r1, r2
    MOV_LIT_OFF_REG = 0x1F, // MOV #0xABCD, r1, r2

    // arithmetic
    ADD_REG_REG = 0x14,     // ADD r1, r2
    ADD_LIT_REG = 0x20,     // ADD 0x1234, r1
    SUB_LIT_REG = 0x21,     // SUB 0x1234, r1
    SUB_REG_LIT = 0x22,     // SUB r1, 0x1234
    SUB_REG_REG = 0x23,     // SUB r1, r2
    INC_REG = 0x24,         // INC r1
    DEC_REG = 0x25,         // DEC r1
    MUL_LIT_REG = 0x26,     // MUL 0x1234, r1               TODO: add support for signed value multiplication
    MUL_REG_REG = 0x27,     // MUL r1, r2                   TODO: add support for signed value multiplication

    // logical
    LSF_REG_LIT = 0x28,     // LSF r1, 0x1234
    LSF_REG_REG = 0x29,     // LSF r1, r2
    RSF_REG_LIT = 0x2A,     // RSF r1, 0x1234
    RSF_REG_REG = 0x2B,     // RSF r1, r2
    AND_REG_LIT = 0x2C,     // AND r1, 0x1234
    AND_REG_REG = 0x2D,     // AND r1, r2
    OR_REG_LIT = 0x2E,      // OR r1, 0x1234
    OR_REG_REG = 0x2F,      // OR r1, r2
    XOR_REG_LIT = 0x30,     // XOR r1, 0x1234
    XOR_REG_REG = 0x31,     // XOR r1, r2
    NOT = 0x32,             // NOT r1

    // branching
    JMP_NOT_EQ = 0x15,      // JNE 0xABCD, #0x1234
    JNE_REG = 0x33,         // JNE r1, #0x1234
    JEQ_REG = 0x34,         // JEQ r1, #0x1234
    JEQ_LIT = 0x35,         // JEQ 0xABCD #0x1234
    JLT_REG = 0x36,         // JLT r1, #0x1234
    JLT_LIT = 0x37,         // JLT 0xABCD, #0x1234
    JGT_REG = 0x38,         // JGT r1, #0x1234
    JGT_LIT = 0x39,         // JGT 0xABCD, #0x1234
    JLE_REG = 0x3A,         // JLE r1, #0x1234
    JLE_LIT = 0x3B,         // JLE 0xABCD, #0x1234
    JGE_REG = 0x3C,         // JGE r1, #0x1234
    JGE_LIT = 0x3D,         // JGE 0xABCD, #0x1234

    PSH_LIT = 0x16,         // PSH 0xABCD
    PSH_REG = 0x17,         // PSH r1
    POP = 0x18,             // POP r1
    CAL_LIT = 0x19,         // CAL 0xABCD
    CAL_REG = 0x1A,         // CAL r1
    RET = 0x1B,             // RET
    HLT = 0x1C,             // HLT
};

} // namespace SealVM

#endif // SEALVM_SEALVM_INSTRUCTIONS