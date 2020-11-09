#include "sealvm/cpu.hpp"

using namespace SealVM;

CPU::CPU(MemoryDevice* memory) noexcept {
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
        // move literal value into register e.g.: MOV $1234, r1
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

        // move register value into memory address e.g.: MOV r1, &ABCD
        case Instructions::MOV_REG_MEM: {
            auto reg = fetchRegisterIndex();
            auto address = fetch16();
            auto val = GetRegister(reg);
            memory->SetValue16(address, val);
            break;
        }

        // move value at a memory address into a register e.g.: MOV &ABCD, r1
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

        // jump to the given address if the given literal is not equal to Registers::acc, e.g.: JNE {literal} {address} | JNE $ABCD &1234
        case Instructions::JNE_LIT: {
            auto compareValue = fetch16();
            auto jmpAddress = fetch16();
            if (compareValue != GetRegister(Registers::acc)) {
                SetRegister(Registers::pc, jmpAddress);
            }
            break;
        }

        // push a literal value onto the stack e.g.: PSH $1234
        case Instructions::PSH_LIT: {
            auto val = fetch16();
            pushStack(val);
            break;
        }

        // push a register value onto the stack e.g.: PSH r1
        case Instructions::PSH_REG: {
            auto reg = fetchRegisterIndex();
            auto val = GetRegister(reg);
            pushStack(val);
            break;
        }

        // pop takes the value from the stack pointer and places it in the given register e.g.: POP r1
        case Instructions::POP: {
            auto reg = fetchRegisterIndex();
            auto val = popStack();
            SetRegister(reg, val);
            break;
        }

        // cal to a literal address e.g.: CAL $ABCD
        case Instructions::CAL_LIT: {
            auto addr = fetch16();
            pushStateStack();
            SetRegister(Registers::pc, addr);
            break;
        }

        // cal to an address held in a register e.g.: CAL r1
        case Instructions::CAL_REG: {
            auto reg = fetchRegisterIndex();
            auto addr = GetRegister(reg);
            pushStateStack();
            SetRegister(Registers::sp, addr); // should be pc ?
            break;
        }

        // return to the location the immediate prior CAL command was called e.g.: RET
        case Instructions::RET: {
            popStateStack();
            break;
        }

        // exit the CPU e.g.: HLT
        case Instructions::HLT: {
            return false;
        }

        // move literal value to memory e.g: MOV $1234 &ABCD
        case Instructions::MOV_LIT_MEM: {
            auto val = fetch16();
            auto addr = fetch16();
            memory->SetValue16(addr, val);
            break;
        }

        // move register pointer to register e.g.: MOV r1, r2
        case Instructions::MOV_REG_PTR_REG: {
            auto r1 = fetchRegisterIndex();
            auto r2 = fetchRegisterIndex();
            auto ptr = GetRegister(r1);
            auto val = memory->GetValue16(ptr);
            SetRegister(r2, val);
            break;
        }

        // move literal at (literal + register) to register e.g.: MOV $ABCD, r1, r2
        case Instructions::MOV_LIT_OFF_REG: {
            auto baseAddr = fetch16();
            auto r1 = fetchRegisterIndex();
            auto r2 = fetchRegisterIndex();
            auto offset = GetRegister(r1);
            auto value = memory->GetValue16(baseAddr + offset);
            SetRegister(r2, value);
            break;
        }

        // add literal to register e.g.: ADD $1234, r1
        case Instructions::ADD_LIT_REG: {
            auto lit = fetch16();
            auto reg = fetchRegisterIndex();
            auto val = GetRegister(reg);
            SetRegister(Registers::acc, lit + val);
            break;
        }

        // substract literal from register e.g.: SUB $1234, r1
        case Instructions::SUB_LIT_REG: {
            auto lit = fetch16();
            auto reg = fetchRegisterIndex();
            auto val = GetRegister(reg);
            SetRegister(Registers::acc, lit - val);
            break;
        }

        // subtract register from literal e.g.: SUB r1, $1234
        case Instructions::SUB_REG_LIT: {
            auto reg = fetchRegisterIndex();
            auto lit = fetch16();
            auto val = GetRegister(reg);
            SetRegister(Registers::acc, val - lit);
            break;
        }

        // subtract register from registers e.g.: SUB r1, r2
        case Instructions::SUB_REG_REG: {
            auto r1 = fetchRegisterIndex();
            auto r2 = fetchRegisterIndex();
            auto val1 = GetRegister(r1);
            auto val2 = GetRegister(r2);
            SetRegister(Registers::acc, val1 - val2);
            break;
        }

        // multiply a literal by a registers e.g.: MUL $1234, r1
        case Instructions::MUL_LIT_REG: {
            auto lit = fetch16();
            auto reg = fetchRegisterIndex();
            auto val = GetRegister(reg);
            SetRegister(Registers::acc, lit * val);
            break;
        }

        // multiple a register by a register e.g.: MUL r1, r2
        case Instructions::MUL_REG_REG: {
            auto r1 = fetchRegisterIndex();
            auto r2 = fetchRegisterIndex();
            auto val1 = GetRegister(r1);
            auto val2 = GetRegister(r2);
            SetRegister(Registers::acc, val1 * val2);
            break;
        }

        // increment a register by 1 e.g.: INC r1
        case Instructions::INC_REG: {
            auto reg = fetchRegisterIndex();
            auto val = GetRegister(reg);
            SetRegister(reg, val + 1);
            break;
        }

        // decrement a register by 1 e.g.: DEC r1
        case Instructions::DEC_REG: {
            auto reg = fetchRegisterIndex();
            auto val = GetRegister(reg);
            SetRegister(reg, val - 1);
            break;
        }

        // left shift register by literal (in place) e.g.: LSF r1, $1234
        case Instructions::LSF_REG_LIT: {
            auto reg = fetchRegisterIndex();
            auto lit = fetch16();
            auto val = GetRegister(reg);
            SetRegister(r1, val << lit);
            break;
        }

        // left shift register by register (in place) e.g.: LSF r1, r2
        case Instructions::LSF_REG_REG: {
            auto r1 = fetchRegisterIndex();
            auto r2 = fetchRegisterIndex();
            auto val1 = GetRegister(r1);
            auto val2 = GetRegister(r2);
            SetRegister(r1, val1 << val2);
            break;
        }

        // right shift register by literal (in place) e.g.: RSF r1, $1234
        case Instructions::RSF_REG_LIT: {
            auto reg = fetchRegisterIndex();
            auto lit = fetch16();
            auto val = GetRegister(reg);
            SetRegister(r1, val >> lit);
            break;
        }

        // right shift register by register (in place) e.g.: RSF r1, r2
        case Instructions::RSF_REG_REG: {
            auto r1 = fetchRegisterIndex();
            auto r2 = fetchRegisterIndex();
            auto val1 = GetRegister(r1);
            auto val2 = GetRegister(r2);
            SetRegister(r1, val1 >> val2);
            break;
        }

        // and register with literal e.g.: AND r1, $1234
        case Instructions::AND_REG_LIT: {
            auto reg = fetchRegisterIndex();
            auto lit = fetch16();
            auto val = GetRegister(reg);
            SetRegister(Registers::acc, val & lit);
            break;
        }

        // and register with register e.g.: AND r1, r2
        case Instructions::AND_REG_REG: {
            auto r1 = fetchRegisterIndex();
            auto r2 = fetchRegisterIndex();
            auto val1 = GetRegister(r1);
            auto val2 = GetRegister(r2);
            SetRegister(Registers::acc, val1 & val2);
            break;
        }

        // or register with literal e.g.: OR r1, $1234
        case Instructions::OR_REG_LIT: {
            auto reg = fetchRegisterIndex();
            auto lit = fetch16();
            auto val = GetRegister(reg);
            SetRegister(Registers::acc, val | lit);
            break;
        }

        // or register with register e.g.: OR r1, r2
        case Instructions::OR_REG_REG: {
            auto r1 = fetchRegisterIndex();
            auto r2 = fetchRegisterIndex();
            auto val1 = GetRegister(r1);
            auto val2 = GetRegister(r2);
            SetRegister(Registers::acc, val1 | val2);
            break;
        }

        // xor register with literal e.g.: XOR r1, $1234
        case Instructions::XOR_REG_LIT: {
            auto reg = fetchRegisterIndex();
            auto lit = fetch16();
            auto val = GetRegister(reg);
            SetRegister(Registers::acc, val ^ lit);
            break;
        }

        // xor register with register e.g.: XOR r1, r2
        case Instructions::XOR_REG_REG: {
            auto r1 = fetchRegisterIndex();
            auto r2 = fetchRegisterIndex();
            auto val1 = GetRegister(r1);
            auto val2 = GetRegister(r2);
            SetRegister(Registers::acc, val1 ^ val2);
            break;
        }

        // not (invert) register e.g.: NOT r1
        case Instructions::NOT: {
            auto reg = fetchRegisterIndex();
            auto val = GetRegister(reg);
            uint16_t res = (~val) & 0xffff; // only want bottom 16 bits incase any funky conversion happens
            SetRegister(Registers::acc, res);
            break;
        }

        // jmp if register not equal to acc e.g.: JNE r1, &1234
        case Instructions::JNE_REG: {
            auto reg = fetchRegisterIndex();
            auto val = GetRegister(reg);
            auto jmpAddr = fetch16();
            if (val != GetRegister(Registers::acc)) {
                SetRegister(Registers::pc, jmpAddr);
            }
            break;
        }

        // jmp if register equal to acc e.g.: JEQ r1, &1234
        case Instructions::JEQ_REG: {
            auto reg = fetchRegisterIndex();
            auto val = GetRegister(reg);
            auto jmpAddr = fetch16();
            if (val == GetRegister(Registers::acc)) {
                SetRegister(Registers::pc, jmpAddr);
            }
            break;
        }

        // jmp if literal equal to acc e.g.: JEQ $ABCD, &1234
        case Instructions::JEQ_LIT: {
            auto lit = fetch16();
            auto jmpAddr = fetch16();
            if (lit == GetRegister(Registers::acc)) {
                SetRegister(Registers::pc, jmpAddr);
            }
            break;
        }

        // jmp if register less than acc e.g.: JLT r1, &1234
        case Instructions::JLT_REG: {
            auto reg = fetchRegisterIndex();
            auto val = GetRegister(reg);
            auto jmpAddr = fetch16();
            if (val < GetRegister(Registers::acc)) {
                SetRegister(Registers::pc, jmpAddr);
            }
            break;
        }

        // jmp if literal less than acc e.g.: JLT $ABCD, &1234
        case Instructions::JLT_LIT: {
            auto lit = fetch16();
            auto jmpAddr = fetch16();
            if (lit < GetRegister(Registers::acc)) {
                SetRegister(Registers::pc, jmpAddr);
            }
            break;
        }

        // jmp if register greater than acc e.g.: JGT r1, &1234
        case Instructions::JGT_REG: {
            auto reg = fetchRegisterIndex();
            auto val = GetRegister(reg);
            auto jmpAddr = fetch16();
            if (val > GetRegister(Registers::acc)) {
                SetRegister(Registers::pc, jmpAddr);
            }
            break;
        }

        // jmp if literal greater than acc e.g.: JGT $ABCD, &1234
        case Instructions::JGT_LIT: {
            auto lit = fetch16();
            auto jmpAddr = fetch16();
            if (lit > GetRegister(Registers::acc)) {
                SetRegister(Registers::pc, jmpAddr);
            }
            break;
        }

        // jmp if register less than or equal to acc e.g.: JLE r1, &1234
        case Instructions::JLE_REG: {
            auto reg = fetchRegisterIndex();
            auto val = GetRegister(reg);
            auto jmpAddr = fetch16();
            if (val <= GetRegister(Registers::acc)) {
                SetRegister(Registers::pc, jmpAddr);
            }
            break;
        }

        // jmp if literal less than or equal to acc e.g.: JLE $ABCD, &1234
        case Instructions::JLE_LIT: {
            auto lit = fetch16();
            auto jmpAddr = fetch16();
            if (lit <= GetRegister(Registers::acc)) {
                SetRegister(Registers::pc, jmpAddr);
            }
            break;
        }

        // jmp if register greater than or equal to acc e.g.: JGE r1, &1234
        case Instructions::JGE_REG: {
            auto reg = fetchRegisterIndex();
            auto val = GetRegister(reg);
            auto jmpAddr = fetch16();
            if (val >= GetRegister(Registers::acc)) {
                SetRegister(Registers::pc, jmpAddr);
            }
            break;
        }

        // jmp if literal greater than or equal to acc e.g.: JGE $ABCD, &1234
        case Instructions::JGE_LIT: {
            auto lit = fetch16();
            auto jmpAddr = fetch16();
            if (lit >= GetRegister(Registers::acc)) {
                SetRegister(Registers::pc, jmpAddr);
            }
            break;
        }
    }

    return true;
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

