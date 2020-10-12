#ifndef SEALVM_MEMORYMAPPER_HPP
#define SEALVM_MEMORYMAPPER_HPP

#include <stdint.h>
#include <vector>
#include <memory>
#include <stdexcept>
#include <string>

#include "sealvm/memoryRegion.hpp"
#include "sealvm/memoryDevice.hpp"

namespace SealVM {

class MemoryMapper: public MemoryDevice {
    public:
    MemoryMapper(std::vector<uint8_t>* buffer);
    ~MemoryMapper() = default;

    // Map maps the given device to memory with the given start & end addresses
    void Map(MemoryDevice* device, const uint16_t startAddr, const uint16_t endAddr, bool remap = true);

    // GetValue16 returns the 16-bit value value held at the given address
    const uint16_t GetValue16(const uint16_t addr);

    // GetValue16 returns the 8-bit value value held at the given address
    const uint8_t GetValue(const uint16_t addr);

    // SetValue sets the 16-bit value at the given address
    void SetValue16(const uint16_t addr, const uint16_t value);

    // SetValue sets the 8-bit value at the given address
    void SetValue(const uint16_t addr, const uint8_t value);

    private:
    // findRegion locates the MemoryRegion containing the requested address
    MemoryRegion* findRegion(const uint16_t addr); 

    // regions contains the allocated memory regions
    std::vector<std::unique_ptr<MemoryRegion>> regions;
};

}

#endif  // SEALVM_MEMORYMAPPER_HPP