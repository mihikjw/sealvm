#ifndef SEALVM_SEALVM_MEMORY_H
#define SEALVM_SEALVM_MEMORY_H

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "sealvm/defines.h"
#include "sealvm/errors.h"

typedef struct Memory {

    // buffer is the internal memory data structure
    uint8_t* _buffer;

    // bufferSize is the size of the internal memory data structure
    int _bufferSize;

    // Buffer provides access to the internal memory data structure, size arg is filled with memory size
    ERR_CODE (*Buffer)(struct Memory* this, uint8_t** buffer, int* size);

    // GetValue returns the value at the given memory address
    ERR_CODE (*GetValue)(struct Memory* this, const uint16_t address, uint8_t* valueOut);

    // GetValue16 returns a 16 bit value from the given memory address (and address +1)
    ERR_CODE (*GetValue16)(struct Memory* this, const uint16_t address, uint16_t* valueOut);

    // SetValue sets the given value at the given memory address
    ERR_CODE (*SetValue)(struct Memory* this, const uint16_t address, const uint8_t value);

    // SetValue16 sets the given 16-bit value at the given memory address (address and address + 1 are occupied)
    ERR_CODE (*SetValue16)(struct Memory* this, const uint16_t address, const uint16_t value);
} Memory;

// NewMemory is a constructor for the Memory type
Memory* NewMemory(uint8_t* memory, const int memSize);

#endif // SEALVM_SEALVM_MEMORY_H
