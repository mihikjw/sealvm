#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "sealvm/sealvm.h"

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        printf("No Binary Provided\n");
        return EXIT_FAILURE;
    }

    const char* binaryPath = argv[1];
    uint8_t mainMemory[MEMORY_SIZE];

    Memory* memory = NewMemory(mainMemory, MEMORY_SIZE);
    if (!memory) {
        printf("Failed To Construct Memory\n");
        return EXIT_FAILURE;
    }

    free(memory);
    return EXIT_SUCCESS;
}