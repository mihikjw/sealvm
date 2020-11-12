#ifndef SEALVM_SEALVM_MEMORYMAPPER_H
#define SEALVM_SEALVM_MEMORYMAPPER_H

#include <stdbool.h>

#include "sealvm/deviceType.h"
#include "sealvm/errors.h"
#include "sealvm/memory.h"

typedef struct MemoryMapper {
    // _memory is an internal link to the Memory object
    Memory* _memory;

    // Map maps the given device to a type
    ErrCode (*Map)(struct MemoryMapper*, void* device, DeviceType type, const uint16_t startAddr, const uint16_t endAddr, bool remap);

} MemoryMapper;

MemoryMapper* NewMemoryMapper(Memory* mem);

#endif // SEALVM_SEALVM_MEMORYMAPPER_H