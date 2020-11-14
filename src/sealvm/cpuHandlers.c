#include "sealvm/cpuHandlers.h"

#include "sealvm/defines.h"
#include "sealvm/errors.h"

/*
`this` pointer will always be checked prior to entering these functions, no need to check again
*/

bool CPU_movLitReg(CPU* this) {
    uint16_t val;
    if (CPU_fetch16(this, &val) != NO_ERR) {
        return false;
    }

    Registers reg;
    if (CPU_fetchRegisterIndex(this, &reg) != NO_ERR) {
        return false;
    }

    if (this->SetRegister(this, reg, val) != NO_ERR) {
        return false;
    }

    return true;
}

bool CPU_movRegReg(CPU* this) {
    Registers srcReg;
    if (CPU_fetchRegisterIndex(this, &srcReg) != NO_ERR) {
        return false;
    }

    Registers destReg;
    if (CPU_fetchRegisterIndex(this, &destReg) != NO_ERR) {
        return false;
    }

    uint16_t srcRegValue;
    if (this->GetRegister(this, srcReg, &srcRegValue) != NO_ERR) {
        return false;
    }

    if (this->SetRegister(this, destReg, srcRegValue) != NO_ERR) {
        return false;
    }

    return true;
}

bool CPU_movRegMem(CPU* this) {
    Registers reg;
    if (CPU_fetchRegisterIndex(this, &reg) != NO_ERR) {
        return false;
    }

    uint16_t addr;
    if (CPU_fetch16(this, &addr) != NO_ERR) {
        return false;
    }

    uint16_t regValue;
    if (this->GetRegister(this, reg, &regValue) != NO_ERR) {
        return false;
    }

    if (this->_memory->SetValue16(this->_memory, addr, regValue) != NO_ERR) {
        return false;
    }

    return true;
}

bool CPU_movMemReg(CPU* this) {
    uint16_t addr;
    if (CPU_fetch16(this, &addr) != NO_ERR) {
        return false;
    }

    Registers reg;
    if (CPU_fetchRegisterIndex(this, &reg) != NO_ERR) {
        return false;
    }

    uint16_t memValue;
    if (this->_memory->GetValue16(this->_memory, addr, &memValue) != NO_ERR) {
        return false;
    }

    if (this->SetRegister(this, reg, memValue) != NO_ERR) {
        return false;
    }

    return true;
}

bool CPU_addRegReg(CPU* this) {
    Registers reg1;
    if (CPU_fetchRegisterIndex(this, &reg1) != NO_ERR) {
        return false;
    }

    Registers reg2;
    if (CPU_fetchRegisterIndex(this, &reg2) != NO_ERR) {
        return false;
    }

    uint16_t reg1Value;
    if (this->GetRegister(this, reg1, &reg1Value) != NO_ERR) {
        return false;
    }

    uint16_t reg2Value;
    if (this->GetRegister(this, reg2, &reg2Value) != NO_ERR) {
        return false;
    }

    if (this->SetRegister(this, acc, reg1Value + reg2Value) != NO_ERR) {
        return false;
    }

    return true;
}

bool CPU_jneLit(CPU* this) {
    uint16_t compareVal;
    if (CPU_fetch16(this, &compareVal) != NO_ERR) {
        return false;
    }

    uint16_t jmpAddr;
    if (CPU_fetch16(this, &jmpAddr) != NO_ERR) {
        return false;
    }

    uint16_t accValue;
    if (this->GetRegister(this, acc, &accValue) != NO_ERR) {
        return false;
    }

    if (compareVal != accValue) {
        if (this->SetRegister(this, pc, jmpAddr) != NO_ERR) {
            return false;
        }
    }

    return true;
}

bool CPU_pshLit(CPU* this) {
    uint16_t val;
    if (CPU_fetch16(this, &val) != NO_ERR) {
        return false;
    }

    if (CPU_pushStack(this, val) != NO_ERR) {
        return false;
    }

    this->_stackFrameSize += 2;
    return true;
}

bool CPU_pshReg(CPU* this) {
    Registers reg;
    if (CPU_fetchRegisterIndex(this, &reg) != NO_ERR) {
        return false;
    }

    uint16_t val;
    if (this->GetRegister(this, reg, &val) != NO_ERR) {
        return false;
    }

    if (CPU_pushStack(this, val) != NO_ERR) {
        return false;
    }

    this->_stackFrameSize += 2;
    return true;
}

bool CPU_pop(CPU* this) {
    Registers reg;
    if (CPU_fetchRegisterIndex(this, &reg) != NO_ERR) {
        return false;
    }

    uint16_t stackVal;
    if (CPU_popStack(this, &stackVal) != NO_ERR) {
        return false;
    }

    if (this->SetRegister(this, reg, stackVal) != NO_ERR) {
        return false;
    }

    return true;
}

