#include "sealvm/memory.h"

#include <stdlib.h>

#include "sealvm/defines.h"

ErrCode Buffer(struct Memory* this, uint8_t** buffer, int* size);
ErrCode GetValue(struct Memory* this, uint16_t address, uint8_t* valueOut);
ErrCode GetValue16(struct Memory* this, uint16_t address, uint16_t* valueOut);
ErrCode SetValue(struct Memory* this, uint16_t address, uint8_t value);
ErrCode SetValue16(struct Memory* this, uint16_t address, uint16_t value);

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
    result->GetValue16 = &GetValue16;
    result->GetValue = &GetValue;
    result->SetValue16 = &SetValue16;
    result->SetValue = &SetValue;
    result->Buffer = &Buffer;
    return result;
}

ErrCode Buffer(struct Memory* this, uint8_t** buffer, int* size) {
    if (!this) {
        return THIS_IS_NULL;
    }
    *buffer = this->_buffer;
    *size = this->_bufferSize;
    return NO_ERR;
}

ErrCode GetValue(struct Memory* this, const uint16_t address, uint8_t* valueOut) {
    if (!this) {
        return THIS_IS_NULL;
    }
    if (address > MEMORY_SIZE) {
        return ADDRESS_OUT_OF_BOUNDS;
    }
    *valueOut = this->_buffer[address];
    return NO_ERR;
}

ErrCode GetValue16(struct Memory* this, const uint16_t address, uint16_t* valueOut) {
    if (!this) {
        return THIS_IS_NULL;
    }
    if (address > MEMORY_SIZE || address + 1 > MEMORY_SIZE) {
        return ADDRESS_OUT_OF_BOUNDS;
    }

    uint8_t part1 = this->_buffer[address];
    uint8_t part2 = this->_buffer[address + 1];
    *valueOut = part1 << 8 | part2;
    return NO_ERR;
}

ErrCode SetValue(struct Memory* this, uint16_t address, uint8_t value) {
    if (!this) {
        return THIS_IS_NULL;
    }
    if (address > MEMORY_SIZE) {
        return ADDRESS_OUT_OF_BOUNDS;
    }
    this->_buffer[address] = value;
    return NO_ERR;
}

ErrCode SetValue16(struct Memory* this, uint16_t address, uint16_t value) {
    if (!this) {
        return THIS_IS_NULL;
    }
    if (address > MEMORY_SIZE || address + 1 > MEMORY_SIZE) {
        return ADDRESS_OUT_OF_BOUNDS;
    }

    uint8_t part1 = (uint8_t)(value >> 8);
    uint8_t part2 = (uint8_t)value;
    this->_buffer[address] = part1;
    this->_buffer[address + 1] = part2;
    return NO_ERR;
}