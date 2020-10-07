#include "sealvm/memory.hpp"

#include <stdexcept>

using namespace SealVM;

Memory::Memory(const unsigned int sizeBytes) : buffer(sizeBytes, SealVM::ZERO_MEMORY) {}