bool CPU_calLit(CPU* this) {
    uint16_t addr;
    if (CPU_fetch16(this, &addr) != NO_ERR) {
        return false;
    }

    if (CPU_pushStateStack(this) != NO_ERR) {
        return false;
    }

    if (this->SetRegister(this, pc, addr) != NO_ERR) {
        return false;
    }

    return true;
}

bool CPU_calReg(CPU* this) {
    Registers reg;
    if (CPU_fetchRegisterIndex(this, &reg) != NO_ERR) {
        return false;
    }

    uint16_t addr;
    if (this->GetRegister(this, reg, &addr) != NO_ERR) {
        return false;
    }

    if (CPU_pushStateStack(this) != NO_ERR) {
        return false;
    }

    if (this->SetRegister(this, pc, addr) != NO_ERR) {
        return false;
    }

    return true;
}

bool CPU_ret(CPU* this) {
    if (CPU_popStateStack(this) != NO_ERR) {
        return false;
    }
    return true;
}

bool CPU_movLitMem(CPU* this) {
    uint16_t litVal;
    if (CPU_fetch16(this, &litVal) != NO_ERR) {
        return false;
    }

    uint16_t addr;
    if (CPU_fetch16(this, &addr) != NO_ERR) {
        return false;
    }

    if (this->_memory->SetValue16(this->_memory, addr, litVal) != NO_ERR) {
        return false;
    }

    return true;
}

bool CPU_movRegPtrReg(CPU* this) {
    Registers srcReg;
    if (CPU_fetchRegisterIndex(this, &srcReg) != NO_ERR) {
        return false;
    }

    Registers destReg;
    if (CPU_fetchRegisterIndex(this, &destReg) != NO_ERR) {
        return false;
    }

    uint16_t addr;
    if (this->GetRegister(this, srcReg, &addr) != NO_ERR) {
        return false;
    }

    uint16_t memValue;
    if (this->_memory->GetValue16(this->_memory, addr, &memValue) != NO_ERR) {
        return false;
    }

    if (this->SetRegister(this, destReg, memValue) != NO_ERR) {
        return false;
    }

    return true;
}

bool CPU_movLitOffReg(CPU* this) {
    uint16_t baseAddr;
    if (CPU_fetch16(this, &baseAddr) != NO_ERR) {
        return false;
    }

    Registers srcReg;
    if (CPU_fetchRegisterIndex(this, &srcReg) != NO_ERR) {
        return false;
    }

    Registers destReg;
    if (CPU_fetchRegisterIndex(this, &destReg) != NO_ERR) {
        return false;
    }

    uint16_t offset;
    if (this->GetRegister(this, srcReg, &offset) != NO_ERR) {
        return false;
    }

    uint16_t memValue;
    if (this->_memory->GetValue16(this->_memory, baseAddr + offset, &memValue) != NO_ERR) {
        return false;
    }

    if (this->SetRegister(this, destReg, memValue) != NO_ERR) {
        return false;
    }

    return true;
}

bool CPU_addLitReg(CPU* this) { return false; }

bool CPU_subLitReg(CPU* this) { return false; }

bool CPU_subRegLit(CPU* this) { return false; }

bool CPU_subRegReg(CPU* this) { return false; }

bool CPU_mulLitReg(CPU* this) { return false; }

bool CPU_mulRegReg(CPU* this) { return false; }

bool CPU_incReg(CPU* this) { return false; }

bool CPU_decReg(CPU* this) { return false; }

bool CPU_lsfRegLit(CPU* this) { return false; }

bool CPU_lsfRegReg(CPU* this) { return false; }

bool CPU_rsfRegLit(CPU* this) { return false; }

bool CPU_rsfRegReg(CPU* this) { return false; }

bool CPU_andRegLit(CPU* this) { return false; }

bool CPU_andRegReg(CPU* this) { return false; }

bool CPU_orRegLit(CPU* this) { return false; }

bool CPU_orRegReg(CPU* this) { return false; }

bool CPU_xorRegLit(CPU* this) { return false; }

bool CPU_xorRegReg(CPU* this) { return false; }

bool CPU_not(CPU* this) { return false; }

bool CPU_jneReg(CPU* this) { return false; }

bool CPU_jeqReg(CPU* this) { return false; }

bool CPU_jeqLit(CPU* this) { return false; }

bool CPU_jltReg(CPU* this) { return false; }

bool CPU_jltLit(CPU* this) { return false; }

bool CPU_jgtReg(CPU* this) { return false; }

bool CPU_jgtLit(CPU* this) { return false; }

bool CPU_jleReg(CPU* this) { return false; }

bool CPU_jleLit(CPU* this) { return false; }

bool CPU_jgeReg(CPU* this) { return false; }

bool CPU_jgeLit(CPU* this) { return false; }

bool CPU_int(CPU* this) { return false; }

bool CPU_retInt(CPU* this) { return false; }