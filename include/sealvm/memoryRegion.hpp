#ifndef SEALVM_MEMORYREGION_HPP
#define SEALVM_MEMORYREGION_HPP

#include <stdint.h>
#include <vector>

namespace SealVM {

class MemoryRegion {
    public:
    MemoryRegion(std::vector<uint8_t> device, const uint16_t startAddr, const uint16_t endAddr, bool remap);
    ~MemoryRegion() = default;

    std::vector<uint8_t> Device;
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

}

#endif  // SEALVM_MEMORYREGION_HPP