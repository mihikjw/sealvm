#include <iostream>

#include "sealvm/sealvm.hpp"

int main() {
    auto memory = SealVM::Memory(256);

    memory.buffer[0] = SealVM::Instructions::MOV_LIT_R1;
    memory.buffer[1] = 0x12;
    memory.buffer[2] = 0x34;
    memory.buffer[3] = SealVM::Instructions::MOV_LIT_R2;
    memory.buffer[4] = 0xAB;
    memory.buffer[5] = 0xCD;
    memory.buffer[6] = SealVM::Instructions::ADD_REG_REG;
    memory.buffer[7] = SealVM::Registers::r1;
    memory.buffer[8] = SealVM::Registers::r2;

    auto cpu = SealVM::CPU(&memory);

    cpu.Debug();
    cpu.Step();
    cpu.Debug();
    cpu.Step();
    cpu.Debug();
    cpu.Step();
    cpu.Debug();
}