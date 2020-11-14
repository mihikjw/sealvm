#include "sealvm/cpu.h"

#include <stdlib.h>

#include "sealvm/defines.h"
#include "sealvm/instructions.h"

ErrCode CPU_GetRegister(CPU* this, Registers reg, uint16_t* valueOut);
ErrCode CPU_SetRegister(CPU* this, Registers reg, uint16_t value);
void CPU_Run(CPU* this);
bool CPU_Cycle(CPU* this);

// CPU_fetch returns the next 8-bits from memory
ErrCode CPU_fetch(CPU* this, uint8_t* output);
// CPU_fetch16 returns the next 16-bits from memory
ErrCode CPU_fetch16(CPU* this, uint16_t* output);
// CPU_fetchRegisterIndex returns the next register literal from memory
ErrCode CPU_fetchRegisterIndex(CPU* this, Registers* output);
// CPU_execute executes the given instruction
bool CPU_execute(CPU* this, uint8_t instruction);

// ------------------------------------
// instruction handlers, pretty self explanatory
// ------------------------------------
bool CPU_mov_lit_reg(CPU* this);
// ------------------------------------

CPU* NewCPU(MemoryMapper* memory, const uint16_t interruptVectorAddr) {
    if (!memory || interruptVectorAddr > MEMORY_SIZE) {
        return NULL;
    }

    CPU* result = malloc(sizeof(CPU));
    if (!result) {
        return NULL;
    }

    result->_isInInterrupt = false;
    result->_stackFrameSize = 0;
    result->_interruptVectorAddr = interruptVectorAddr;
    result->_memory = memory;
    result->SetRegister = &CPU_SetRegister;
    result->GetRegister = &CPU_GetRegister;
    result->Run = &CPU_Run;
    result->Cycle = &CPU_Cycle;

    result->_registers = NewRegisterMap(REGISTER_COUNT);
    result->_registers->Set(result->_registers, pc, ZERO_MEMORY);
    result->_registers->Set(result->_registers, r1, ZERO_MEMORY);
    result->_registers->Set(result->_registers, r2, ZERO_MEMORY);
    result->_registers->Set(result->_registers, r3, ZERO_MEMORY);
    result->_registers->Set(result->_registers, r4, ZERO_MEMORY);
    result->_registers->Set(result->_registers, r5, ZERO_MEMORY);
    result->_registers->Set(result->_registers, r6, ZERO_MEMORY);
    result->_registers->Set(result->_registers, r7, ZERO_MEMORY);
    result->_registers->Set(result->_registers, r8, ZERO_MEMORY);
    result->_registers->Set(result->_registers, acc, ZERO_MEMORY);
    result->_registers->Set(result->_registers, sp, FULL_MEMORY - 1);
    result->_registers->Set(result->_registers, fp, FULL_MEMORY - 1);
    result->_registers->Set(result->_registers, im, FULL_MEMORY);

    return result;
}

ErrCode CPU_GetRegister(CPU* this, const Registers reg, uint16_t* valueOut) {
    if (!this) {
        return THIS_IS_NULL;
    }
    return this->_registers->Get(this->_registers, reg, valueOut);
}

ErrCode CPU_SetRegister(CPU* this, Registers reg, uint16_t value) {
    if (!this) {
        return THIS_IS_NULL;
    }
    this->_registers->Set(this->_registers, reg, value);
}

void CPU_Run(CPU* this) {
    if (!this) {
        return;
    }

    while (true) {
        if (!this->Cycle(this)) {
            break;
        }
    }
}

bool CPU_Cycle(CPU* this) {
    if (!this) {
        return false;
    }

    uint8_t instruction;
    ErrCode err = CPU_fetch(this, &instruction);
    if (err != NO_ERR) {
        return false;
    }

    return CPU_execute(this, instruction);
}

ErrCode CPU_fetch(CPU* this, uint8_t* output) {
    if (!this) {
        return THIS_IS_NULL;
    }

    uint16_t nextInstructionAddress;
    ErrCode err = this->GetRegister(this, pc, &nextInstructionAddress);
    if (err != NO_ERR) {
        return err;
    }

    err = this->_memory->GetValue(this->_memory, nextInstructionAddress, output);
    if (err != NO_ERR) {
        return err;
    }

    return this->SetRegister(this, pc, nextInstructionAddress + 1);
}

ErrCode CPU_fetch16(CPU* this, uint16_t* output) {
    if (!this) {
        return THIS_IS_NULL;
    }

    uint16_t nextInstructionAddress;
    ErrCode err = this->GetRegister(this, pc, &nextInstructionAddress);
    if (err != NO_ERR) {
        return err;
    }

    err = this->_memory->GetValue16(this->_memory, nextInstructionAddress, output);
    if (err != NO_ERR) {
        return err;
    }

    return this->SetRegister(this, pc, nextInstructionAddress + 2);
}

ErrCode CPU_fetchRegisterIndex(CPU* this, Registers* output) {
    if (!this) {
        return THIS_IS_NULL;
    }

    uint8_t reg;
    ErrCode err = CPU_fetch(this, &reg);
    if (err != NO_ERR) {
        return err;
    }

    if (reg >= pc && reg <= im) {
        *output = (Registers)reg;
        return NO_ERR;
    }

    return INVALID_REGISTER;
}

bool CPU_execute(CPU* this, uint8_t instruction) {
    if (!this) {
        return false;
    }

    switch (instruction) {
        case MOV_LIT_REG: {
            return CPU_mov_lit_reg(this);
        }
    }
}

bool CPU_mov_lit_reg(CPU* this) {
    uint16_t val;
    ErrCode err = CPU_fetch16(this, &val);
    if (err != NO_ERR) {
        return false;
    }

    Registers reg;
    err = CPU_fetchRegisterIndex(this, &reg);
    if (err != NO_ERR) {
        return false;
    }

    err = this->SetRegister(this, reg, val);
    if (err != NO_ERR) {
        return false;
    }

    return true;
}