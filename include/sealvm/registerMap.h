#ifndef SEALVM_SEALVM_REGISTERMAP_H
#define SEALVM_SEALVM_REGISTERMAP_H

#include <stdint.h>

#include "sealvm/errors.h"

// RegNode represents a single node in a HashMap
typedef struct RegNode {
    uint8_t Key;
    uint16_t Value;
    struct RegNode* Next;
} RegNode;

// HashMap represents a key-value data structure
typedef struct RegisterMap {
    int Size;
    RegNode** List;

    // Set sets a given value for the given key
    void (*Set)(struct RegisterMap*, const uint8_t key, const uint16_t value);

    // Get returns the stored value for the given key
    ErrCode (*Get)(struct RegisterMap*, const uint8_t key, uint16_t* output);

    // Clear free's all allocated memory internally
    void (*Clear)(struct RegisterMap*);
} RegisterMap;

// NewRegisterMap is a constructor for the RegisterMap object
RegisterMap* NewRegisterMap(const int size);

#endif // SEALVM_SEALVM_REGISTERMAP_H