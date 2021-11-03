#ifndef SEALVM_SEALVM_MEMORYMAPPER_H
#define SEALVM_SEALVM_MEMORYMAPPER_H

#include <stdbool.h>

#include "sealvm/deviceType.h"
#include "sealvm/errors.h"
#include "sealvm/memory.h"
#include "sealvm/memoryRegion.h"

typedef struct MemoryMapper {
    // _memory is an internal link to the Memory object
    Memory* _memory;

    // _regions is an internal array containing all the mapped regions
    MemoryRegion* (*_regions)[];
    int _regionsSize;

    // Map maps the given device to a type
    ErrCode (*Map)(struct MemoryMapper*, void* device, DeviceType type, const uint16_t startAddr, const uint16_t endAddr, bool remap);

    // GetValue returns the value at the given memory address
    ErrCode (*GetValue)(struct MemoryMapper*, const uint16_t address, uint8_t* valueOut);

    // GetValue16 returns a 16 bit value from the given memory address (and address + 1)
    ErrCode (*GetValue16)(struct MemoryMapper*, const uint16_t address, uint16_t* valueOut);

    // SetValue sets the given value at the given memory address
    ErrCode (*SetValue)(struct MemoryMapper*, const uint16_t address, const uint8_t value);

    // SetValue16 sets the given 16-bit value at the given memory address (address and address + 1 are occupied)
    ErrCode (*SetValue16)(struct MemoryMapper*, const uint16_t address, const uint16_t value);

    // ClearRegions free's all memory allocated in the internal _regions array - should be called prior to `free`
    void (*ClearRegions)(struct MemoryMapper*);

} MemoryMapper;

// NewMemoryMapper is a constructor for MemoryMapper
MemoryMapper* NewMemoryMapper(Memory* mem);

#endif // SEALVM_SEALVM_MEMORYMAPPER_H
