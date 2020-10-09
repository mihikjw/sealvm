#include <iostream>

#include "sealvm/sealvm.hpp"

int main() {
    auto memory = SealVM::Memory(256 * 256);
    auto cpu = SealVM::CPU(&memory);

    // ---------------------------
    // Program machine code
    // ---------------------------
    uint16_t i = 0;

    memory.SetValue(i++, SealVM::Instructions::PSH_LIT); // PSH 0x3333
    memory.SetValue(i++, 0x33);
    memory.SetValue(i++, 0x33);

    memory.SetValue(i++, SealVM::Instructions::PSH_LIT); // PSH 0x2222
    memory.SetValue(i++, 0x22);
    memory.SetValue(i++, 0x22);

    memory.SetValue(i++, SealVM::Instructions::PSH_LIT); // PSH 0x1111
    memory.SetValue(i++, 0x11);
    memory.SetValue(i++, 0x11);

    memory.SetValue(i++, SealVM::Instructions::MOV_LIT_REG); // MOV 0x1234, r1
    memory.SetValue(i++, 0x12);
    memory.SetValue(i++, 0x34);
    memory.SetValue(i++, SealVM::Registers::r1);

    memory.SetValue(i++, SealVM::Instructions::MOV_LIT_REG); // MOV 0x5678, r4
    memory.SetValue(i++, 0x56);
    memory.SetValue(i++, 0x78);
    memory.SetValue(i++, SealVM::Registers::r4);

    memory.SetValue(i++, SealVM::Instructions::PSH_LIT); // PSH 0x0000
    memory.SetValue(i++, 0x00);
    memory.SetValue(i++, 0x00);

    memory.SetValue(i++, SealVM::Instructions::CAL_LIT); // CAL 0x3000
    memory.SetValue(i++, 0x30);
    memory.SetValue(i++, 0x00);

    memory.SetValue(i++, SealVM::Instructions::PSH_LIT); // PSH 0x4444
    memory.SetValue(i++, 0x44);
    memory.SetValue(i++, 0x44);

    // next instructions are part of 'my_subroutine:'
    i = 0x3000;

    memory.SetValue(i++, SealVM::Instructions::PSH_LIT); // PSH 0x0102
    memory.SetValue(i++, 0x01);
    memory.SetValue(i++, 0x02);

    memory.SetValue(i++, SealVM::Instructions::PSH_LIT); // PSH 0x0304
    memory.SetValue(i++, 0x03);
    memory.SetValue(i++, 0x04);

    memory.SetValue(i++, SealVM::Instructions::PSH_LIT); // PSH 0x0506
    memory.SetValue(i++, 0x05);
    memory.SetValue(i++, 0x06);

    memory.SetValue(i++, SealVM::Instructions::MOV_LIT_REG); // MOV 0x0708, r1
    memory.SetValue(i++, 0x07);
    memory.SetValue(i++, 0x08);
    memory.SetValue(i++, SealVM::Registers::r1);

    memory.SetValue(i++, SealVM::Instructions::MOV_LIT_REG); // MOV 0x090A, r8
    memory.SetValue(i++, 0x09);
    memory.SetValue(i++, 0x0A);
    memory.SetValue(i++, SealVM::Registers::r8);

    memory.SetValue(i++, SealVM::Instructions::RET);

    // ---------------------------
    // Rudimentary Debugger
    // ---------------------------
    std::string input;

    while (std::cin) {
        std::getline(std::cin, input);
        cpu.Cycle();
        cpu.Debug();
        memory.Debug(cpu.GetRegister(SealVM::Registers::pc));
        memory.Debug(0xffff - 43, 44);
    }
}