#ifndef SEALVM_SEALASM_TYPES_HPP
#define SEALVM_SEALASM_TYPES_HPP

#include <map>
#include <string>

#include "sealvm/instructions.hpp"

namespace SealASM {

// OperationType defines a type of operation in the assembler language
enum OperationType {
    INSTRUCTION,
};

// Instruction defines an instruction to make, and any arguments it requires
struct Instruction {
    public:
    SealVM::Instructions Type;
    std::map<std::string, std::string> Args;
};

// ASMStateResult is the result of parsing an ASM line
struct ASMStateResult {
    public:
    OperationType Type;
    Instruction Ins;
};

} // namespace SealASM

#endif // SEALVM_SEALASM_TYPES_HPP