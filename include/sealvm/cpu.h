#ifndef SEALVM_SEALVM_CPU_H
#define SEALVM_SEALVM_CPU_H

#include <stdbool.h>
#include <stdint.h>

#include "sealvm/errors.h"
#include "sealvm/memoryMapper.h"
#include "sealvm/registerStore.h"
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
    uint16_t _stackFrameSize;

    // _registers contains the storage for registers
    RegisterStore* _registers;
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

// CPU_pushStack pushes the given value onto the stack - designed for internal use only
ErrCode CPU_pushStack(CPU* this, const uint16_t value);
// CPU_pushRegisterStack pushes the value held in the given register onto the stack - designed for internal use only
ErrCode CPU_pushRegisterStack(CPU* this, const Registers reg);
// CPU_popStack pops a value off the stack, puts it in `output` arg ptr - designed for internal use only
ErrCode CPU_popStack(CPU* this, uint16_t* output);
// CPU_pushStackStack push's all current CPU state to the head of the stack - designed for internal use only
ErrCode CPU_pushStateStack(CPU* this);
// CPU_popStateStack returns the CPU to a state stored on the head of the stack - designed for internal use only
ErrCode CPU_popStateStack(CPU* this);
// CPU_popRegisterStack pops the current stack head value into the given register - designed for internal use only
ErrCode CPU_popRegisterStack(CPU* this, const Registers reg);

// CPU_handleInterrupt is a generic interrupt handler function
ErrCode CPU_handleInterrupt(CPU* this, const uint16_t vectorIndex);

#endif // SEALVM_SEALVM_CPU_H
