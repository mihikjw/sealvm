#ifndef SEALVM_SEALVM_INSTRUCTIONS_HPP
#define SEALVM_SEALVM_INSTRUCTIONS_HPP

#include <cstdint>

namespace SealVM {

// Instructions contains the hex value opcodes for all the instructions the CPU supports
enum Instructions {

    // move values
    MOV_LIT_REG = 0x10,     // MOV $1234, r1
    MOV_REG_REG = 0x11,     // MOV r1, r2
    MOV_REG_MEM = 0x12,     // MOV r1, &ABCD
    MOV_MEM_REG = 0x13,     // MOV &ABCD, r1
    MOV_LIT_MEM = 0x1D,     // MOV $1234 &ABCD
    MOV_REG_PTR_REG = 0x1E, // MOV r1, r2
    MOV_LIT_OFF_REG = 0x1F, // MOV $ABCD, r1, r2

    // arithmetic
    ADD_REG_REG = 0x14, // ADD r1, r2
    ADD_LIT_REG = 0x20, // ADD $1234, r1
    SUB_LIT_REG = 0x21, // SUB $1234, r1
    SUB_REG_LIT = 0x22, // SUB r1, $1234
    SUB_REG_REG = 0x23, // SUB r1, r2
    INC_REG = 0x24,     // INC r1
    DEC_REG = 0x25,     // DEC r1
    MUL_LIT_REG = 0x26, // MUL $1234, r1               TODO: add support for signed value multiplication
    MUL_REG_REG = 0x27, // MUL r1, r2                   TODO: add support for signed value multiplication

    // logical
    LSF_REG_LIT = 0x28, // LSF r1, $1234
    LSF_REG_REG = 0x29, // LSF r1, r2
    RSF_REG_LIT = 0x2A, // RSF r1, $1234
    RSF_REG_REG = 0x2B, // RSF r1, r2
    AND_REG_LIT = 0x2C, // AND r1, $1234
    AND_REG_REG = 0x2D, // AND r1, r2
    OR_REG_LIT = 0x2E,  // OR r1, $1234
    OR_REG_REG = 0x2F,  // OR r1, r2
    XOR_REG_LIT = 0x30, // XOR r1, $1234
    XOR_REG_REG = 0x31, // XOR r1, r2
    NOT = 0x32,         // NOT r1

    // branching
    JNE_LIT = 0x15, // JNE $ABCD, &1234
    JNE_REG = 0x33, // JNE r1, &1234
    JEQ_REG = 0x34, // JEQ r1, &1234
    JEQ_LIT = 0x35, // JEQ $ABCD &1234
    JLT_REG = 0x36, // JLT r1, &1234
    JLT_LIT = 0x37, // JLT $0xABCD, &1234
    JGT_REG = 0x38, // JGT r1, &1234
    JGT_LIT = 0x39, // JGT $ABCD, &1234
    JLE_REG = 0x3A, // JLE r1, &1234
    JLE_LIT = 0x3B, // JLE $ABCD, &1234
    JGE_REG = 0x3C, // JGE r1, &1234
    JGE_LIT = 0x3D, // JGE $ABCD, &1234

    PSH_LIT = 0x16, // PSH $ABCD
    PSH_REG = 0x17, // PSH r1
    POP = 0x18,     // POP r1
    CAL_LIT = 0x19, // CAL $ABCD
    CAL_REG = 0x1A, // CAL r1
    RET = 0x1B,     // RET
    HLT = 0x1C,     // HLT
    INT = 0x3E,     // INT &15F6
    RET_INT = 0x3F  // RET_INT
};

// Instruction contains more details about each instruction, required by compilers etc
namespace Instruction {

// Type groups instructions by their supported ASM modes (i.e. MOV_LIT_REG and ADD_LIT_REG are the same type)
enum Type {
    LIT_REG = 0,
    REG_LIT,
    REG_LIT_8,
    REG_REG,
    REG_MEM,
    MEM_REG,
    LIT_MEM,
    REG_PTR_REG,
    LIT_OFF_REG,
    NO_ARGS,
    SINGLE_REG,
    SINGLE_LIT,
};

// Sizes of instruction groups defined here
uint8_t LitReg = 4;
uint8_t RegLit = 4;
uint8_t RegLit8 = 3;
uint8_t RegReg = 3;
uint8_t RegMem = 4;
uint8_t MemReg = 4;
uint8_t LitMem = 5;
uint8_t RegPtrReg = 3;
uint8_t LitOffReg = 5;
uint8_t NoArgs = 1;
uint8_t SingleReg = 2;
uint8_t SingleLit = 3;

// Mnemonic contains values used to group instructions by their Mnemonic (i.e. MOV_LIT_REG and MOV_REG_REG are the same 'MOV' mnemonic)
enum Mnemonic {
    MOV = 0,
    ADD,
    SUB,
    INC,
    DEC,
    MUL,
    LSF,
    RSF,
    AND,
    OR,
    XOR,
    NOT,
    JNE,
    JEQ,
    JLT,
    JGT,
    JLE,
    JGE,
    PSH,
    POP,
    CAL,
    RET,
    HTL,
    INT,
    RET_INT,
};

} // namespace Instruction

} // namespace SealVM

#endif // SEALVM_SEALVM_INSTRUCTIONS_HPP