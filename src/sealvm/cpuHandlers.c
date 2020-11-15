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

bool CPU_addLitReg(CPU* this) {
    uint16_t lit;
    if (CPU_fetch16(this, &lit) != NO_ERR) {
        return false;
    }

    Registers reg;
    if (CPU_fetchRegisterIndex(this, &reg) != NO_ERR) {
        return false;
    }

    uint16_t regVal;
    if (this->GetRegister(this, reg, &regVal) != NO_ERR) {
        return false;
    }

    if (this->SetRegister(this, acc, lit + regVal) != NO_ERR) {
        return false;
    }

    return true;
}

bool CPU_subLitReg(CPU* this) {
    uint16_t lit;
    if (CPU_fetch16(this, &lit) != NO_ERR) {
        return false;
    }

    Registers reg;
    if (CPU_fetchRegisterIndex(this, &reg) != NO_ERR) {
        return false;
    }

    uint16_t regVal;
    if (this->GetRegister(this, reg, &regVal) != NO_ERR) {
        return false;
    }

    if (this->SetRegister(this, acc, lit - regVal) != NO_ERR) {
        return false;
    }

    return true;
}

bool CPU_subRegLit(CPU* this) {
    Registers reg;
    if (CPU_fetchRegisterIndex(this, &reg) != NO_ERR) {
        return false;
    }

    uint16_t lit;
    if (CPU_fetch16(this, &lit) != NO_ERR) {
        return false;
    }

    uint16_t regVal;
    if (this->GetRegister(this, reg, &regVal) != NO_ERR) {
        return false;
    }

    if (this->SetRegister(this, acc, regVal - lit) != NO_ERR) {
        return false;
    }

    return true;
}

bool CPU_subRegReg(CPU* this) {
    Registers reg1;
    if (CPU_fetchRegisterIndex(this, &reg1) != NO_ERR) {
        return false;
    }

    Registers reg2;
    if (CPU_fetchRegisterIndex(this, &reg2) != NO_ERR) {
        return false;
    }

    uint16_t reg1Val;
    if (this->GetRegister(this, reg1, &reg1Val) != NO_ERR) {
        return false;
    }

    uint16_t reg2Val;
    if (this->GetRegister(this, reg2, &reg2Val) != NO_ERR) {
        return false;
    }

    if (this->SetRegister(this, acc, reg1Val - reg2Val) != NO_ERR) {
        return false;
    }

    return true;
}

bool CPU_mulLitReg(CPU* this) {
    uint16_t lit;
    if (CPU_fetch16(this, &lit) != NO_ERR) {
        return false;
    }

    Registers reg;
    if (CPU_fetchRegisterIndex(this, &reg) != NO_ERR) {
        return false;
    }

    uint16_t regVal;
    if (this->GetRegister(this, reg, &regVal) != NO_ERR) {
        return false;
    }

    if (this->SetRegister(this, acc, lit * regVal) != NO_ERR) {
        return false;
    }

    return true;
}

bool CPU_mulRegReg(CPU* this) {
    Registers reg1;
    if (CPU_fetchRegisterIndex(this, &reg1) != NO_ERR) {
        return false;
    }

    Registers reg2;
    if (CPU_fetchRegisterIndex(this, &reg2) != NO_ERR) {
        return false;
    }

    uint16_t reg1Val;
    if (this->GetRegister(this, reg1, &reg1Val) != NO_ERR) {
        return false;
    }

    uint16_t reg2Val;
    if (this->GetRegister(this, reg2, &reg2Val) != NO_ERR) {
        return false;
    }

    if (this->SetRegister(this, acc, reg1Val * reg2Val) != NO_ERR) {
        return false;
    }

    return true;
}

bool CPU_incReg(CPU* this) {
    Registers reg;
    if (CPU_fetchRegisterIndex(this, &reg) != NO_ERR) {
        return false;
    }

    uint16_t regVal;
    if (this->GetRegister(this, reg, &regVal) != NO_ERR) {
        return false;
    }

    if (this->SetRegister(this, reg, regVal++) != NO_ERR) {
        return false;
    }

    return true;
}

bool CPU_decReg(CPU* this) {
    Registers reg;
    if (CPU_fetchRegisterIndex(this, &reg) != NO_ERR) {
        return false;
    }

    uint16_t regVal;
    if (this->GetRegister(this, reg, &regVal) != NO_ERR) {
        return false;
    }

    if (this->SetRegister(this, reg, regVal--) != NO_ERR) {
        return false;
    }

    return true;
}