void CPU::pushStack(const uint16_t value) {
    auto sp = GetRegister(Registers::sp);
    memory->SetValue16(sp, value);
    SetRegister(Registers::sp, sp - 2);
    stackFrameSize += 2;
}

const uint16_t CPU::popStack() {
    auto sp = GetRegister(Registers::sp) + 2;
    auto val = memory->GetValue16(sp);
    SetRegister(Registers::sp, sp);
    stackFrameSize -= 2;
    return val;
}

void CPU::pushStateStack() {
    pushStack(GetRegister(Registers::r1));
    pushStack(GetRegister(Registers::r2));
    pushStack(GetRegister(Registers::r3));
    pushStack(GetRegister(Registers::r4));
    pushStack(GetRegister(Registers::r5));
    pushStack(GetRegister(Registers::r6));
    pushStack(GetRegister(Registers::r7));
    pushStack(GetRegister(Registers::r8));

    // return address
    pushStack(GetRegister(Registers::pc));

    // size of the stack frame, + 2 to include this value
    pushStack(stackFrameSize + 2);

    // set fp to the current stack location
    SetRegister(Registers::fp, GetRegister(Registers::sp));

    // reset so if our CAL includes a subsiquent CAL it it will still work
    stackFrameSize = 0;
}

void CPU::popStateStack() {
    auto fp = GetRegister(Registers::fp);
    SetRegister(Registers::sp, fp);

    // head of the stack will be the frame size
    stackFrameSize = popStack();
    auto tmpFrameSize = stackFrameSize;

    // next is program counter
    SetRegister(Registers::pc, popStack());

    // then general purpose registers in reverse to how we set them
    SetRegister(Registers::r8, popStack());
    SetRegister(Registers::r7, popStack());
    SetRegister(Registers::r6, popStack());
    SetRegister(Registers::r5, popStack());
    SetRegister(Registers::r4, popStack());
    SetRegister(Registers::r3, popStack());
    SetRegister(Registers::r2, popStack());
    SetRegister(Registers::r1, popStack());

    // return sp to just before we pushed anything at all
    auto nArgs = popStack();
    for (unsigned int i = 0; i < nArgs; i++) {
        popStack();
    }

    // return frame pointer to the beginning of this frame
    SetRegister(Registers::fp, fp + tmpFrameSize);
}
