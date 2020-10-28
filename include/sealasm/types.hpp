#ifndef SEALVM_SEALASM_TYPES_HPP
#define SEALVM_SEALASM_TYPES_HPP

// TODO: Refactor this file

#include <map>
#include <string>
#include <vector>

#include "sealvm/instructions.hpp"

namespace SealASM {

// Operators represents the supported ASM operators
enum Operators {
    OP_PLUS,
    OP_MINUS,
    OP_MULTIPLY,
};

// InstructionArg represents the arguments for an ASM instruction
struct InstructionArg {
    public:
    InstructionArg(const std::string& src) { Str = src; }
    InstructionArg(const std::vector<std::string>& src) { Vec = src; }
    std::string Str;
    std::vector<std::string> Vec;
};

// OperationType defines a type of operation in the assembler language
enum OperationType {
    INSTRUCTION,
};

// Instruction defines an instruction to make, and any arguments it requires
struct Instruction {
    public:
    SealVM::Instructions Type;
    std::map<std::string, InstructionArg> Args;
};

// ASMStateResult is the result of parsing an ASM line
struct ASMStateResult {
    public:
    OperationType Type;
    Instruction Ins;
};

} // namespace SealASM

#endif // SEALVM_SEALASM_TYPES_HPP