# SealVM
SealVM is a 16-bit virtual machine, primary as a hobby project, written in C++. My primary goals at the moment are to develop a CPU, an assembly language, then a higher-level c-style language compiler. This project is a work in-progress.

## Developing
I use Visual Studio Code to develop this project, under `.vscode/` are the launch config/tasks/settings etc. You're welcome to use whatever environment you like.
### Requirements
- Visual Studio Code
    - C/C++ extension
    - Native Debug
    - Clang-Format
    - Clang-Tidy
    - CMake
- CMake
- Make
- Git
- Clang-Format
- Clang-Tidy

### Install
1. `git clone https://github.com/MichaelWittgreffe/sealvm`
2. `cd sealvm`
3. build:
    - vscode: `ctrl + lshift + b` (default build task) 
    - cmake: `cmake -G Unix Makefiles -DCMAKE_BUILD_TYPE=Debug`

### Code Guidelines
- Lint with the provided clang-format configuration, clang-tidy is configured for VSCode
- public functions should start with uppercase, private and protected with lowercase. Should all be camelCase.

## Specifications
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
Memory size is currently arbitary and is defined on construction as an argument. A pointer is then injected to any required classes.

### Supported Instructions 
16-bit instruction enums are defined under `sealvm/instructions.hpp`, with a comment for a corresponding assembly example. They're decoded in the CPU `sealvm/cpu.hpp` which also includes a comment for a corresponding assembly example. I'll improve this documentation once I put together a real assembler.