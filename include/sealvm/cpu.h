#ifndef SEALVM_SEALVM_CPU_H
#define SEALVM_SEALVM_CPU_H

#include <stdbool.h>
#include <stdint.h>

#include "sealvm/errors.h"
#include "sealvm/memoryMapper.h"
#include "sealvm/registerMap.h"
#include "sealvm/registers.h"

// CPU represents the Central Processing Unit of the VM
typedef struct CPU {

    // Run executes the program loaded at address ZERO_MEMORY, exits on HLT instruction
    void (*Run)(struct CPU*);

    // Cycle gets the next instruction & executes it, returns whether its the last instruction or not
    bool (*Cycle)(struct CPU*);

    // GetRegister sets the `valueOut` field to the value held in register `reg`
    ErrCode (*GetRegister)(struct CPU*, const Registers reg, uint16_t* valueOut);

    // SetRegister sets the register `reg` to the value `value`
    ErrCode (*SetRegister)(struct CPU*, const Registers reg, const uint16_t value);

    // _memory is the interface to the VM memory
    MemoryMapper* _memory;
    // _interruptVectorAddr contains the start address of the interrupt vector in memory
    uint16_t _interruptVectorAddr;

    // _isInInterrupt is an internal flag indicating whether we are in an interrupt or not
    bool _isInInterrupt;

    // _stackFrameSize tracks the size of the stack - could be used in a register but I don't want this to be user accessable
    uint8_t _stackFrameSize;

    // _registers contains a map of {register: value}
    RegisterMap* _registers;
} CPU;

// NewCPU is a constructor for a CPU object
CPU* NewCPU(MemoryMapper* memory, const uint16_t interruptVectorAddr);

// CPU_fetch returns the next 8-bits from memory - designed for internal use only
ErrCode CPU_fetch(CPU* this, uint8_t* output);
// CPU_fetch16 returns the next 16-bits from memory - designed for internal use only
ErrCode CPU_fetch16(CPU* this, uint16_t* output);
// CPU_fetchRegisterIndex returns the next register literal from memory - designed for internal use only
ErrCode CPU_fetchRegisterIndex(CPU* this, Registers* output);
// CPU_execute executes the given instruction - designed for internal use only
bool CPU_execute(CPU* this, uint8_t instruction);

#endif // SEALVM_SEALVM_CPU_H
