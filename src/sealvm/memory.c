#include "sealvm/memory.h"

#include <stdlib.h>

#include "sealvm/defines.h"

ErrCode M_Buffer(Memory* this, uint8_t** buffer, int* size) {
    if (!this) {
        return THIS_IS_NULL;
    }
    *buffer = this->_buffer;
    *size = this->_bufferSize;
    return NO_ERR;
}

ErrCode M_GetValue(Memory* this, const uint16_t address, uint8_t* valueOut) {
    if (!this) {
        return THIS_IS_NULL;
    }
    *valueOut = this->_buffer[address];
    return NO_ERR;
}

ErrCode M_GetValue16(Memory* this, const uint16_t address, uint16_t* valueOut) {
    if (!this) {
        return THIS_IS_NULL;
    }
    if (address == MEMORY_SIZE) {
        return ADDRESS_OUT_OF_BOUNDS;
    }

    uint8_t part1 = this->_buffer[address];
    uint8_t part2 = this->_buffer[address + 1];
    *valueOut = part1 << 8 | part2;
    return NO_ERR;
}

ErrCode M_SetValue(Memory* this, uint16_t address, uint8_t value) {
    if (!this) {
        return THIS_IS_NULL;
    }
    this->_buffer[address] = value;
    return NO_ERR;
}

ErrCode M_SetValue16(Memory* this, uint16_t address, uint16_t value) {
    if (!this) {
        return THIS_IS_NULL;
    }
    if (address == MEMORY_SIZE) {
        return ADDRESS_OUT_OF_BOUNDS;
    }

    uint8_t part1 = (uint8_t)(value >> 8);
    uint8_t part2 = (uint8_t)value;
    this->_buffer[address] = part1;
    this->_buffer[address + 1] = part2;
    return NO_ERR;
}

Memory* NewMemory(uint8_t* memory, const int memSize) {
    if (!memory || memSize <= 0) {
        return NULL;
    }

    Memory* result = malloc(sizeof(Memory));
    if (!result) {
        return NULL;
    }

    result->_buffer = memory;
    result->_bufferSize = memSize;
    result->GetValue16 = &M_GetValue16;
    result->GetValue = &M_GetValue;
    result->SetValue16 = &M_SetValue16;
    result->SetValue = &M_SetValue;
    result->Buffer = &M_Buffer;
    return result;
}
