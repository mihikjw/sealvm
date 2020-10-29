#include <iostream>

#include "sealvm/sealvm.hpp"

/*
this is the executable for SealVM, however it's currently WIP, instruction codes etc are likley to change before v1.0 release.
currently you need to manually add machine-code into memory starting from position 0, I'm working on an assembly parser and
    compiler before coming back to working on the VM itself, where a core focus from there will be
    making all the VM code more resiliant and efficient
*/

// MEMORY_SIZE defines the total size of memory avalible
constexpr int MEMORY_SIZE = 256 * 256;

int main() {
    std::vector<uint8_t> mainMemory(MEMORY_SIZE, SealVM::ZERO_MEMORY);

    auto memory = SealVM::Memory(&mainMemory);
    auto mapper = SealVM::MemoryMapper(&mainMemory);
    mapper.Map(&memory, SealVM::ZERO_MEMORY, SealVM::FULL_MEMORY);

    // as a test, map part of the address space to a 'screen device', mapped from the start/end
    //  this device doesn't take memory, instead writes from 0x3000 - 0x30ff, first 8-bits are any commands, the last 8 are the character to print
    // see `sealvm/screenDevice.hpp` for details
    SealVM::ScreenDevice screenDevice(nullptr);
    mapper.Map(&screenDevice, 0x3000, 0x30ff, true);

    auto cpu = SealVM::CPU(&mapper);

    // ---------------------------
    // Program machine code
    // ---------------------------
    int i = 0;

    // H
    memory.SetValue(i++, SealVM::Instructions::MOV_LIT_REG);
    memory.SetValue(i++, 0x01);
    memory.SetValue(i++, 0x48);
    memory.SetValue(i++, SealVM::Registers::r1);

    memory.SetValue(i++, SealVM::Instructions::MOV_REG_MEM);
    memory.SetValue(i++, SealVM::Registers::r1);
    memory.SetValue(i++, 0x30);
    memory.SetValue(i++, 0x00);

    // E
    memory.SetValue(i++, SealVM::Instructions::MOV_LIT_REG);
    memory.SetValue(i++, 0x00);
    memory.SetValue(i++, 0x45);
    memory.SetValue(i++, SealVM::Registers::r1);

    memory.SetValue(i++, SealVM::Instructions::MOV_REG_MEM);
    memory.SetValue(i++, SealVM::Registers::r1);
    memory.SetValue(i++, 0x30);
    memory.SetValue(i++, 0x01);

    // L
    memory.SetValue(i++, SealVM::Instructions::MOV_LIT_REG);
    memory.SetValue(i++, 0x00);
    memory.SetValue(i++, 0x4C);
    memory.SetValue(i++, SealVM::Registers::r1);

    memory.SetValue(i++, SealVM::Instructions::MOV_REG_MEM);
    memory.SetValue(i++, SealVM::Registers::r1);
    memory.SetValue(i++, 0x30);
    memory.SetValue(i++, 0x02);

    // L
    memory.SetValue(i++, SealVM::Instructions::MOV_LIT_REG);
    memory.SetValue(i++, 0x02);
    memory.SetValue(i++, 0x4C);
    memory.SetValue(i++, SealVM::Registers::r1);

    memory.SetValue(i++, SealVM::Instructions::MOV_REG_MEM);
    memory.SetValue(i++, SealVM::Registers::r1);
    memory.SetValue(i++, 0x30);
    memory.SetValue(i++, 0x03);

    // O
    memory.SetValue(i++, SealVM::Instructions::MOV_LIT_REG);
    memory.SetValue(i++, 0x00);
    memory.SetValue(i++, 0x4F);
    memory.SetValue(i++, SealVM::Registers::r1);

    memory.SetValue(i++, SealVM::Instructions::MOV_REG_MEM);
    memory.SetValue(i++, SealVM::Registers::r1);
    memory.SetValue(i++, 0x30);
    memory.SetValue(i++, 0x04);

    memory.SetValue(i++, SealVM::Instructions::HLT);

    cpu.Run();
}