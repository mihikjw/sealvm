#include "sealvm/cpuHandlers.h"

bool CPU_movLitReg(CPU* this) {
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

bool CPU_movRegReg(CPU* this) { return false; }

bool CPU_movRegMem(CPU* this) { return false; }

bool CPU_movMemReg(CPU* this) { return false; }

bool CPU_addRegReg(CPU* this) { return false; }

bool CPU_jneLit(CPU* this) { return false; }

bool CPU_pshLit(CPU* this) { return false; }

bool CPU_pshReg(CPU* this) { return false; }

bool CPU_pop(CPU* this) { return false; }

bool CPU_calLit(CPU* this) { return false; }

bool CPU_calReg(CPU* this) { return false; }

bool CPU_ret(CPU* this) { return false; }

bool CPU_movLitMem(CPU* this) { return false; }

bool CPU_movRegPtrReg(CPU* this) { return false; }

bool CPU_movLitOffReg(CPU* this) { return false; }

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