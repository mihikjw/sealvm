#include "sealvm/cpu.hpp"

using namespace SealVM;

CPU::CPU(Memory* memory) noexcept { this->memory = memory; }

const uint16_t CPU::GetRegister(const Registers name) {
    auto validRegister = registers.find(name);
    if (validRegister == registers.end()) {
        throw std::runtime_error("invalid register");
    }

    return registers[name];
}

void CPU::SetRegister(const Registers name, uint16_t value) {
    auto validRegister = registers.find(name);
    if (validRegister == registers.end()) {
        throw std::runtime_error("invalid register");
    }

    registers[name] = value;
}

const uint8_t CPU::Fetch() {
    auto nextInstructionAddress = GetRegister(Registers::pc);
    auto instruction = memory->buffer[nextInstructionAddress];
    SetRegister(Registers::pc, (nextInstructionAddress + 1));
    return instruction;
}

const uint16_t CPU::Fetch16() {
    const uint16_t nextInstructionAddress = GetRegister(Registers::pc);
    uint8_t instruction1 = memory->buffer[nextInstructionAddress];
    uint8_t instruction2 = memory->buffer[nextInstructionAddress + 1];
    SetRegister(Registers::pc, (nextInstructionAddress + 2));
    return instruction1 << 8 | instruction2;
}

void CPU::Execute(const uint16_t instruction) {
    switch (instruction) {
        case Instructions::MOV_LIT_R1: {
            auto value = Fetch16();
            SetRegister(Registers::r1, value);
            break;
        }

        case Instructions::MOV_LIT_R2: {
            auto value = Fetch16();
            SetRegister(Registers::r2, value);
            break;
        }

        case Instructions::ADD_REG_REG: {
            auto r1 = static_cast<Registers>(Fetch());
            auto r2 = static_cast<Registers>(Fetch());
            auto r1Value = GetRegister(r1);
            auto r2Value = GetRegister(r2);
            SetRegister(Registers::acc, r1Value + r2Value);
            break;
        }
    }
}

void CPU::Step() {
    auto instruction = Fetch();
    Execute(instruction);
}

void CPU::Debug() {
    for (auto const& [key, val] : registers) {
        std::cout << std::hex << "0x" << key << ": " << val << std::endl;
    }
}