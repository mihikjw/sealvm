#ifndef SEALVM_BINREADER_READER_H
#define SEALVM_BINREADER_READER_H

#include <stdint.h>
#include <stdio.h>

// BinReader is an object capable of loading a bytecode program into memory for execution
typedef struct BinReader {
    // _memory is an internal link to the main program memory
    uint8_t* _memory;
    // _logOut is an internal object for outputting error messages
    FILE* _logOut;

    // FromFile reads bytecode from the given file and loads into memory from position 0 ready for execution
    uint8_t (*FromFile)(struct BinReader*, const char* filePath);
} BinReader;

// NewBinReader is a constructor for the `BinReader` object
BinReader* NewBinReader(uint8_t* memory, FILE* logOut);

#endif // SEALVM_BINREADER_READER_H