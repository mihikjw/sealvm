#ifndef SEALVM_SEALVM_MEMORY_H
#define SEALVM_SEALVM_MEMORY_H

#include <stdint.h>

#include "sealvm/errors.h"

typedef struct Memory {
    // buffer is the internal memory data structure
    uint8_t* _buffer;

    // bufferSize is the size of the internal memory data structure
    int _bufferSize;

    // Buffer provides access to the internal memory data structure, size arg is filled with memory size
    ErrCode (*Buffer)(struct Memory*, uint8_t** buffer, int* size);

    // GetValue returns the value at the given memory address
    ErrCode (*GetValue)(struct Memory*, const uint16_t address, uint8_t* valueOut);

    // GetValue16 returns a 16 bit value from the given memory address (and address + 1)
    ErrCode (*GetValue16)(struct Memory*, const uint16_t address, uint16_t* valueOut);

    // SetValue sets the given value at the given memory address
    ErrCode (*SetValue)(struct Memory*, const uint16_t address, const uint8_t value);

    // SetValue16 sets the given 16-bit value at the given memory address (address and address + 1 are occupied)
    ErrCode (*SetValue16)(struct Memory*, const uint16_t address, const uint16_t value);
} Memory;

// NewMemory is a constructor for the Memory type
Memory* NewMemory(uint8_t* memory, const int memSize);

#endif // SEALVM_SEALVM_MEMORY_H
