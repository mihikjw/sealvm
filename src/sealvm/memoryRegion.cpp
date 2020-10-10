#include "sealvm/memoryRegion.hpp"

using namespace SealVM;

MemoryRegion::MemoryRegion(std::vector<uint8_t> device, const uint16_t startAddr, const uint16_t endAddr, bool remap) {
    this->Device = device; 
    this->StartAddr = startAddr; 
    this->EndAddr = endAddr; 
    this->Remap = remap;
}

const uint16_t MemoryRegion::GetValue16(const uint16_t addr) {
    auto val1 = Device[addr];
    auto val2 = Device[addr+1];
    return val1 << 8 | val2;
}

const uint8_t MemoryRegion::GetValue(const uint16_t addr) {
    return Device[addr];
}

void MemoryRegion::SetValue16(const uint16_t addr, const uint16_t value){
    auto part1 = (uint8_t)(value >> 8);
    auto part2 = (uint8_t)value;
    Device[addr] = part1;
    Device[addr+1] = part2;
}

void MemoryRegion::SetValue(const uint16_t addr, const uint8_t value) {
    Device[addr] = value; 
}