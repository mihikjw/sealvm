#ifndef SEALVM_SEALVM_BINREADER_H
#define SEALVM_SEALVM_BINREADER_H

#include <stdint.h>

#include "sealvm/errors.h"

// BinReader is an object capable of loading a bytecode program into memory for execution
typedef struct BinReader {
    // _memory is an internal link to the main program memory
    uint8_t* _memory;

    // FromFile reads bytecode from the given file and loads into memory from position 0 ready for execution - will only work on linux
    ErrCode (*FromFile)(struct BinReader*, const char* filePath);
} BinReader;

// NewBinReader is a constructor for the `BinReader` object, requires pointer to program memory buffer
BinReader* NewBinReader(uint8_t* memory);

#endif // SEALVM_SEALVM_BINREADER_H
