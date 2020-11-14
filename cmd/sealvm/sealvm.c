#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "sealvm/sealvm.h"

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "No Binary Provided\n");
        return EXIT_FAILURE;
    }

    const char* binaryPath = argv[1];
    uint8_t mainMemory[MEMORY_SIZE];

    Memory* memory = NewMemory(mainMemory, MEMORY_SIZE);
    if (!memory) {
        fprintf(stderr, "Failed To Construct Memory\n");
        return EXIT_FAILURE;
    }

    MemoryMapper* mMap = NewMemoryMapper(memory);
    if (!mMap) {
        fprintf(stderr, "Failed To Construct MemoryMapper\n");
        return EXIT_FAILURE;
    }

    ScreenDevice* output = NewScreenDevice();
    if (!output) {
        printf("Failed To Construct ScreenDevice\n");
        return EXIT_FAILURE;
    }

    if (mMap->Map(mMap, memory, MainMemory, ZERO_MEMORY, FULL_MEMORY, false) != NO_ERR) {
        printf("Failed To Map MainMemory\n");
        return EXIT_FAILURE;
    }

    if (mMap->Map(mMap, output, Screen, 0x4000, 0x40ff, true) != NO_ERR) {
        printf("Failed To Map ScreenDevice\n");
        return EXIT_FAILURE;
    }

    // read binary from file

    // execute program
    CPU* cpu = NewCPU(mMap, 0x1000);
    cpu->Run(cpu);

    mMap->ClearRegions(mMap);
    cpu->_registers->Clear(cpu->_registers); // this should be hidden away
    free(mMap);
    free(memory);

    return EXIT_SUCCESS;
}