#ifndef SEALVM_SEALVM_ERRORS_H
#define SEALVM_SEALVM_ERRORS_H

// ERR_CODE defines a type to use for error codes
#define ERR_CODE uint8_t

// NO_ERR indicates no error has occured in the called function
#define NO_ERR 0

// THIS_IS_NULL indicates the 'this' pointer is NULL
#define THIS_IS_NULL 1

// INVALID_ADDRESS indicates the given memory addresses are out of bounds
#define ADDRESS_OUT_OF_BOUNDS 2

#endif // SEALVM_SEALVM_ERRORS_H