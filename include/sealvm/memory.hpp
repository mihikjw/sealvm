#ifndef SEALVM_SEALVM_MEMORY_HPP
#define SEALVM_SEALVM_MEMORY_HPP

#include <memory>
#include <vector>

#include "defines.hpp"

namespace SealVM {

class Memory {
    public:
    Memory(const unsigned int sizeBytes);
    ~Memory() = default;
    std::vector<uint8_t> buffer;
};

} // namespace SealVM

#endif // SEALVM_SEALVM_MEMORY_HPP