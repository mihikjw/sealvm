#include "sealvm/registerMap.h"

#include <stdlib.h>

void RM_Set(RegisterMap* this, uint8_t key, uint16_t value);
ErrCode RM_Get(RegisterMap* this, uint8_t key, uint16_t* output);
void RM_Clear(RegisterMap* this);

// hashCode returns the hashCode for a member
uint8_t RM_hashCode(RegisterMap* this, uint8_t key);

RegisterMap* NewRegisterMap(const int size) {
    RegisterMap* result = malloc(sizeof(RegisterMap));
    if (!result) {
        return NULL;
    }

    result->Size = size;
    result->List = malloc(sizeof(RegNode*) * size);
    for (register int i = 0; i < size; i++) {
        result->List[i] = NULL;
    }

    result->Set = &RM_Set;
    result->Get = &RM_Get;
    result->Clear = &RM_Clear;
    return result;
}

uint8_t RM_hashCode(RegisterMap* this, const uint8_t key) {
    if (!this) {
        return -1;
    }

    return key % this->Size;
}

void RM_Set(RegisterMap* this, const uint8_t key, const uint16_t value) {
    if (!this) {
        return;
    }

    uint8_t position = RM_hashCode(this, key);
    if (position == -1) {
        return;
    }

    RegNode* list = this->List[position];
    RegNode* tmp = list;

    // change value if key already exists
    while (tmp) {
        if (tmp->Key == key) {
            tmp->Value = value;
            return;
        }
        tmp = tmp->Next;
    }

    // allocate a new node if key does not exist
    RegNode* newNode = malloc(sizeof(RegNode));
    newNode->Key = key;
    newNode->Value = value;
    newNode->Next = list;
    this->List[position] = newNode;
}

ErrCode RM_Get(RegisterMap* this, const uint8_t key, uint16_t* output) {
    if (!this) {
        return THIS_IS_NULL;
    }

    uint8_t position = RM_hashCode(this, key);
    if (position == -1) {
        return CANNOT_COMPUTE_HASH;
    }

    RegNode* list = this->List[position];
    RegNode* tmp = list;

    while (tmp) {
        if (tmp->Key == key) {
            *output = tmp->Value;
            return NO_ERR;
        }
        tmp = tmp->Next;
    }

    return INVALID_REGISTER;
}

void RM_Clear(RegisterMap* this) {
    if (!this) {
        return;
    }

    for (register int i = 0; i < this->Size; i++) {
        if (this->List[i]) {
            free(this->List[i]);
        }
    }
}