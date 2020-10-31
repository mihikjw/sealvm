from typing import Dict


class Operators():
    "enum for all supported operators"
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
