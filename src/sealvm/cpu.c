#include "sealvm/cpu.h"

#include <stdlib.h>

#include "sealvm/cpuHandlers.h"
#include "sealvm/defines.h"
#include "sealvm/instructions.h"

ErrCode CPU_GetRegister(CPU* this, Registers reg, uint16_t* valueOut);
ErrCode CPU_SetRegister(CPU* this, Registers reg, uint16_t value);
void CPU_Run(CPU* this);
bool CPU_Cycle(CPU* this);

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
            return CPU_movLitReg(this);
        }
        case MOV_REG_REG: {
            return CPU_movRegReg(this);
        }
        case MOV_REG_MEM: {
            return CPU_movRegMem(this);
        }
        case MOV_MEM_REG: {
            return CPU_movMemReg(this);
        }
        case ADD_REG_REG: {
            return CPU_addRegReg(this);
        }
        case JNE_LIT: {
            return CPU_jneLit(this);
        }
        case PSH_LIT: {
            return CPU_pshLit(this);
        }
        case PSH_REG: {
            return CPU_pshReg(this);
        }
        case POP: {
            return CPU_pop(this);
        }
        case CAL_LIT: {
            return CPU_calLit(this);
        }
        case CAL_REG: {
            return CPU_calReg(this);
        }
        case RET: {
            return CPU_ret(this);
        }
        case MOV_LIT_MEM: {
            return CPU_movLitMem(this);
        }
        case MOV_REG_PTR_REG: {
            return CPU_movRegPtrReg(this);
        }
        case MOV_LIT_OFF_REG: {
            return CPU_movLitOffReg(this);
        }
        case ADD_LIT_REG: {
            return CPU_addLitReg(this);
        }
        case SUB_LIT_REG: {
            return CPU_subLitReg(this);
        }
        case SUB_REG_LIT: {
            return CPU_subRegLit(this);
        }
        case SUB_REG_REG: {
            return CPU_subRegReg(this);
        }
        case MUL_LIT_REG: {
            return CPU_mulLitReg(this);
        }
        case MUL_REG_REG: {
            return CPU_mulRegReg(this);
        }
        case INC_REG: {
            return CPU_incReg(this);
        }
        case DEC_REG: {
            return CPU_decReg(this);
        }
        case LSF_REG_LIT: {
            return CPU_lsfRegLit(this);
        }
        case LSF_REG_REG: {
            return CPU_lsfRegReg(this);
        }
        case RSF_REG_LIT: {
            return CPU_rsfRegLit(this);
        }
        case RSF_REG_REG: {
            return CPU_rsfRegReg(this);
        }
        case AND_REG_LIT: {
            return CPU_andRegLit(this);
        }
        case AND_REG_REG: {
            return CPU_andRegReg(this);
        }
        case OR_REG_LIT: {
            return CPU_orRegLit(this);
        }
        case OR_REG_REG: {
            return CPU_orRegReg(this);
        }
        case XOR_REG_LIT: {
            return CPU_xorRegLit(this);
        }
        case XOR_REG_REG: {
            return CPU_xorRegReg(this);
        }
        case NOT: {
            return CPU_not(this);
        }
        case JNE_REG: {
            return CPU_jneReg(this);
        }
        case JEQ_REG: {
            return CPU_jeqReg(this);
        }
        case JEQ_LIT: {
            return CPU_jeqLit(this);
        }
        case JLT_REG: {
            return CPU_jltReg(this);
        }
        case JLT_LIT: {
            return CPU_jltLit(this);
        }
        case JGT_REG: {
            return CPU_jgtReg(this);
        }
        case JGT_LIT: {
            return CPU_jgtLit(this);
        }
        case JLE_REG: {
            return CPU_jleReg(this);
        }
        case JLE_LIT: {
            return CPU_jltLit(this);
        }
        case JGE_REG: {
            return CPU_jgeReg(this);
        }
        case JGE_LIT: {
            return CPU_jgeLit(this);
        }
        case INT: {
            return CPU_int(this);
        }
        case RET_INT: {
            return CPU_retInt(this);
        }
        // exit the CPU e.g.: HLT
        case HLT: {
            return false;
        }
    }

    return false;
}