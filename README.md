# SealVM
SealVM is a 16-bit, big-endian virtual machine, written in C++ with an ASM compiler in Python. You can find 'main' source code under `/cmd`. 

## Applications `/cmd`
### SealVM
`sealvm` contains the code for the virtual machine, including the CPU and memory devices, implemented in C++. The VM is capable of executing instructions generated from the `sealasm` compiler, in a `*.seal` hex file format. Currently there's no debugger beyond stepping through the CPU C++ code, this is a goal to work on at some point soon.

#### Interrupts
The SealVM does support interrupts, however at the moment there are none enabled. The interrupt vector starts (by default) at address `0x1000`, and the `INT {index}` instruction should reference an index in this vector. For example, `INT $03` references index 3 in the vector, address `0x1006`. Documentation for supported interrupts will be added as handlers are added. There is currently no other way to load interrupts than to either compile a SealASM program ending with a `RET_INT` instruction and (in the C++) add it to memory instruction by instruction, or to implement the interrupt in C++ directly and create a `MemoryDevice` inherited class for it, mapped to an address space. I'm actively working on improving the way interrupt 'modules' can be loaded into the VM on startup.

#### Usage
`sealvm [binary_path.seal]`

### SealASM
`sealasm` contains a parser and compiler for the SealASM language, implemented in Python. The parser uses a 'parser combinator' paradigm, with a number of 'parser' classes, which can be individually run or combined using a `Runner` class. These are combined and their results manipulated to create an Abstract Syntax Tree (AST), which can then be compiled. Each SealASM line has an AST generated for it, which is then immediatly passed to a `Compiler` class, which is responsible for translating this into machine code. The compiler then saves this in hex form as a 'binary' file (`*.seal`), which can be executed by the `sealvm`.

#### Usage
`sealasm [source_path.asm]`
- `-h` or `--help`: output help
- `-v` or `--version`: output version
- `-o [path]`: output binary path
- `-ast [path]` or `--ast`: output AST as JSON at path or alongside the binary output

#### Test Programs `/example_programs`
- `test1.asm`: moves values between registers and memory, then adds them; very simple test program
- `test2.asm`: stores number 10 in memory, then begins a loop - load number from memory, increment `r2` three times, if loaded number is not 10, jump to the start of the loop. This program is essentially a for loop.

### SealDbg
`sealdbg` is a debugger for SealVM-based applications, implemented in C++. This is currently being worked on, however the focus is to have a CLI-based debugger capable of viewing and representing the current register state, state of memory at given addresses, and a disassembly of the loaded program with a visual representation of the current line. The user can then step through the code line by line to view the various states. Perhaps be able to visualize memory usage as a graph.

I'm planning to make use of the [`tabulate`](https://github.com/p-ranav/tabulate) library to help output this data to the CLI: 

## SealVM Specifications
### Registers `sealvm/registers.hpp`
Each register is 16-bits in size, currently the only way of interacting with them is in 16-bit chunks. Registers defined under `sealvm/registers.hpp`, and instantiated on the `CPU` class itself (`sealvm/CPU.hpp`). Implemented are a Program Counter, Accumulator, Stack Pointer, Frame Pointer, Interrupt Mask and x8 general purpose registers.

### Memory `sealvm/memory.hpp`
Memory size is `256 * 256` and is defined on construction as an argument - any instance of base class `MemoryDevice` can be used as memory, which takes an `std::vector<uint8_t>` to be used as the internal memory buffer.

### Supported Instructions `sealvm/instructions.hpp`
Instruction enums are defined under `sealvm/instructions.hpp`, with a comment for a corresponding assembly example. They're decoded in the CPU `sealvm/cpu.hpp` which also includes a comment for a corresponding assembly example. A couple of example programs used for testing are located under `/example_programs`.

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
    - cmake: `cmake -G Unix Makefiles -DCMAKE_BUILD_TYPE=Debug` && `make`

### Code Guidelines
- Lint with the provided clang-format configuration, clang-tidy is configured for VSCode
- C++: public functions should start with uppercase, private and protected with lowercase. Should all be camelCase.