bool CPU_lsfRegLit(CPU* this) {
    Registers reg;
    if (CPU_fetchRegisterIndex(this, &reg) != NO_ERR) {
        return false;
    }

    uint16_t lit;
    if (CPU_fetch16(this, &lit) != NO_ERR) {
        return false;
    }

    uint16_t regVal;
    if (this->GetRegister(this, reg, &regVal) != NO_ERR) {
        return false;
    }

    if (this->SetRegister(this, reg, regVal << lit) != NO_ERR) {
        return false;
    }

    return true;
}

bool CPU_lsfRegReg(CPU* this) {
    Registers reg1;
    if (CPU_fetchRegisterIndex(this, &reg1) != NO_ERR) {
        return false;
    }

    Registers reg2;
    if (CPU_fetchRegisterIndex(this, &reg2) != NO_ERR) {
        return false;
    }

    uint16_t reg1Val;
    if (this->GetRegister(this, reg1, &reg1Val) != NO_ERR) {
        return false;
    }

    uint16_t reg2Val;
    if (this->GetRegister(this, reg2, &reg2Val) != NO_ERR) {
        return false;
    }

    if (this->SetRegister(this, reg1, reg1Val << reg2Val) != NO_ERR) {
        return false;
    }

    return true;
}

bool CPU_rsfRegLit(CPU* this) {
    Registers reg;
    if (CPU_fetchRegisterIndex(this, &reg) != NO_ERR) {
        return false;
    }

    uint16_t lit;
    if (CPU_fetch16(this, &lit) != NO_ERR) {
        return false;
    }

    uint16_t regVal;
    if (this->GetRegister(this, reg, &regVal) != NO_ERR) {
        return false;
    }

    if (this->SetRegister(this, reg, regVal >> lit) != NO_ERR) {
        return false;
    }

    return true;
}

bool CPU_rsfRegReg(CPU* this) {
    Registers reg1;
    if (CPU_fetchRegisterIndex(this, &reg1) != NO_ERR) {
        return false;
    }

    Registers reg2;
    if (CPU_fetchRegisterIndex(this, &reg2) != NO_ERR) {
        return false;
    }

    uint16_t reg1Val;
    if (this->GetRegister(this, reg1, &reg1Val) != NO_ERR) {
        return false;
    }

    uint16_t reg2Val;
    if (this->GetRegister(this, reg2, &reg2Val) != NO_ERR) {
        return false;
    }

    if (this->SetRegister(this, reg1, reg1Val >> reg2Val) != NO_ERR) {
        return false;
    }

    return true;
}

bool CPU_andRegLit(CPU* this) {
    Registers reg;
    if (CPU_fetchRegisterIndex(this, &reg) != NO_ERR) {
        return false;
    }

    uint16_t lit;
    if (CPU_fetch16(this, &lit) != NO_ERR) {
        return false;
    }

    uint16_t regVal;
    if (this->GetRegister(this, reg, &regVal) != NO_ERR) {
        return false;
    }

    if (this->SetRegister(this, acc, regVal & lit) != NO_ERR) {
        return false;
    }

    return true;
}

bool CPU_andRegReg(CPU* this) {
    Registers reg1;
    if (CPU_fetchRegisterIndex(this, &reg1) != NO_ERR) {
        return false;
    }

    Registers reg2;
    if (CPU_fetchRegisterIndex(this, &reg2) != NO_ERR) {
        return false;
    }

    uint16_t reg1Val;
    if (this->GetRegister(this, reg1, &reg1Val) != NO_ERR) {
        return false;
    }

    uint16_t reg2Val;
    if (this->GetRegister(this, reg2, &reg2Val) != NO_ERR) {
        return false;
    }

    if (this->SetRegister(this, acc, reg1Val & reg2Val) != NO_ERR) {
        return false;
    }

    return true;
}

bool CPU_orRegLit(CPU* this) {
    Registers reg;
    if (CPU_fetchRegisterIndex(this, &reg) != NO_ERR) {
        return false;
    }

    uint16_t lit;
    if (CPU_fetch16(this, &lit) != NO_ERR) {
        return false;
    }

    uint16_t regVal;
    if (this->GetRegister(this, reg, &regVal) != NO_ERR) {
        return false;
    }

    if (this->SetRegister(this, acc, regVal | lit) != NO_ERR) {
        return false;
    }

    return true;
}

bool CPU_orRegReg(CPU* this) {
    Registers reg1;
    if (CPU_fetchRegisterIndex(this, &reg1) != NO_ERR) {
        return false;
    }

    Registers reg2;
    if (CPU_fetchRegisterIndex(this, &reg2) != NO_ERR) {
        return false;
    }

    uint16_t reg1Val;
    if (this->GetRegister(this, reg1, &reg1Val) != NO_ERR) {
        return false;
    }

    uint16_t reg2Val;
    if (this->GetRegister(this, reg2, &reg2Val) != NO_ERR) {
        return false;
    }

    if (this->SetRegister(this, acc, reg1Val | reg2Val) != NO_ERR) {
        return false;
    }

    return true;
}

