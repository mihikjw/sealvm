#include <iostream>

#include "sealvm/sealvm.hpp"

int main() {
    auto memory = SealVM::Memory(256 * 256);
    auto cpu = SealVM::CPU(&memory);

    // ---------------------------
    // Program machine code
    // ---------------------------
    uint16_t i = 0;

    // start: // this is just a label for address 0x00 in memory
    memory.SetValue(i++, SealVM::Instructions::MOV_MEM_REG); // MOV #0x0100, r1
    memory.SetValue(i++, 0x01);
    memory.SetValue(i++, 0x00);
    memory.SetValue(i++, SealVM::Registers::r1);

    memory.SetValue(i++, SealVM::Instructions::MOV_LIT_REG); // MOV 0x0001, r2
    memory.SetValue(i++, 0x00);
    memory.SetValue(i++, 0x01);
    memory.SetValue(i++, SealVM::Registers::r2);

    memory.SetValue(i++, SealVM::Instructions::ADD_REG_REG); // ADD r1, r2
    memory.SetValue(i++, SealVM::Registers::r1);
    memory.SetValue(i++, SealVM::Registers::r2);

    memory.SetValue(i++, SealVM::Instructions::MOV_REG_MEM); // MOV acc, #0x0100
    memory.SetValue(i++, SealVM::Registers::acc);
    memory.SetValue(i++, 0x01);
    memory.SetValue(i++, 0x00);

    memory.SetValue(i++, SealVM::Instructions::JMP_NOT_EQ); // JNE 0x003, #0x0100, start:
    memory.SetValue(i++, 0x00);
    memory.SetValue(i++, 0x03);
    memory.SetValue(i++, 0x00);

    // ---------------------------
    // Rudimentary Debugger
    // ---------------------------
    std::string input;

    while (std::cin) {
        cpu.Step();
        cpu.Debug();
        memory.Debug(cpu.GetRegister(SealVM::Registers::pc));
        memory.Debug(0x0100);
        std::getline(std::cin, input);
    }
}