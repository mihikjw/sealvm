#include "sealvm/memory.hpp"

using namespace SealVM;

Memory::Memory(std::vector<uint8_t>* buffer) : MemoryDevice(buffer) {}

const uint8_t Memory::GetValue(const uint16_t address) { return buffer->at(address); }

const uint16_t Memory::GetValue16(const uint16_t address) { 
    uint8_t part1 = buffer->at(address);
    uint8_t part2 = buffer->at(address + 1);
    return part1 << 8 | part2;
}

void Memory::SetValue(const uint16_t address, const uint8_t value) { buffer->at(address) = value; }

void Memory::SetValue16(const uint16_t address, const uint16_t value) {
    auto part1 = (uint8_t)(value >> 8);
    auto part2 = (uint8_t)value;
    buffer->at(address) = part1;
    buffer->at(address + 1) = part2; 
}

void Memory::Debug(const uint16_t address, uint8_t n) {
    uint16_t i = 0;
    auto max = (buffer->begin() + address) + n;

    printf("----------\nDEBUG MEMORY\n");
    for (auto it = buffer->begin() + address; it != max; it++) {
        printf("0x%x: 0x%x\n", address + i, *it);
        i++;
    }
    printf("----------\n");
}