#ifndef SEALVM_SEALVM_INSTRUCTIONS
#define SEALVM_SEALVM_INSTRUCTIONS

namespace SealVM {

// Instructions contains the hex values for all the instructions the CPU supports
enum Instructions {
    MOV_LIT_R1 = 0x10,
    MOV_LIT_R2 = 0x11,
    ADD_REG_REG = 0x12,
};

} // namespace SealVM

#endif // SEALVM_SEALVM_INSTRUCTIONS