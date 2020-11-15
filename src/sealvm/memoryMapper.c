#include "sealvm/memoryMapper.h"

#include <stdlib.h>

// findRegion locates the MemoryRegion covering the given address
MemoryRegion* findRegion(MemoryMapper* this, uint16_t addr);

ErrCode MM_Map(MemoryMapper* this, void* device, DeviceType type, const uint16_t startAddr, const uint16_t endAddr, const bool remap) {
    if (!this) {
        return THIS_IS_NULL;
    }
    if (!device) {
        return DEVICE_IS_NULL;
    }

    MemoryRegion* region = NewMemoryRegion(device, type, startAddr, endAddr, remap);
    if (!region) {
        return CANNOT_CONSTRUCT;
    }

    MemoryRegion*(*regions)[] = malloc(this->_regionsSize++ * sizeof(MemoryRegion*));
    (*regions)[0] = region;

    // this is only ever called on program startup (i.e. regions are not mapped at program 'runtime', only read) so it
    //  makes sense to base this on arrays rather than a linkedlist or similar
    if (this->_regions) {
        for (register int i = 1; i < this->_regionsSize; i++) {
            (*regions)[i] = (*this->_regions)[i - 1];
        }
    }

    this->_regions = regions;

    return NO_ERR;
}

ErrCode MM_GetValue(MemoryMapper* this, uint16_t address, uint8_t* valueOut) {
    if (!this) {
        return THIS_IS_NULL;
    }

    MemoryRegion* region = findRegion(this, address);
    if (!region) {
        return REGION_NOT_FOUND;
    }

    /*
    internally, if remap is enabled, regions start a 0x0000 but overall memory could be higher,
        so we need to take the start address from the requested address. This same logic applies to all get/set funcs
    region covers 0x1000 - 0x1080
    requested 0x1030
    need to find regions address so 0x1030 - 0x1000
    finalAddr would be 0x30 within the region
    */
    uint16_t finalAddr = region->Remap ? address - region->StartAddr : address;
    return region->GetValue(region, finalAddr, valueOut);
}

ErrCode MM_GetValue16(MemoryMapper* this, uint16_t address, uint16_t* valueOut) {
    if (!this) {
        return THIS_IS_NULL;
    }

    MemoryRegion* region = findRegion(this, address);
    if (!region) {
        return REGION_NOT_FOUND;
    }

    uint16_t finalAddr = region->Remap ? address - region->StartAddr : address;
    return region->GetValue16(region, finalAddr, valueOut);
}

ErrCode MM_SetValue(MemoryMapper* this, uint16_t address, uint8_t value) {
    if (!this) {
        return THIS_IS_NULL;
    }

    MemoryRegion* region = findRegion(this, address);
    if (!region) {
        return REGION_NOT_FOUND;
    }

    uint16_t finalAddr = region->Remap ? address - region->StartAddr : address;
    return region->SetValue(region, address, value);
}

ErrCode MM_SetValue16(MemoryMapper* this, uint16_t address, uint16_t value) {
    if (!this) {
        return THIS_IS_NULL;
    }

    MemoryRegion* region = findRegion(this, address);
    if (!region) {
        return REGION_NOT_FOUND;
    }

    uint16_t finalAddr = region->Remap ? address - region->StartAddr : address;
    return region->SetValue16(region, address, value);
}

void MM_ClearRegions(MemoryMapper* this) {
    if (!this || !this->_regions) {
        return;
    }

    MemoryRegion* tmp;
    for (register int i = 0; i < this->_regionsSize; i++) {
        tmp = (*this->_regions)[i];
        if (tmp) {
            free(tmp);
        }
    }

    this->_regions = NULL;
}

MemoryMapper* NewMemoryMapper(Memory* mem) {
    if (!mem) {
        return NULL;
    }

    MemoryMapper* result = malloc(sizeof(MemoryMapper));
    if (!result) {
        return NULL;
    }

    result->_memory = mem;
    result->_regions = NULL;
    result->_regionsSize = 0;
    result->Map = &MM_Map;
    result->GetValue = &MM_GetValue;
    result->GetValue16 = &MM_GetValue16;
    result->SetValue16 = &MM_SetValue16;
    result->SetValue = &MM_SetValue;
    result->ClearRegions = &MM_ClearRegions;
    return result;
}

MemoryRegion* findRegion(MemoryMapper* this, const uint16_t addr) {
    if (this && this->_regions) {
        MemoryRegion* region;

        for (register int i = 0; i < this->_regionsSize; i++) {
            region = (*this->_regions)[i];
            if (region) {
                if (addr >= region->StartAddr && addr <= region->EndAddr) {
                    return region;
                }
            }
        }
    }

    return NULL;
}
