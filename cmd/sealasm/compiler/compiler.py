from typing import Dict, Any, Tuple, List
from sealvm import InstructionMap, Registers, Type


class Compiler():
    "methods for compiling an AST entry to machine code"

    def __init__(self):
        self.current_address: int = 0
        self.labels: Dict[str, int] = {}

    def line(self, line: Dict[str, Any]) -> List[int]:
        "compiles a given line of AST to machine code as a list"
        if "value" not in line or "type" not in line:
            raise ValueError("Compiler: invalid line ast given")

        value = line["value"]
        if "instruction" not in value:
            raise ValueError("Compiler: invalid instruction ast given")

        instruction = value["instruction"]
        if instruction not in InstructionMap:
            raise ValueError(f"Compiler: instruction {instruction} not supported")

        metadata = InstructionMap[instruction]
        result: List[int] = [metadata.opcode]

        try:
            args = self._get_args(value)

            if metadata.type in (Type.LIT_REG, Type.MEM_REG):
                high, low = self._encode_lit_or_mem(args[0])
                result.append(high)
                result.append(low)
                result.append(self._encode_reg(args[1]))
            elif metadata.type in (Type.REG_LIT, Type.REG_MEM):
                result.append(self._encode_reg(args[0]))
                high, low = self._encode_lit_or_mem(args[1])
                result.append(high)
                result.append(low)
            elif metadata.type == Type.REG_LIT_8:
                byte = self._encode_lit_8(args[0])
                result.append(byte)
                result.append(self._encode_reg(args[1]))
            elif metadata.type in (Type.REG_REG, Type.REG_PTR_REG):
                result.append(self._encode_reg(args[0]))
                result.append(self._encode_reg(args[1]))
            elif metadata.type == Type.LIT_MEM:
                high, low = self._encode_lit_or_mem(args[0])
                result.append(high)
                result.append(low)
                high, low = self._encode_lit_or_mem(args[1])
                result.append(high)
                result.append(low)
            elif metadata.type == Type.LIT_OFF_REG:
                high, low = self._encode_lit_or_mem(args[0])
                result.append(high)
                result.append(low)
                result.append(self._encode_reg(args[1]))
                result.append(self._encode_reg(args[2]))
            elif metadata.type == Type.SINGLE_REG:
                result.append(self._encode_reg(args[0]))
            elif metadata.type == Type.SINGLE_LIT:
                high, low = self._encode_lit_or_mem(args[0])
                result.append(high)
                result.append(low)
            elif metadata.type == Type.NO_ARGS:
                pass
            else:
                raise ValueError(f"metadata.type {metadata.type} not supported")
        except ValueError as ex:
            raise RuntimeError(f"Compiler: error parsing instruction {instruction}: {str(ex)}")

        return result

    def _encode_lit_or_mem(self, lit_or_mem: Dict[str, str]) -> Tuple[int, int]:
        "encodes a 16-bit literal as machine code"
        if "value" not in lit_or_mem or "type" not in lit_or_mem:
            raise ValueError(f"invalid formatted _encode_lit_or_mem: {lit_or_mem}")

        hex_val = self._get_variable_value(lit_or_mem)
        src = int(hex_val, base=16)
        high = (src & 0xff00) >> 8
        low = src & 0x00ff
        return high, low

    def _encode_lit_8(self, lit: Dict[str, str]) -> int:
        "encodes an 8-bit literal as machine code"
        if "value" not in lit:
            raise ValueError(f"invalid formatted _encode_lit_8: {lit}")
        hex_val = self._get_variable_value(lit)
        src = int(hex_val, base=16)
        bit = src & 0x00ff
        return bit

    def _encode_reg(self, reg: Dict[str, str]) -> int:
        if "value" not in reg:
            raise ValueError(f"invalid formatted _encode_reg: {reg}")
        reg_value = reg["value"]
        if reg_value not in Registers:
            raise ValueError(f"Compiler: register {reg_value} not supported")
        return Registers[reg_value]

    def _get_args(self, instruction_entry: Dict[str, Any]) -> List[Dict[str, str]]:
        "gets the args from a given instruction entry"
        if "args" not in instruction_entry:
            raise ValueError(f"no args supplied")
        return instruction_entry["args"]

    def _get_variable_value(self, entry: Dict[str, Any]) -> str:
        "gets a possible variable or label value"
        if entry["type"] == "VARIABLE":
            if entry["value"] not in self.labels:
                raise ValueError(f"label {entry['value']} not resolved")
            return hex(self.labels[entry['value']])
        return entry['value']
