#ifndef SEALVM_SEALVM_INSTRUCTIONMAP_HPP
#define SEALVM_SEALVM_INSTRUCTIONMAP_HPP

#include <map>
#include <string>

#include "sealvm-cpp/instructionDef.hpp"
#include "sealvm-cpp/instructions.hpp"

namespace SealVM {
namespace Instruction {

// Map contains a mapping of string to a more detailed InstructionDef object
std::map<std::string, InstructionDef> Map{
  {"MOV_LIT_REG", {MOV_LIT_REG, LitReg, LIT_REG, MOV}},
  {"MOV_REG_REG", {MOV_REG_REG, RegReg, REG_REG, MOV}},
  {"MOV_REG_MEM", {MOV_REG_MEM, RegMem, REG_MEM, MOV}},
  {"MOV_MEM_REG", {MOV_MEM_REG, MemReg, MEM_REG, MOV}},
  {"MOV_LIT_MEM", {MOV_LIT_MEM, LitMem, LIT_MEM, MOV}},
  {"MOV_REG_PTR_REG", {MOV_REG_PTR_REG, RegPtrReg, RegPtrReg, MOV}},
  {"MOV_LIT_OFF_REG", {MOV_LIT_OFF_REG, LitOffReg, LIT_OFF_REG, MOV}},

  {"ADD_REG_REG", {ADD_REG_REG, RegReg, REG_REG, ADD}},
  {"ADD_LIT_REG", {ADD_LIT_REG, LitReg, LIT_REG, ADD}},
  {"SUB_LIT_REG", {SUB_LIT_REG, LitReg, LIT_REG, SUB}},
  {"SUB_REG_LIT", {SUB_REG_LIT, RegLit, REG_LIT, SUB}},
  {"SUB_REG_REG", {SUB_REG_REG, RegReg, REG_REG, SUB}},
  {"INC_REG", {INC_REG, SingleReg, SINGLE_REG, INC}},
  {"DEC_REG", {DEC_REG, SingleReg, SINGLE_REG, DEC}},
  {"MUL_LIT_REG", {MUL_LIT_REG, LitReg, LIT_REG, MUL}},
  {"MUL_REG_REG", {MUL_REG_REG, RegReg, REG_REG, MUL}},

  {"LSF_REG_LIT", {LSF_REG_LIT, RegLit, REG_LIT, LSF}},
  {"LSF_REG_REG", {LSF_REG_REG, RegReg, REG_REG, LSF}},
  {"RSF_REG_LIT", {RSF_REG_LIT, RegLit, REG_LIT, RSF}},
  {"RSF_REG_REG", {RSF_REG_REG, RegReg, REG_REG, RSF}},
  {"AND_REG_LIT", {AND_REG_LIT, RegLit, REG_LIT, AND}},
  {"AND_REG_REG", {AND_REG_REG, RegReg, REG_REG, AND}},
  {"OR_REG_LIT", {OR_REG_LIT, RegLit, REG_LIT, OR}},
  {"OR_REG_REG", {OR_REG_REG, RegReg, REG_REG, OR}},
  {"XOR_REG_LIT", {XOR_REG_LIT, RegLit, REG_LIT, XOR}},
  {"XOR_REG_REG", {XOR_REG_REG, RegReg, REG_REG, XOR}},
  {"NOT", {NOT, SingleReg, SINGLE_REG, NOT}},

  {"JMP_NOT_EQ", {JMP_NOT_EQ, LitMem, LIT_MEM, JNE}},
  {"JNE_REG", {JNE_REG, RegMem, REG_MEM, JNE}},
  {"JEQ_REG", {JEQ_REG, RegMem, REG_MEM, JEQ}},
  {"JEQ_LIT", {JEQ_LIT, LitMem, LIT_MEM, JEQ}},
  {"JLT_REG", {JLT_REG, RegMem, REG_MEM, JLT}},
  {"JLT_LIT", {JLT_LIT, LitMem, LIT_MEM, JLT}},
  {"JGT_REG", {JGT_REG, RegMem, REG_MEM, JGT}},
  {"JGT_LIT", {JGT_LIT, LitMem, LIT_MEM, JGT}},
  {"JLE_REG", {JLE_REG, RegMem, REG_MEM, JLE}},
  {"JLE_LIT", {JLE_LIT, LitMem, LIT_MEM, JLE}},
  {"JGE_REG", {JGE_REG, RegMem, REG_MEM, JGE}},
  {"JGE_LIT", {JGE_LIT, LitMem, LIT_MEM, JGE}},

  {"PSH_LIT", {PSH_LIT, SingleLit, SINGLE_LIT, PSH}},
  {"PSH_REG", {PSH_REG, SingleReg, SINGLE_REG, PSH}},
  {"POP", {POP, SingleReg, SINGLE_REG, POP}},
  {"CAL_LIT", {CAL_LIT, SingleLit, SINGLE_LIT, CAL}},
  {"CAL_REG", {CAL_REG, SingleReg, SINGLE_REG, CAL}},
  {"RET", {RET, NoArgs, NO_ARGS, RET}},
  {"HLT", {HLT, NoArgs, NO_ARGS, HLT}},
};

} // namespace Instruction
} // namespace SealVM

#endif // SEALVM_SEALVM_INSTRUCTIONMAP_HPP