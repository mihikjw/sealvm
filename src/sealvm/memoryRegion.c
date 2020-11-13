#include "sealvm/memoryRegion.h"

#include <stdlib.h>

#include "sealvm/defines.h"
#include "sealvm/screenDevice.h"

ErrCode MR_GetValue(MemoryRegion* this, uint16_t address, uint8_t* valueOut);
ErrCode MR_GetValue16(MemoryRegion* this, uint16_t address, uint16_t* valueOut);
ErrCode MR_SetValue(MemoryRegion* this, uint16_t address, uint8_t value);
ErrCode MR_SetValue16(MemoryRegion* this, uint16_t address, uint16_t value);

MemoryRegion* NewMemoryRegion(void* device, const uint16_t deviceType, const uint16_t startAddr, const uint16_t endAddr, bool remap) {
    if (!device) {
        return NULL;
    }

    MemoryRegion* result = malloc(sizeof(MemoryRegion));
    if (!result) {
        return NULL;
    }

    result->Device = device;
    result->DeviceType = deviceType;
    result->StartAddr = startAddr;
    result->EndAddr = endAddr;
    result->Remap = remap;
    result->GetValue16 = &MR_GetValue16;
    result->GetValue = &MR_GetValue;
    result->SetValue16 = &MR_SetValue16;
    result->SetValue = &MR_SetValue;
    return result;
}

ErrCode MR_GetValue(MemoryRegion* this, uint16_t address, uint8_t* valueOut) {
    if (!this) {
        return THIS_IS_NULL;
    }
    if (address > MEMORY_SIZE) {
        return ADDRESS_OUT_OF_BOUNDS;
    }

    switch (this->DeviceType) {
        case Screen: {
            return DEVICE_FUNCTION_NOT_SUPPORTED;
        }
        default: {
            return DEVICE_TYPE_NOT_SUPPORTED;
        }
    }
}

ErrCode MR_GetValue16(MemoryRegion* this, uint16_t address, uint16_t* valueOut) {
    if (!this) {
        return THIS_IS_NULL;
    }
    if (address > MEMORY_SIZE || address + 1 > MEMORY_SIZE) {
        return ADDRESS_OUT_OF_BOUNDS;
    }

    switch (this->DeviceType) {
        case Screen: {
            return DEVICE_FUNCTION_NOT_SUPPORTED;
        }
        default: {
            return DEVICE_TYPE_NOT_SUPPORTED;
        }
    }
}

ErrCode MR_SetValue(MemoryRegion* this, uint16_t address, uint8_t value) {
    if (!this) {
        return THIS_IS_NULL;
    }
    if (address > MEMORY_SIZE) {
        return ADDRESS_OUT_OF_BOUNDS;
    }

    switch (this->DeviceType) {
        case Screen: {
            return DEVICE_FUNCTION_NOT_SUPPORTED;
        }
        default: {
            return DEVICE_TYPE_NOT_SUPPORTED;
        }
    }
}

ErrCode MR_SetValue16(MemoryRegion* this, uint16_t address, uint16_t value) {
    if (!this) {
        return THIS_IS_NULL;
    }
    if (address > MEMORY_SIZE || address + 1 > MEMORY_SIZE) {
        return ADDRESS_OUT_OF_BOUNDS;
    }

    switch (this->DeviceType) {
        case Screen: {
            ScreenDevice* device = (ScreenDevice*)this->Device;
            return device->SetValue16(device, address, value);
        }
        default: {
            return DEVICE_TYPE_NOT_SUPPORTED;
        }
    }
}
