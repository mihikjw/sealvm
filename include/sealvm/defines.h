#ifndef SEALVM_SEALVM_DEFINES_H
#define SEALVM_SEALVM_DEFINES_H

// MEMORY_SIZE defines the size of memory for the VM
#define MEMORY_SIZE 65535

// REGISTER_COUNT defines the number of registers
#define REGISTER_COUNT 13

// ZERO_MEMORY defines a totally-zero memory address
#define ZERO_MEMORY 0x0000

// FULL_MEMORY defines a totally-full memory address
#define FULL_MEMORY 0xFFFF

// PROGRAM_START_ADDRESS defines the start address for any programs
#define PROGRAM_START_ADDRESS 0x1000

#endif // SEALVM_SEALVM_DEFINES_H
