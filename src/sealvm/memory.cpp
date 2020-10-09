#include "sealvm/memory.hpp"

using namespace SealVM;

Memory::Memory(const unsigned int sizeBytes) : buffer(sizeBytes, SealVM::ZERO_MEMORY) {}

const uint8_t Memory::GetValue(const uint16_t address) { return buffer[address]; }

const uint16_t Memory::GetValue16(const uint16_t address) {
    uint8_t part1 = buffer[address];
    uint8_t part2 = buffer[address + 1];
    return part1 << 8 | part2;
}

void Memory::SetValue(const uint16_t address, const uint8_t value) { buffer[address] = value; }

void Memory::SetValue16(const uint16_t address, const uint16_t value) {
    auto part1 = (uint8_t)(value >> 8);
    auto part2 = (uint8_t)value;
    buffer[address] = part1;
    buffer[address + 1] = part2;
}

void Memory::Debug(const uint16_t address, uint8_t n) {
    uint16_t i = 0;
    auto max = (buffer.begin() + address) + n;

    printf("----------\nDEBUG MEMORY\n");
    for (auto it = buffer.begin() + address; it != max; it++) {
        printf("0x%x: 0x%x\n", address + i, *it);
        i++;
    }
    printf("----------\n");
}

uint8_t Memory::Size() { return buffer.size(); }