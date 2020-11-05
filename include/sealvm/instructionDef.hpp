#ifndef SEALVM_SEALVM_INSTRUCTIONDEF_HPP
#define SEALVM_SEALVM_INSTRUCTIONDEF_HPP

#include <cstdint>
#include <string>

#include "sealvm/instructions.hpp"

namespace SealVM {

// InstructionDef defines an instruction with supporting data
class InstructionDef {
    public:
    // OpCode holds the opcode for the instruction
    Instructions OpCode;

    // Size holds the size of the instruction in bytes
    uint8_t Size;

    // Type holds the ASM type of the instruction
    Instruction::Type Type;

    // Mnemonic holds the instruction mnemonic
    Instruction::Mnemonic Mnemonic;
};

} // namespace SealVM

#endif // SEALVM_SEALVM_INSTRUCTIONDEF_HPP