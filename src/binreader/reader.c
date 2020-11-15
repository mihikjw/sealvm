#include "binreader/reader.h"

#include <stdlib.h>

// BR_EXIT_SUCCESS is the status code returned when we succesfully loaded a program into memory
#define BR_EXIT_SUCCESS 0
// BR_EXIT_FAILURE is the status code returned when we fail to load a program into memory (error printed to `stderr`)
#define BR_EXIT_FAILURE 1

uint8_t BR_FromFile(BinReader* this, const char* filePath) {
    if (!this) {
        fprintf(this->_logOut, "BinReader: `this` is NULL\n");
        return BR_EXIT_FAILURE;
    }
    if (!filePath) {
        fprintf(this->_logOut, "BinReader: `filePath` is NULL\n");
        return BR_EXIT_FAILURE;
    }

    fprintf(this->_logOut, "BinReader::FromFile: Not Implemented\n");
    return BR_EXIT_FAILURE;
}

BinReader* NewBinReader(uint8_t* memory, FILE* logOut) {
    if (!memory || !logOut) {
        return NULL;
    }

    BinReader* result = malloc(sizeof(BinReader));
    if (!result) {
        return NULL;
    }

    result->_memory = memory;
    result->_logOut = logOut;
    result->FromFile = &BR_FromFile;
    return result;
}
