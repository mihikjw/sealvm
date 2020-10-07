#ifndef SEALVM_SEALVM_CPU_HPP
#define SEALVM_SEALVM_CPU_HPP

#include <array>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

#include "defines.hpp"
#include "instructions.hpp"
#include "memory.hpp"
#include "registers.hpp"

namespace SealVM {

// REGISTER_COUNT contains the number of registers in the SealVM CPU
constexpr unsigned short REGISTER_COUNT = 10;

class CPU {
    public:
    CPU(Memory* memory) noexcept;
    ~CPU() = default;

    // GetRegister returns the value currently held in the register 'name'
    const uint16_t GetRegister(const Registers name);

    // SetRegister sets the given value to the register 'name'
    void SetRegister(const Registers name, uint16_t value);

    // Fetch returns the next instruction in the pc register, increments program counter
    const uint8_t Fetch();

    // Fetch returns the next instruction in the pc register, increments program counter by 2
    const uint16_t Fetch16();

    // Execute executes the given instruction
    void Execute(const uint16_t instruction);

    // Step gets the next instruction & executes it
    void Step();

    // debug loops through the registers and outputs them to the console in a hex format
    void Debug();

    private:
    // memory is a pointer to the vm memory
    Memory* memory;

    // registers links the register name to an actual register
    std::map<Registers, uint16_t> registers{
      {Registers::acc, ZERO_MEMORY}, {Registers::pc, ZERO_MEMORY}, {Registers::r1, ZERO_MEMORY}, {Registers::r2, ZERO_MEMORY}, {Registers::r3, ZERO_MEMORY},
      {Registers::r4, ZERO_MEMORY},  {Registers::r5, ZERO_MEMORY}, {Registers::r6, ZERO_MEMORY}, {Registers::r7, ZERO_MEMORY},
    };
};

} // namespace SealVM

#endif // SEALVM_SEALVM_CPU_HPP