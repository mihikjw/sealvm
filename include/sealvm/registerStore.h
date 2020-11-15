#ifndef SEALVM_SEALVM_REGISTERSTORE_H
#define SEALVM_SEALVM_REGISTERSTORE_H

#include <stdint.h>

#include "sealvm/defines.h"
#include "sealvm/errors.h"
#include "sealvm/registers.h"

// RegisterStore represents the registers stored on the CPU
typedef struct RegisterStore {
    // _store contains the register mapping
    uint16_t _store[REGISTER_COUNT];

    // Set sets the given `reg` to the given `value`
    void (*Set)(struct RegisterStore*, const Registers reg, const uint16_t value);

    // Get returns the stored value for the given `reg`, sets `output` to the value
    ErrCode (*Get)(struct RegisterStore*, const Registers reg, uint16_t* output);
} RegisterStore;

// NewRegisterStore is a constructor for the RegisterStore object
RegisterStore* NewRegisterStore();

#endif // SEALVM_SEALVM_REGISTERSTORE_H