# SealVM

## Introduction
SealVM is a 16-bit virtual machine, primary as a hobby project and a learning experience.

## Registers
- Program Counter
- Accumulator (math ops results)
- x8 General Purpose registers
- each is 16 bytes, 2 bytes for each register

## Memory
- made up of an std::array containing uint8_t of the requested input size