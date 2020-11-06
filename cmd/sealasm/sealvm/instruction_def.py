
class InstructionDef():
    "class defining an instruction's details"

    def __init__(self, opcode: int, size: int, type: int, mnemonic: int):
        self.opcode: int = opcode
        self.size: int = size
        self.type: int = type
        self.mnemonic: int = mnemonic
