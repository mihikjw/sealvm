#ifndef SEALVM_SEALVM_INSTRUCTIONS
#define SEALVM_SEALVM_INSTRUCTIONS

namespace SealVM {

// Instructions contains the hex values for all the instructions the CPU supports
enum Instructions {
    MOV_LIT_REG = 0x10,
    MOV_REG_REG = 0x11,
    MOV_REG_MEM = 0x12,
    MOV_MEM_REG = 0x13,
    ADD_REG_REG = 0x14,
};

} // namespace SealVM

#endif // SEALVM_SEALVM_INSTRUCTIONS