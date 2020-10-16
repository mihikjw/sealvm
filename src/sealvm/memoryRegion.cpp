#include "sealvm/memoryRegion.hpp"

using namespace SealVM;

MemoryRegion::MemoryRegion(MemoryDevice* device, const uint16_t startAddr, const uint16_t endAddr, bool remap) : MemoryDevice(device->Buffer()) {
    this->Device = device;
    this->StartAddr = startAddr;
    this->EndAddr = endAddr;
    this->Remap = remap;
}

const uint16_t MemoryRegion::GetValue16(const uint16_t addr) {
    auto val1 = Device->Buffer()->at(addr);
    auto val2 = Device->Buffer()->at(addr + 1);
    return val1 << 8 | val2;
}

const uint8_t MemoryRegion::GetValue(const uint16_t addr) { return Device->Buffer()->at(addr); }

void MemoryRegion::SetValue16(const uint16_t addr, const uint16_t value) { Device->SetValue16(addr, value); }

void MemoryRegion::SetValue(const uint16_t addr, const uint8_t value) { Device->SetValue(addr, value); }