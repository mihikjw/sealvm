#include "sealvm/cpu.hpp"

using namespace SealVM;

CPU::CPU(Memory* memory) noexcept {
    this->memory = memory;
    stackFrameSize = 0;
}

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

const uint8_t CPU::fetch() {
    auto nextInstructionAddress = GetRegister(Registers::pc);
    auto instruction = memory->GetValue(nextInstructionAddress);
    SetRegister(Registers::pc, (nextInstructionAddress + 1));
    return instruction;
}

const uint16_t CPU::fetch16() {
    auto nextInstructionAddress = GetRegister(Registers::pc);
    auto instruction1 = memory->GetValue(nextInstructionAddress);
    auto instruction2 = memory->GetValue(nextInstructionAddress + 1);
    SetRegister(Registers::pc, (nextInstructionAddress + 2));
    return instruction1 << 8 | instruction2;
}

const Registers CPU::fetchRegisterIndex() { return static_cast<Registers>((fetch() % registers.size())); }

bool CPU::execute(const uint16_t instruction) {
    switch (instruction) {
        // move literal value into register e.g.: MOV 0x1234, r1
        case Instructions::MOV_LIT_REG: {
            auto val = fetch16();
            auto reg = fetchRegisterIndex();
            SetRegister(reg, val);
            break;
        }

        // move register value into another register e.g.: MOV r1, r2
        case Instructions::MOV_REG_REG: {
            auto registerFrom = fetchRegisterIndex();
            auto registerTo = fetchRegisterIndex();
            auto val = GetRegister(registerFrom);
            SetRegister(registerTo, val);
            break;
        }

        // move register value into memory address e.g.: MOV r1, 0xABCD
        case Instructions::MOV_REG_MEM: {
            auto reg = fetchRegisterIndex();
            auto address = fetch16();
            auto val = GetRegister(reg);
            memory->SetValue16(address, val);
            break;
        }

        // move value at a memory address into a register e.g.: MOV 0xABCD, r1
        case Instructions::MOV_MEM_REG: {
            auto address = fetch16();
            auto reg = fetchRegisterIndex();
            auto val = memory->GetValue16(address);
            SetRegister(reg, val);
            break;
        }

        // add register values together, put into Registers::acc e.g.: ADD r1, r2
        case Instructions::ADD_REG_REG: {
            auto r1 = fetchRegisterIndex();
            auto r2 = fetchRegisterIndex();
            auto r1Val = GetRegister(r1);
            auto r2Val = GetRegister(r2);
            SetRegister(Registers::acc, r1Val + r2Val);
            break;
        }

        // jump to the given address if the given literal is not equal to Registers::acc, e.g.: JNE {literal} {address} | JNE 0xABCD #0x1234
        case Instructions::JMP_NOT_EQ: {
            auto compareValue = fetch16();
            auto jmpAddress = fetch16();
            if (compareValue != GetRegister(Registers::acc)) {
                SetRegister(Registers::pc, jmpAddress);
            }
            break;
        }

        // push a literal value onto the stack e.g.: PSH 0x1234
        case Instructions::PSH_LIT: {
            auto val = fetch16();
            push(val);
            break;
        }

        // push a register value onto the stack e.g.: PSH r1
        case Instructions::PSH_REG: {
            auto reg = fetchRegisterIndex();
            auto val = GetRegister(reg);
            push(val);
            break;
        }

        // pop takes the value from the stack pointer and places it in the given register e.g.: POP r1
        case Instructions::POP: {
            auto reg = fetchRegisterIndex();
            auto val = pop();
            SetRegister(reg, val);
            break;
        }

        // cal to a literal address e.g.: CAL 0xABCD
        case Instructions::CAL_LIT: {
            auto addr = fetch16();
            pushState();
            SetRegister(Registers::pc, addr);
            break;
        }

        // cal to an address held in a register e.g.: CAL r1
        case Instructions::CAL_REG: {
            auto reg = fetchRegisterIndex();
            auto addr = GetRegister(reg);
            pushState();
            SetRegister(Registers::sp, addr); // should be pc ?
            break;
        }

        // return to the location the immediate prior CAL command was called e.g.: RET
        case Instructions::RET: {
            popState();
            break;
        }

        // exit the CPU e.g.: HLT
        case Instructions::HLT: {
            return true;
        }
    }

    return false;
}

bool CPU::Cycle() {
    auto instruction = fetch();
    return execute(instruction);
}

void CPU::Debug() {
    printf("----------\nDEBUG CPU\n");
    for (auto const& [key, val] : registers) {
        printf("0x%x: 0x%x\n", key, val);
    }
    printf("----------\n");
}

void CPU::Run() {
    while (true) {
        if (!Cycle()) {
            break;
        }
    }
}

void CPU::push(const uint16_t value) {
    auto sp = GetRegister(Registers::sp);
    memory->SetValue16(sp, value);
    SetRegister(Registers::sp, sp - 2);
    stackFrameSize += 2;
}

const uint16_t CPU::pop() {
    auto sp = GetRegister(Registers::sp) + 2;
    auto val = memory->GetValue16(sp);
    SetRegister(Registers::sp, sp);
    stackFrameSize -= 2;
    return val;
}

void CPU::pushState() {
    push(GetRegister(Registers::r1));
    push(GetRegister(Registers::r2));
    push(GetRegister(Registers::r3));
    push(GetRegister(Registers::r4));
    push(GetRegister(Registers::r5));
    push(GetRegister(Registers::r6));
    push(GetRegister(Registers::r7));
    push(GetRegister(Registers::r8));

    // return address
    push(GetRegister(Registers::pc));

    // size of the stack frame, + 2 to include this value
    push(stackFrameSize + 2);

    // set fp to the current stack location
    SetRegister(Registers::fp, GetRegister(Registers::sp));

    // reset so if our CAL includes a subsiquent CAL it it will still work
    stackFrameSize = 0;
}

void CPU::popState() {
    auto fp = GetRegister(Registers::fp);
    SetRegister(Registers::sp, fp);

    // head of the stack will be the frame size
    stackFrameSize = pop();
    auto tmpFrameSize = stackFrameSize;

    // next is program counter
    SetRegister(Registers::pc, pop());

    // then general purpose registers in reverse to how we set them
    SetRegister(Registers::r8, pop());
    SetRegister(Registers::r7, pop());
    SetRegister(Registers::r6, pop());
    SetRegister(Registers::r5, pop());
    SetRegister(Registers::r4, pop());
    SetRegister(Registers::r3, pop());
    SetRegister(Registers::r2, pop());
    SetRegister(Registers::r1, pop());

    // return sp to just before we pushed anything at all
    auto nArgs = pop();
    for (unsigned int i = 0; i < nArgs; i++) {
        pop();
    }

    // return frame pointer to the beginning of this frame
    SetRegister(Registers::fp, fp + tmpFrameSize);
}