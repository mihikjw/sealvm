#ifndef SEALVM_SEALVM_REGISTERS_H
#define SEALVM_SEALVM_REGISTERS_H

#include "sealvm/defines.h"

// Registers contains the hex values for all the register names in the CPU
typedef enum Registers {
    pc = 0x00, // program counter
    r1 = 0x01,
    r2 = 0x02,
    r3 = 0x03,
    r4 = 0x04,
    r5 = 0x05,
    r6 = 0x06,
    r7 = 0x07,
    r8 = 0x08,
    acc = 0x09, // accumulator
    sp = 0x0A,  // stack pointer
    fp = 0x0B,  // frame pointer
    im = 0x0C,  // interrupt mask
} Registers;

#endif // SEALVM_SEALVM_REGISTERS_H