bool CPU_xorRegLit(CPU* this) {
    Registers reg;
    if (CPU_fetchRegisterIndex(this, &reg) != NO_ERR) {
        return false;
    }

    uint16_t lit;
    if (CPU_fetch16(this, &lit) != NO_ERR) {
        return false;
    }

    uint16_t regVal;
    if (this->GetRegister(this, reg, &regVal) != NO_ERR) {
        return false;
    }

    if (this->SetRegister(this, acc, regVal ^ lit) != NO_ERR) {
        return false;
    }

    return true;
}

bool CPU_xorRegReg(CPU* this) {
    Registers reg1;
    if (CPU_fetchRegisterIndex(this, &reg1) != NO_ERR) {
        return false;
    }

    Registers reg2;
    if (CPU_fetchRegisterIndex(this, &reg2) != NO_ERR) {
        return false;
    }

    uint16_t reg1Val;
    if (this->GetRegister(this, reg1, &reg1Val) != NO_ERR) {
        return false;
    }

    uint16_t reg2Val;
    if (this->GetRegister(this, reg2, &reg2Val) != NO_ERR) {
        return false;
    }

    if (this->SetRegister(this, acc, reg1Val ^ reg2Val) != NO_ERR) {
        return false;
    }

    return true;
}

bool CPU_not(CPU* this) {
    Registers reg;
    if (CPU_fetchRegisterIndex(this, &reg) != NO_ERR) {
        return false;
    }

    uint16_t val;
    if (this->GetRegister(this, reg, &val) != NO_ERR) {
        return false;
    }

    // only want bottom 16 bits incase anything funky happens
    if (this->SetRegister(this, acc, (~val) & 0xffff) != NO_ERR) {
        return false;
    }
}

bool CPU_jneReg(CPU* this) {
    Registers reg;
    if (CPU_fetchRegisterIndex(this, &reg) != NO_ERR) {
        return false;
    }

    uint16_t jmpAddr;
    if (CPU_fetch16(this, &jmpAddr) != NO_ERR) {
        return false;
    }

    uint16_t regVal;
    if (this->GetRegister(this, reg, &regVal) != NO_ERR) {
        return false;
    }

    uint16_t accVal;
    if (this->GetRegister(this, acc, &accVal) != NO_ERR) {
        return false;
    }

    if (regVal != accVal) {
        if (this->SetRegister(this, pc, jmpAddr) != NO_ERR) {
            return false;
        }
    }

    return true;
}

bool CPU_jeqReg(CPU* this) {
    Registers reg;
    if (CPU_fetchRegisterIndex(this, &reg) != NO_ERR) {
        return false;
    }

    uint16_t jmpAddr;
    if (CPU_fetch16(this, &jmpAddr) != NO_ERR) {
        return false;
    }

    uint16_t regVal;
    if (this->GetRegister(this, reg, &regVal) != NO_ERR) {
        return false;
    }

    uint16_t accVal;
    if (this->GetRegister(this, acc, &accVal) != NO_ERR) {
        return false;
    }

    if (regVal == accVal) {
        if (this->SetRegister(this, pc, jmpAddr) != NO_ERR) {
            return false;
        }
    }

    return true;
}

bool CPU_jeqLit(CPU* this) {
    uint16_t literal;
    if (CPU_fetch16(this, &literal) != NO_ERR) {
        return false;
    }

    uint16_t jmpAddr;
    if (CPU_fetch16(this, &jmpAddr) != NO_ERR) {
        return false;
    }

    uint16_t accVal;
    if (this->GetRegister(this, acc, &accVal) != NO_ERR) {
        return false;
    }

    if (literal == accVal) {
        if (this->SetRegister(this, pc, jmpAddr) != NO_ERR) {
            return false;
        }
    }

    return true;
}

bool CPU_jltReg(CPU* this) {
    Registers reg;
    if (CPU_fetchRegisterIndex(this, &reg) != NO_ERR) {
        return false;
    }

    uint16_t jmpAddr;
    if (CPU_fetch16(this, &jmpAddr) != NO_ERR) {
        return false;
    }

    uint16_t regVal;
    if (this->GetRegister(this, reg, &regVal) != NO_ERR) {
        return false;
    }

    uint16_t accVal;
    if (this->GetRegister(this, acc, &accVal) != NO_ERR) {
        return false;
    }

    if (regVal < accVal) {
        if (this->SetRegister(this, pc, jmpAddr) != NO_ERR) {
            return false;
        }
    }

    return true;
}

