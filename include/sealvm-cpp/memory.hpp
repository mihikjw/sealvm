#ifndef SEALVM_SEALVM_MEMORY_HPP
#define SEALVM_SEALVM_MEMORY_HPP

#include <cstdio>
#include <memory>
#include <stdint.h>
#include <vector>

#include "sealvm-cpp/defines.hpp"
#include "sealvm-cpp/memoryDevice.hpp"

namespace SealVM {

class Memory : public MemoryDevice {
    public:
    Memory(std::vector<uint8_t>* buffer);
    ~Memory() = default;

    // GetValue returns the value at the given memory address
    const uint8_t GetValue(const uint16_t address);

    // GetValue16 returns a 16 bit value from the given memory address (and address +1)
    const uint16_t GetValue16(const uint16_t address);

    // SetValue sets the given value at the given memory address
    void SetValue(const uint16_t address, const uint8_t value);

    // SetValue16 sets the given 16-bit value at the given memory address (address and address + 1 are occupied)
    void SetValue16(const uint16_t address, const uint16_t value);

    // Debug prints the given memory address and the following 7 addresses to the console
    void Debug(const uint16_t address, uint8_t n = 8);
};

} // namespace SealVM

#endif // SEALVM_SEALVM_MEMORY_HPP