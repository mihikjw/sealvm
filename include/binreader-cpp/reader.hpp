#ifndef SEALVM_BINREADER_READER_HPP
#define SEALVM_BINREADER_READER_HPP

#include <cstdint>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace BinReader {

class Reader {
    public:
    Reader(std::vector<uint8_t>* memory);
    ~Reader() = default;

    // FromFile loads the given *.seal binary into the injected memory vector starting at position 0x0000
    void FromFile(const std::string& filePath);

    private:
    std::vector<uint8_t>* memory;
    const char* delim = " ";
};

} // namespace BinReader

#endif // SEALVM_BINREADER_READER_HPP