# SealVM
SealVM is a 16-bit virtual machine, primary as a hobby project and a learning experience. My primary goals at the moment are to develop a CPU, an assembly language, then a higher-level c-style language compiler. This project is a work in-progress.

## Registers `sealvm/registers.hpp`
Each register is 16-bits in size, currently the only way of interacting with them is in 16-bit chunks.
- 0x00: pc (Program Counter)
- 0x01: r1 (General Purpose)
- 0x02: r2 (General Purpose)
- 0x03: r3 (General Purpose)
- 0x04: r4 (General Purpose)
- 0x05: r5 (General Purpose)
- 0x06: r6 (General Purpose)
- 0x07: r7 (General Purpose)
- 0x08: r8 (General Purpose)
- 0x09: acc (Accumulator)

## Memory `sealvm/memory.hpp`
Memory size is currently arbitary and is defined on construction as an argument. Memory is then injected to the CPU.
- `std::array` buffer containing `uint8_t` of the size passed to the constructor
- can be interacted with in `uint8_t` chunks or `uint16_t` chunks as this is the current supported minimum register size

## Supported Instructions 
16-bit instruction enums are defined under `sealvm/instructions.hpp`, with a comment for a corresponding assembly example. I'll likley improve this once I put together an actual assembler.