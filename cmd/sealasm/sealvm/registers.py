from typing import Dict

# Registers is a mapping between register names and their machine-code values
Registers: Dict[str, int] = {
    "pc": 0x00,
    "r1": 0x01,
    "r2": 0x02,
    "r3": 0x03,
    "r4": 0x04,
    "r5": 0x05,
    "r6": 0x06,
    "r7": 0x07,
    "r8": 0x08,
    "acc": 0x09,
    "sp": 0x10,
    "fp": 0x11,
    "im": 0x12,
}
