#include "sealvm/registerStore.h"

#include <stdlib.h>

void RS_Set(RegisterStore* this, Registers reg, uint16_t value);
ErrCode RS_Get(RegisterStore* this, Registers reg, uint16_t* output);

RegisterStore* NewRegisterStore() {
    RegisterStore* result = malloc(sizeof(RegisterStore));
    if (!result) {
        return NULL;
    }

    result->Set = &RS_Set;
    result->Get = &RS_Get;
    result->_store[pc] = ZERO_MEMORY;
    result->_store[r1] = ZERO_MEMORY;
    result->_store[r2] = ZERO_MEMORY;
    result->_store[r3] = ZERO_MEMORY;
    result->_store[r4] = ZERO_MEMORY;
    result->_store[r5] = ZERO_MEMORY;
    result->_store[r6] = ZERO_MEMORY;
    result->_store[r7] = ZERO_MEMORY;
    result->_store[r8] = ZERO_MEMORY;
    result->_store[acc] = ZERO_MEMORY;
    result->_store[sp] = FULL_MEMORY - 1;
    result->_store[fp] = FULL_MEMORY - 1;
    result->_store[im] = FULL_MEMORY;
    return result;
}

void RS_Set(RegisterStore* this, const Registers reg, const uint16_t value) {
    if (!this) {
        return;
    }
    this->_store[reg] = value;
}

ErrCode RS_Get(RegisterStore* this, const Registers reg, uint16_t* output) {
    if (!this) {
        return THIS_IS_NULL;
    }
    *output = this->_store[reg];
    return NO_ERR;
}