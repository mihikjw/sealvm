#include <iostream>

#include "sealvm/sealvm.hpp"

int main() {
    auto memory = SealVM::Memory(256 * 256);
    auto cpu = SealVM::CPU(&memory);
    uint16_t i = 0;

    memory.SetValue(i++, SealVM::Instructions::MOV_LIT_REG); // MOV 0x1234 r1
    memory.SetValue(i++, 0x12);
    memory.SetValue(i++, 0x34);
    memory.SetValue(i++, SealVM::Registers::r1);

    memory.SetValue(i++, SealVM::Instructions::MOV_LIT_REG); // MOV 0xABCD r2
    memory.SetValue(i++, 0xAB);
    memory.SetValue(i++, 0xCD);
    memory.SetValue(i++, SealVM::Registers::r2);

    memory.SetValue(i++, SealVM::Instructions::ADD_REG_REG); // ADD r1, r2
    memory.SetValue(i++, SealVM::Registers::r1);
    memory.SetValue(i++, SealVM::Registers::r2);

    memory.SetValue(i++, SealVM::Instructions::MOV_REG_MEM); // ADD acc, 0x0100
    memory.SetValue(i++, SealVM::Registers::acc);
    memory.SetValue(i++, 0x01);
    memory.SetValue(i++, 0x00);

    cpu.Debug();
    memory.Debug(cpu.GetRegister(SealVM::Registers::pc));
    memory.Debug(0x0100);
    cpu.Step();

    cpu.Debug();
    memory.Debug(cpu.GetRegister(SealVM::Registers::pc));
    memory.Debug(0x0100);
    cpu.Step();

    cpu.Debug();
    memory.Debug(cpu.GetRegister(SealVM::Registers::pc));
    memory.Debug(0x0100);
    cpu.Step();

    cpu.Debug();
    memory.Debug(cpu.GetRegister(SealVM::Registers::pc));
    memory.Debug(0x0100);
    cpu.Step();

    cpu.Debug();
    memory.Debug(cpu.GetRegister(SealVM::Registers::pc));
    memory.Debug(0x0100);
}