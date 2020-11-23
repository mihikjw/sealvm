#include "sealvm/binReader.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sealvm/defines.h"

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

    uint16_t memAddr = PROGRAM_START_ADDRESS;
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
