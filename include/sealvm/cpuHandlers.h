#ifndef SEALVM_SEALVM_CPUHANDLERS_H
#define SEALVM_SEALVM_CPUHANDLERS_H

#include <stdbool.h>
#include <stdint.h>

#include "sealvm/cpu.h"

// CPU_movLitReg moves literal value into register e.g.: MOV $1234, r1
bool CPU_movLitReg(CPU* this);

// CPU_movRegReg moves register value into another register e.g.: MOV r1, r2
bool CPU_movRegReg(CPU* this);

// CPU_movRegMem moves register value into memory address e.g.: MOV r1, &ABCD
bool CPU_movRegMem(CPU* this);

// CPU_movMemReg moves value at a memory address into a register e.g.: MOV &ABCD, r1
bool CPU_movMemReg(CPU* this);

// CPU_addRegReg adds register values together, put into Registers::acc e.g.: ADD r1, r2
bool CPU_addRegReg(CPU* this);

// CPU_jneLit jumps to the given address if the given literal is not equal to Registers::acc, e.g.: JNE {literal} {address} | JNE $ABCD &1234
bool CPU_jneLit(CPU* this);

// CPU_pshLit pushes a literal value onto the stack e.g.: PSH $1234
bool CPU_pshLit(CPU* this);

// CPU_pshReg pushes a register value onto the stack e.g.: PSH r1
bool CPU_pshReg(CPU* this);

// CPU_pop takes the value from the stack pointer and places it in the given register e.g.: POP r1
bool CPU_pop(CPU* this);

// CPU_calLit cal's to a literal address e.g.: CAL $ABCD
bool CPU_calLit(CPU* this);

// CPU_calReg cal's to an address held in a register e.g.: CAL r1
bool CPU_calReg(CPU* this);

// CPU_ret returns to the location the immediate prior CAL command was called e.g.: RET
bool CPU_ret(CPU* this);

// CPU_movLitMem moves literal value to memory e.g: MOV $1234 &ABCD
bool CPU_movLitMem(CPU* this);

// CPU_movRegPtrReg moves register pointer to register e.g.: MOV [r1], r2
bool CPU_movRegPtrReg(CPU* this);

// CPU_movLitOffReg moves literal at (literal + register) to register e.g.: MOV $ABCD, r1, r2
bool CPU_movLitOffReg(CPU* this);

// CPU_addLitReg adds literal to register e.g.: ADD $1234, r1
bool CPU_addLitReg(CPU* this);

// CPU_subLitReg substracts literal from register e.g.: SUB $1234, r1
bool CPU_subLitReg(CPU* this);

// CPU_subRegLit subtracts register from literal e.g.: SUB r1, $1234
bool CPU_subRegLit(CPU* this);

// CPU_subRegReg subtracts register from registers e.g.: SUB r1, r2
bool CPU_subRegReg(CPU* this);

// CPU_mulLitReg multiplies a literal by a registers e.g.: MUL $1234, r1
bool CPU_mulLitReg(CPU* this);

// CPU_mulRegReg multiplies a register by a register e.g.: MUL r1, r2
bool CPU_mulRegReg(CPU* this);

// CPU_incReg increments a register by 1 e.g.: INC r1
bool CPU_incReg(CPU* this);

// CPU_decReg decrements a register by 1 e.g.: DEC r1
bool CPU_decReg(CPU* this);

// CPU_lsfRegLit left shifts register by literal (in place) e.g.: LSF r1, $1234
bool CPU_lsfRegLit(CPU* this);

// CPU_lsfRegReg left shifts register by register (in place) e.g.: LSF r1, r2
bool CPU_lsfRegReg(CPU* this);

// CPU_rsfRegLit right shifts register by literal (in place) e.g.: RSF r1, $1234
bool CPU_rsfRegLit(CPU* this);

// CPU_rsfRegReg right shifts register by register (in place) e.g.: RSF r1, r2
bool CPU_rsfRegReg(CPU* this);

// CPU_addRegLit and's register with literal e.g.: AND r1, $1234
bool CPU_andRegLit(CPU* this);

// CPU_andRegReg and's register with register e.g.: AND r1, r2
bool CPU_andRegReg(CPU* this);

// CPU_orRegLit or's register with literal e.g.: OR r1, $1234
bool CPU_orRegLit(CPU* this);

// CPU_orRegReg or's register with register e.g.: OR r1, r2
bool CPU_orRegReg(CPU* this);

// CPU_xorRegLit xor's register with literal e.g.: XOR r1, $1234
bool CPU_xorRegLit(CPU* this);

// CPU_xorRegReg xor register with register e.g.: XOR r1, r2
bool CPU_xorRegReg(CPU* this);

// CPU_not not's (invert) register e.g.: NOT r1
bool CPU_not(CPU* this);

// CPU_jneReg jmp's if register not equal to acc e.g.: JNE r1, &1234
bool CPU_jneReg(CPU* this);

// CPU_jeqReg jmp's if register equal to acc e.g.: JEQ r1, &1234
bool CPU_jeqReg(CPU* this);

// CPU_jmpLit jmp's if literal equal to acc e.g.: JEQ $ABCD, &1234
bool CPU_jeqLit(CPU* this);

// CPU_jltReg jmp's if register less than acc e.g.: JLT r1, &1234
bool CPU_jltReg(CPU* this);

// CPU_jltLit jmp's if literal less than acc e.g.: JLT $ABCD, &1234
bool CPU_jltLit(CPU* this);

// CPU_jgtReg jmp's if register greater than acc e.g.: JGT r1, &1234
bool CPU_jgtReg(CPU* this);

// CPU_jgtLit jmp's if literal greater than acc e.g.: JGT $ABCD, &1234
bool CPU_jgtLit(CPU* this);

// CPU_jleReg jmp's if register less than or equal to acc e.g.: JLE r1, &1234
bool CPU_jleReg(CPU* this);

// CPU_jleLit jmp's if literal less than or equal to acc e.g.: JLE $ABCD, &1234
bool CPU_jleLit(CPU* this);

// CPU_jgeReg jmp's if register greater than or equal to acc e.g.: JGE r1, &1234
bool CPU_jgeReg(CPU* this);

// CPU_jgeLit jmp's if literal greater than or equal to acc e.g.: JGE $ABCD, &1234
bool CPU_jgeLit(CPU* this);

// CPU_int is the interrupt handler for an interrupt vector index call e.g.: INT $3
bool CPU_int(CPU* this);

// CPU_retInt is the return from interrupt handler e.g.: RET_INT
bool CPU_retInt(CPU* this);

#endif // SEALVM_SEALVM_CPUHANDLERS_H