bool CPU_jltLit(CPU* this) {
    uint16_t literal;
    if (CPU_fetch16(this, &literal) != NO_ERR) {
        return false;
    }

    uint16_t jmpAddr;
    if (CPU_fetch16(this, &jmpAddr) != NO_ERR) {
        return false;
    }

    uint16_t accVal;
    if (this->GetRegister(this, acc, &accVal) != NO_ERR) {
        return false;
    }

    if (literal < accVal) {
        if (this->SetRegister(this, pc, jmpAddr) != NO_ERR) {
            return false;
        }
    }

    return true;
}

bool CPU_jgtReg(CPU* this) {
    Registers reg;
    if (CPU_fetchRegisterIndex(this, &reg) != NO_ERR) {
        return false;
    }

    uint16_t jmpAddr;
    if (CPU_fetch16(this, &jmpAddr) != NO_ERR) {
        return false;
    }

    uint16_t regVal;
    if (this->GetRegister(this, reg, &regVal) != NO_ERR) {
        return false;
    }

    uint16_t accVal;
    if (this->GetRegister(this, acc, &accVal) != NO_ERR) {
        return false;
    }

    if (regVal > accVal) {
        if (this->SetRegister(this, pc, jmpAddr) != NO_ERR) {
            return false;
        }
    }

    return true;
}

bool CPU_jgtLit(CPU* this) {
    uint16_t literal;
    if (CPU_fetch16(this, &literal) != NO_ERR) {
        return false;
    }

    uint16_t jmpAddr;
    if (CPU_fetch16(this, &jmpAddr) != NO_ERR) {
        return false;
    }

    uint16_t accVal;
    if (this->GetRegister(this, acc, &accVal) != NO_ERR) {
        return false;
    }

    if (literal > accVal) {
        if (this->SetRegister(this, pc, jmpAddr) != NO_ERR) {
            return false;
        }
    }

    return true;
}

bool CPU_jleReg(CPU* this) {
    Registers reg;
    if (CPU_fetchRegisterIndex(this, &reg) != NO_ERR) {
        return false;
    }

    uint16_t jmpAddr;
    if (CPU_fetch16(this, &jmpAddr) != NO_ERR) {
        return false;
    }

    uint16_t regVal;
    if (this->GetRegister(this, reg, &regVal) != NO_ERR) {
        return false;
    }

    uint16_t accVal;
    if (this->GetRegister(this, acc, &accVal) != NO_ERR) {
        return false;
    }

    if (regVal <= accVal) {
        if (this->SetRegister(this, pc, jmpAddr) != NO_ERR) {
            return false;
        }
    }

    return true;
}

bool CPU_jleLit(CPU* this) {
    uint16_t literal;
    if (CPU_fetch16(this, &literal) != NO_ERR) {
        return false;
    }

    uint16_t jmpAddr;
    if (CPU_fetch16(this, &jmpAddr) != NO_ERR) {
        return false;
    }

    uint16_t accVal;
    if (this->GetRegister(this, acc, &accVal) != NO_ERR) {
        return false;
    }

    if (literal <= accVal) {
        if (this->SetRegister(this, pc, jmpAddr) != NO_ERR) {
            return false;
        }
    }

    return true;
}

bool CPU_jgeReg(CPU* this) {
    Registers reg;
    if (CPU_fetchRegisterIndex(this, &reg) != NO_ERR) {
        return false;
    }

    uint16_t jmpAddr;
    if (CPU_fetch16(this, &jmpAddr) != NO_ERR) {
        return false;
    }

    uint16_t regVal;
    if (this->GetRegister(this, reg, &regVal) != NO_ERR) {
        return false;
    }

    uint16_t accVal;
    if (this->GetRegister(this, acc, &accVal) != NO_ERR) {
        return false;
    }

    if (regVal >= accVal) {
        if (this->SetRegister(this, pc, jmpAddr) != NO_ERR) {
            return false;
        }
    }

    return true;
}

bool CPU_jgeLit(CPU* this) {
    uint16_t literal;
    if (CPU_fetch16(this, &literal) != NO_ERR) {
        return false;
    }

    uint16_t jmpAddr;
    if (CPU_fetch16(this, &jmpAddr) != NO_ERR) {
        return false;
    }

    uint16_t accVal;
    if (this->GetRegister(this, acc, &accVal) != NO_ERR) {
        return false;
    }

    if (literal >= accVal) {
        if (this->SetRegister(this, pc, jmpAddr) != NO_ERR) {
            return false;
        }
    }

    return true;
}

bool CPU_int(CPU* this) {
    uint16_t vectorIndex;
    if (CPU_fetch16(this, &vectorIndex) != NO_ERR) {
        return false;
    }

    if (CPU_handleInterrupt(this, vectorIndex) != NO_ERR) {
        return false;
    }

    return true;
}

bool CPU_retInt(CPU* this) {
    this->_isInInterrupt = false;
    if (CPU_popStateStack(this) != NO_ERR) {
        return false;
    }
    return true;
}