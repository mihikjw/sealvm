#ifndef SEALVM_SEALVM_INSTRUCTIONS
#define SEALVM_SEALVM_INSTRUCTIONS

namespace SealVM {

// Instructions contains the hex values for all the instructions the CPU supports
enum Instructions {
    MOV_LIT_REG = 0x10, // MOV 0x1234, r1
    MOV_REG_REG = 0x11, // MOV r1, r2
    MOV_REG_MEM = 0x12, // MOV r1, 0xABCD
    MOV_MEM_REG = 0x13, // MOV 0xABCD, r1
    ADD_REG_REG = 0x14, // ADD r1, r2
    JMP_NOT_EQ = 0x15,  // JNE 0xABCD, 0x1234
};

} // namespace SealVM

#endif // SEALVM_SEALVM_INSTRUCTIONS