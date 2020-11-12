#ifndef SEALVM_MEMORYDEVICE_HPP
#define SEALVM_MEMORYDEVICE_HPP

#include <stdint.h>
#include <vector>

namespace SealVM {

class MemoryDevice {
    public: 
    MemoryDevice(std::vector<uint8_t>* buffer){ this->buffer = buffer; }
    virtual ~MemoryDevice() = default;

    // GetValue returns the value at the given memory address
    virtual const uint8_t GetValue(const uint16_t address) = 0;

    // GetValue16 returns a 16 bit value from the given memory address (and address +1)
    virtual const uint16_t GetValue16(const uint16_t address) = 0;

    // SetValue sets the given value at the given memory address
    virtual void SetValue(const uint16_t address, const uint8_t value) = 0;

    // SetValue16 sets the given 16-bit value at the given memory address (address and address + 1 are occupied)
    virtual void SetValue16(const uint16_t address, const uint16_t value) = 0;

    // Size returns the number of bytes used for memory (this->buffer.size())
    uint8_t Size(){ return buffer->size(); }

    // Buffer returns a pointer to the memory buffer
    std::vector<uint8_t>* Buffer(){ return buffer;}

    protected:
    std::vector<uint8_t>* buffer;
};

}

#endif // SEALVM_MEMORYDEVICE_HPP