#include <cstdint>
#include <iostream>
#include <memory>
#include <vector>

#include "binreader/reader.hpp"
#include "sealvm/sealvm.hpp"

constexpr int MEMORY_SIZE = 256 * 256;

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        std::cout << "no binary provided" << std::endl;
        return 1;
    }

    std::vector<uint8_t> mainMemory(MEMORY_SIZE, SealVM::ZERO_MEMORY);

    try {
        auto memory = SealVM::Memory(&mainMemory);
        auto mapper = SealVM::MemoryMapper(&mainMemory);
        mapper.Map(&memory, SealVM::ZERO_MEMORY, SealVM::FULL_MEMORY);

        // map addresses 0x3000 to 0x30ff as screen output
        SealVM::ScreenDevice screenDevice(nullptr);
        mapper.Map(&screenDevice, 0x3000, 0x30ff, true);

        auto binReader = BinReader::Reader(&mainMemory);
        binReader.FromFile(argv[1]);

        auto cpu = SealVM::CPU(&mapper);
        cpu.Run();

        return 0;
    } catch (const std::exception& ex) {
        std::cout << "Exception: " << ex.what() << std::endl;
    }
}
