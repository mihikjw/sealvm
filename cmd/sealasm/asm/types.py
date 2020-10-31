from typing import Dict


class Operators():
    "enum for all supported operators and mappings between, as well as priority"
    OP_ADD = "+"
    OP_MINUS = "-"
    OP_MULTIPLY = "*"

    code_operator_map: Dict[str, str] = {
        "OP_ADD": OP_ADD,
        "OP_MINUS": OP_MINUS,
        "OP_MULTIPLY": OP_MULTIPLY
    }

    operator_code_map: Dict[str, str] = {
        OP_ADD: "OP_ADD",
        OP_MINUS: "OP_MINUS",
        OP_MULTIPLY: "OP_MULTIPLY",
    }

    priorities: Dict[str, int] = {
        operator_code_map[OP_MULTIPLY]: 2,
        operator_code_map[OP_ADD]: 1,
        operator_code_map[OP_MINUS]: 0,
    }
