# SealVM
SealVM is a 16-bit virtual machine designed to be either standalone or embedded into C applications, providing a JIT compiled runtime environment. The project currently consists of `sealvm` - the VM - and `sealasm`, an assembly compiler for the VM. The VM uses interrupts as a way of calling between C code and _seal_ code, the design is for programmers to write and load their own interrupts in C or SealASM, or to bring their own memory devices mapping to C code, with the VM providing a flexible way of adding functionality without recompiling your whole C application.

This project is actively being worked on soley by me at the moment and has much to go, but the initial 'core' components are in a state I'm happy to show publically. If you'd like to contribute or discuss the project, feel free to raise a PR :)

## Applications `/cmd`
### SealVM
`sealvm` contains the code for the virtual machine, including the CPU and memory devices, implemented in C. The VM is capable of executing instructions generated from the `sealasm` compiler, in a `*.seal` file format. Currently there's no debugger beyond stepping through the CPU C code, this is a goal to work on at some point soon.

The `sealvm` will execute programs starting at address `0x1000`, any addresses lower than this are reserved for internal VM code, such as the interrupt vector and standard memory devices.

#### Interrupts
The SealVM does support interrupts, however at the moment there are none enabled. The interrupt vector starts (by default) at address `0x0000`, and the `INT {index}` instruction should reference an index in this vector. For example, `INT $03` references index 3 in the vector, address `0x0006`. Documentation for supported interrupts will be added as handlers are added. There is currently no other way to load interrupts than to either compile a SealASM program ending with a `RET_INT` instruction and (in the C) add it to memory instruction by instruction, or to implement the interrupt in C directly and create a `MemoryDevice` inherited class for it, mapped to an address space. I'm actively working on improving the way interrupt 'modules' can be loaded into the VM on startup.

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
- `test3.asm`: test program for handling interrupts, this requires a bit of manually mucking about so don't run this yet, I'm going to work on a dynamic way of easily loading in SealASM & C interrupts which will make this much easier. Currently you need to (in C) load the opcodes into the memory array.

## SealVM Specifications
### Registers `sealvm/registers.h`
Each register is 16-bits in size, currently the only way of interacting with them is in 16-bit chunks. Registers defined under `sealvm/registers.h`, and instantiated on the `CPU` struct itself (`sealvm/CPU.h`). Implemented are a Program Counter, Accumulator, Stack Pointer, Frame Pointer, Interrupt Mask and x8 general purpose registers.

### Supported Instructions `sealvm/instructions.h`
Instruction enums are defined under `sealvm/instructions.h`, with a comment for a corresponding assembly example. They're decoded in the CPU `sealvm/cpu.h` which also includes a comment for a corresponding assembly example. A couple of example programs used for testing are located under `/example_programs`.

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
3. build:
    - vscode: `ctrl + lshift + b` (default build task) 
    - cmake: `cmake -G Unix Makefiles -DCMAKE_BUILD_TYPE=Debug` && `make`

### Code Guidelines
- Lint with the provided clang-format configuration, clang-tidy is configured for VSCode
- C: public functions should start with uppercase, private and protected with lowercase and pre-pended with an underscore. Should all be camelCase.
