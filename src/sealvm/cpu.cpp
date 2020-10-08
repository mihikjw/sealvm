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
    auto instruction = memory->GetValue(nextInstructionAddress);
    SetRegister(Registers::pc, (nextInstructionAddress + 1));
    return instruction;
}

const uint16_t CPU::Fetch16() {
    auto nextInstructionAddress = GetRegister(Registers::pc);
    auto instruction1 = memory->GetValue(nextInstructionAddress);
    auto instruction2 = memory->GetValue(nextInstructionAddress + 1);
    SetRegister(Registers::pc, (nextInstructionAddress + 2));
    return instruction1 << 8 | instruction2;
}

void CPU::Execute(const uint16_t instruction) {
    switch (instruction) {
        // move literal value into register e.g.: MOV 0x1234, r1
        case Instructions::MOV_LIT_REG: {
            auto value = Fetch16();
            auto reg = static_cast<Registers>((Fetch() % registers.size()));
            SetRegister(reg, value);
            break;
        }

        // move register value into another register e.g.: MOV r1, r2
        case Instructions::MOV_REG_REG: {
            auto registerFrom = static_cast<Registers>((Fetch() % registers.size()));
            auto registerTo = static_cast<Registers>((Fetch() % registers.size()));
            auto value = GetRegister(registerFrom);
            SetRegister(registerTo, value);
            break;
        }

        // move register value into memory address e.g.: MOV r1, 0xABCD
        case Instructions::MOV_REG_MEM: {
            auto reg = static_cast<Registers>((Fetch() % registers.size()));
            auto address = Fetch16();
            auto value = GetRegister(reg);
            memory->SetValue16(address, value);
            break;
        }

        // move value at a memory address into a register e.g.: MOV 0xABCD, r1
        case Instructions::MOV_MEM_REG: {
            auto address = Fetch16();
            auto reg = static_cast<Registers>((Fetch() % registers.size()));
            auto value = memory->GetValue16(address);
            SetRegister(reg, value);
            break;
        }

        // add register values together, put into Registers::acc e.g.: ADD r1, r2
        case Instructions::ADD_REG_REG: {
            auto register1 = static_cast<Registers>(Fetch());
            auto register2 = static_cast<Registers>(Fetch());
            auto register1Value = GetRegister(register1);
            auto register2Value = GetRegister(register2);
            SetRegister(Registers::acc, register1Value + register2Value);
            break;
        }

        // jump to the given address if the given literal is not equal to Registers::acc, e.g.: JNE {literal} {address} | JNE 0xABCD 0x1234
        case Instructions::JMP_NOT_EQ: {
            auto compareValue = Fetch16();
            auto jmpAddress = Fetch16();

            if (compareValue != GetRegister(Registers::acc)) {
                SetRegister(Registers::pc, jmpAddress);
            }

            break;
        }
    }
}

void CPU::Step() {
    auto instruction = Fetch();
    Execute(instruction);
}

void CPU::Debug() {
    printf("----------\nDEBUG CPU\n");
    for (auto const& [key, val] : registers) {
        printf("0x%x: 0x%x\n", key, val);
    }
    printf("----------\n");
}