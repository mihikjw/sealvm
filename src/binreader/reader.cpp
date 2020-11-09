#include "binreader/reader.hpp"

using namespace BinReader;

Reader::Reader(std::vector<uint8_t>* memory) { this->memory = memory; }

void Reader::FromFile(const std::string& filePath) {
    if (filePath.empty()) {
        throw std::invalid_argument("FilePath Invalid");
    }

    try {
        auto inFile = std::ifstream(filePath);
        std::string program;
        std::string line;

        while (std::getline(inFile, line)) {
            program += line;
        }

        if (program.empty()) {
            throw std::runtime_error("no binary read");
        }

        uint8_t tmp;
        uint8_t i = 0x00;
        size_t pos = 0;
        size_t nextPos = 0;

        while ((nextPos = program.find(delim, pos)) != std::string::npos) {
            std::string substr = program.substr(pos, nextPos - pos);
            tmp = std::stoi(substr, nullptr, 16);
            memory->at(i) = tmp;
            pos = pos + (nextPos - pos) + 1;
            i++;
        }

    } catch (const std::exception& ex) {
        throw std::runtime_error(ex.what());
    }
}