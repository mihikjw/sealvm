#ifndef SEALVM_SEALVM_CPU_HPP
#define SEALVM_SEALVM_CPU_HPP

#include <array>
#include <cstdint>
#include <cstdio>
#include <map>
#include <stdexcept>
#include <string>

#include "sealvm/defines.hpp"
#include "sealvm/instructions.hpp"
#include "sealvm/memoryDevice.hpp"
#include "sealvm/registers.hpp"

namespace SealVM {

class CPU {
    public:
    CPU(MemoryDevice* memory, uint16_t interruptVectorAddress = (uint16_t)0x1000) noexcept;
    ~CPU() = default;

    // GetRegister returns the value currently held in the register 'name'
    const uint16_t GetRegister(const Registers name);

    // SetRegister sets the given value to the register 'name'
    void SetRegister(const Registers name, uint16_t value);

    // Cycle gets the next instruction & executes it, returns whether its the last instruction or not
    bool Cycle();

    // debug loops through the registers and outputs them to the console in a hex format
    void Debug();

    void Run();

    private:
    // fetch returns the next instruction in the pc register, increments program counter
    const uint8_t fetch();

    // fetch returns the next instruction in the pc register, increments program counter by 2
    const uint16_t fetch16();

    // fetchRegisterIndex reads the next instruction in the pc register, returns it as a SealVM::Register, calls this->fetch()
    const Registers fetchRegisterIndex();

    // execute executes the given instruction, returns false if program is EOF
    bool execute(const uint16_t instruction);

    // pushStack pushes a value onto the stack
    void pushStack(const uint16_t value);

    // pushStateStack push's the current CPU state into the stack as a stack frame
    void pushStateStack();

    // popStack removes & returns the head of the stack
    const uint16_t popStack();

    // popStateStack returns the CPU state to that indicated by the fp register
    void popStateStack();

    void handleInterrupt(const uint16_t value);

    // memory is a pointer to the given memory device
    MemoryDevice* memory;

    // stackFrameSize tracks the size of the stack - could be used in a register but I don't want this to be user accessable
    uint8_t stackFrameSize;

    // registers links the register name to an actual register
    std::map<Registers, uint16_t> registers{
      {Registers::acc, ZERO_MEMORY}, {Registers::pc, ZERO_MEMORY}, {Registers::r1, ZERO_MEMORY},     {Registers::r2, ZERO_MEMORY},
      {Registers::r3, ZERO_MEMORY},  {Registers::r4, ZERO_MEMORY}, {Registers::r5, ZERO_MEMORY},     {Registers::r6, ZERO_MEMORY},
      {Registers::r7, ZERO_MEMORY},  {Registers::r8, ZERO_MEMORY}, {Registers::sp, FULL_MEMORY - 1}, {Registers::fp, FULL_MEMORY - 1},
      {Registers::im, FULL_MEMORY},
    };

    uint16_t interruptVectorAddress;
    bool isInInterrupt;
};

} // namespace SealVM

#endif // SEALVM_SEALVM_CPU_HPP