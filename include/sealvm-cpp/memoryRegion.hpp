#ifndef SEALVM_MEMORYREGION_HPP
#define SEALVM_MEMORYREGION_HPP

#include <stdint.h>
#include <vector>

#include "sealvm-cpp/memoryDevice.hpp"

namespace SealVM {

class MemoryRegion : public MemoryDevice {
    public:
    MemoryRegion(MemoryDevice* device, const uint16_t startAddr, const uint16_t endAddr, bool remap);
    ~MemoryRegion() = default;

    MemoryDevice* Device;
    uint16_t StartAddr;
    uint16_t EndAddr;
    bool Remap;

    // GetValue16 returns the 16-bit value from the given address and given address + 1
    const uint16_t GetValue16(const uint16_t addr);

    // GetValue returns the 8-bit value from the given address
    const uint8_t GetValue(const uint16_t addr);

    // SetValue16 sets the given 16-bit value at the given address and given address + 1
    void SetValue16(const uint16_t addr, const uint16_t value);

    // SetValue sets the given 8-bit value at the given address
    void SetValue(const uint16_t addr, const uint8_t value);
};

} // namespace SealVM

#endif // SEALVM_MEMORYREGION_HPP