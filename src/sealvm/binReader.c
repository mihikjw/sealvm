#include "sealvm/binReader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// BR_EXIT_SUCCESS is the status code returned when we succesfully loaded a program into memory
#define BR_EXIT_SUCCESS 0
// BR_EXIT_FAILURE is the status code returned when we fail to load a program into memory (error printed to `stderr`)
#define BR_EXIT_FAILURE 1

ErrCode BR_FromFile(BinReader* this, const char* filePath) {
#if _POSIX_C_SOURCE >= 200809L
    if (!this) {
        return THIS_IS_NULL;
    }
    if (!filePath) {
        return FILEPATH_IS_NULL;
    }

    FILE* f = fopen(filePath, "r");
    if (!f) {
        return CANNOT_OPEN_FILE;
    }

    uint16_t memAddr = 0x0000;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    int startIndex = 0;
    char tmp[4];
    uint8_t val;

    while ((read = getline(&line, &len, f)) != -1) {
        for (register int i = 0; i < read; i++) {
            if (line[i] == ' ' || line[i] == '\n') {
                // convert value to int, add to memory
                strncpy(tmp, line + startIndex, i - startIndex);
                val = (uint8_t)strtol(tmp, NULL, 16);
                this->_memory[memAddr] = val;
                memset(tmp, '\0', sizeof(tmp));
                startIndex = i + 1;
                memAddr++;
            }
        }
    }

    // alloc in getline if `line` is NULL and `size` is 0, free even on failure
    free(line);
    fclose(f);
    return NO_ERR;
#else
    return NOT_IMPLEMENTED;
#endif
}

BinReader* NewBinReader(uint8_t* memory) {
    if (!memory) {
        return NULL;
    }

    BinReader* result = malloc(sizeof(BinReader));
    if (!result) {
        return NULL;
    }

    result->_memory = memory;
    result->FromFile = &BR_FromFile;
    return result;
}
