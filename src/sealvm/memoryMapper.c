#include "sealvm/memoryMapper.h"

#include <stdlib.h>

MemoryMapper* NewMemoryMapper(Memory* mem) {
    if (!mem) {
        return NULL;
    }

    MemoryMapper* result = malloc(sizeof(MemoryMapper));
    result->_memory = mem;

    return result;
}