#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "binreader/reader.h"
#include "sealvm/sealvm.h"

int main(int argc, const char* argv[]) {
    // TODO: refactor cmd-line args, this works for now but when others are added this needs putting into it's
    //       own function
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

    BinReader* binReader = NewBinReader(mainMemory, stderr);
    if (!binReader) {
        fprintf(stderr, "Failed To Construct BinReader\n");
        return EXIT_FAILURE;
    }

    // returns 0 on success, will print own failure to `stderr`
    if (binReader->FromFile(binReader, binaryPath)) {
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

    // TODO: finalise interrupt vector address, currently arbitary and too low
    CPU* cpu = NewCPU(mMap, 0x1000);
    if (!cpu) {
        printf("Failed To Construct CPU\n");
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

    // execute program
    cpu->Run(cpu);

    // cleanup
    mMap->ClearRegions(mMap);
    free(mMap);
    free(memory);

    return EXIT_SUCCESS;
}