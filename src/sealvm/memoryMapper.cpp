#include "sealvm/memoryMapper.hpp"

using namespace SealVM;

MemoryMapper::MemoryMapper(std::vector<uint8_t>* buffer) : MemoryDevice(buffer) {}  

void MemoryMapper::Map(MemoryDevice* device, const uint16_t startAddr, const uint16_t endAddr, bool remap){
    auto region = std::make_unique<MemoryRegion>(device, startAddr, endAddr, remap);
    regions.emplace(regions.begin(), std::move(region));
    // return a function to unmap the region ?
}

MemoryRegion* MemoryMapper::findRegion(const uint16_t addr) { 
    for (auto const &r: regions) {
        if (addr >= r->StartAddr && addr <= r->EndAddr) {
            return r.get();
        }
    }

    // unmapped, but CPU has still tried to read/write from it
    throw std::runtime_error("requested address " + std::to_string(addr) + " is not mapped");
}

const uint16_t MemoryMapper::GetValue16(const uint16_t addr) { 
    auto region = findRegion(addr);
    /* 
    internally, if remap is enabled, regions start a 0x0000 but overall memory could be higher, 
        so we need to take the start address from the requested address. This same logic applies to all get/set funcs
    region covers 0x1000 - 0x1080
    requested 0x1030
    need to find regions address so 0x1030 - 0x1000
    finalAddr would be 0x30 within the region
    */
    auto finalAddr = region->Remap ? addr - region->StartAddr : addr;
    return region->GetValue16(finalAddr);
}

const uint8_t MemoryMapper::GetValue(const uint16_t addr) { 
    auto region = findRegion(addr);
    auto finalAddr = region->Remap ? addr - region->StartAddr : addr;
    return region->GetValue(finalAddr);
} 

void MemoryMapper::SetValue16(const uint16_t addr, const uint16_t value) {
    auto region = findRegion(addr);
    auto finalAddr = region->Remap ? addr - region->StartAddr : addr;
    region->SetValue16(finalAddr, value);
}

void MemoryMapper::SetValue(const uint16_t addr, const uint8_t value) {
    auto region = findRegion(addr);
    auto finalAddr = region->Remap ? addr - region->StartAddr : addr;
    region->SetValue(finalAddr, value);
}