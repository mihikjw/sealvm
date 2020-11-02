from typing import Tuple, Any, List, Dict

import parser_combinator as parser

from asm.asm_parser_base import ASMParser


class NoArgParser(ASMParser):
    "parses a no argument based instruction for the SealASM grammer"

    def __init__(self, runner: parser.Runner, instruction_mnemonic: str, instruction: str, map_method: Any = None):
        super().__init__(runner, instruction_mnemonic, instruction, map_method=map_method)

    def run(self, state: parser.State) -> parser.State:
        # get instruction
        state = self._upper_or_lower_string(self._instruction_mnemonic, state.source, state)
        if state.is_error:
            return state

        state = self._optional_whitespace(state)
        if state.is_error:
            return state

        # setup result tree
        result = {
            "type": self._instruction_mnemonic,
            "value": {
                "instruction": self._instruction,
                "args": []
            }
        }
        return parser.State(source=state.source, result=result, index=state.index)
