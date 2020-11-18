#ifndef SEALVM_SEALVM_MEMORYREGION_H
#define SEALVM_SEALVM_MEMORYREGION_H

#include <stdbool.h>
#include <stdint.h>

#include "sealvm/deviceType.h"
#include "sealvm/errors.h"

// MemoryRegion contains a region of memory mapped to a Device
typedef struct MemoryRegion {

    // GetValue returns the value at the given memory address
    ErrCode (*GetValue)(struct MemoryRegion*, const uint16_t address, uint8_t* valueOut);

    // GetValue16 returns a 16 bit value from the given memory address (and address + 1)
    ErrCode (*GetValue16)(struct MemoryRegion*, const uint16_t address, uint16_t* valueOut);

    // SetValue sets the given value at the given memory address
    ErrCode (*SetValue)(struct MemoryRegion*, const uint16_t address, const uint8_t value);

    // SetValue16 sets the given 16-bit value at the given memory address (address and address + 1 are occupied)
    ErrCode (*SetValue16)(struct MemoryRegion*, const uint16_t address, const uint16_t value);

    // DeviceType holds a flag for the type of device stored
    DeviceType DeviceType;

    // Device holds a pointer to the device, type indicated by `deviceType` flag
    void* Device;

    // StartAddr indicates the start memory address of the device
    uint16_t StartAddr;

    // EndAddr indicates the end memory address of the device
    uint16_t EndAddr;

    // Remap indicates whether the device supports remapping
    bool Remap;
} MemoryRegion;

// NewMemoryRegion is a construction for MemoryRegion
MemoryRegion* NewMemoryRegion(void* device, const uint16_t deviceType, const uint16_t startAddr, const uint16_t endAddr, bool remap);

#endif // SEALVM_SEALVM_MEMORYREGION_H