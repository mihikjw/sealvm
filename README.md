# SealVM
SealVM is a 16-bit virtual machine, written in C++. My primary goals at the moment are to develop a CPU, an assembly language, then a higher-level c-style language compiler. This project is a work in-progress.

## Applications `/cmd`
### SealVM
`sealvm` contains the code for the virtual machine, including the CPU and memory devices, implemented in C++.

### SealASM
`sealasm` contains a parser and compiler for the SealASM language, implemented in Python.

## SealVM Specifications
### Registers `sealvm/registers.hpp`
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
- 0x10: sp (Stack Pointer)
- 0x11: fp (Frame Pointer)

### Memory `sealvm/memory.hpp`
Memory size is currently arbitary and is defined on construction as an argument - any instance of base class `MemoryDevice` can be used as memory, which takes an `std::vector<uint8_t>` to be used as the internal memory buffer. The process of memory construction is a continuing development.

### Supported Instructions `sealvm/instructions.hpp`
16-bit instruction enums are defined under `sealvm/instructions.hpp`, with a comment for a corresponding assembly example. They're decoded in the CPU `sealvm/cpu.hpp` which also includes a comment for a corresponding assembly example. I'll improve this documentation once the SealASM library is complete, and the interface is stable.

## Developing
I use Visual Studio Code to develop this project, under `.vscode/` are the launch config/tasks/settings etc. You're welcome to use whatever environment you like. I'm using GCC-10 as a compiler.

### Requirements
- Visual Studio Code
    - C/C++ support
    - Python support
    - Native Debug
    - Trigger Task on Save
    - Clang-Tidy
    - CMake
- Python3
- CMake
- Make
- Git
- Clang-Format
- Clang-Tidy
- GCC-10

### Install
1. `git clone https://github.com/MichaelWittgreffe/sealvm`
2. `cd sealvm`
3. `git submodule init`
4. `git submodule update --init --recursive --remote`
5. build:
    - vscode: `ctrl + lshift + b` (default build task) 
    - cmake: `cmake -G Unix Makefiles -DCMAKE_BUILD_TYPE=Debug`

### Code Guidelines
- Lint with the provided clang-format configuration, clang-tidy is configured for VSCode
- public functions should start with uppercase, private and protected with lowercase. Should all be camelCase.
