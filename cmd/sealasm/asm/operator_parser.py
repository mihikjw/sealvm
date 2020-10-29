from typing import Callable, Optional

import parser

from asm.types import Operators


class OperatorParser(parser.BaseParser):
    "parses operators for the SealASM grammer"

    def __init__(self, runner: parser.Runner, map_method: Optional[Callable] = None):
        self._runner: parser.Runner = runner
        self._supported_operators = {
            "+": Operators.OP_ADD,
            "-": Operators.OP_MINUS,
            "*": Operators.OP_MULTIPLY,
        }
        super().__init__(map_method)

    def run(self, state: parser.State) -> parser.State:
        if state.is_error:
            return state

        state = self._runner.run(parser.CharParser(), state.source, state=state)
        if state.is_error:
            return state

        if state.result not in self._supported_operators:
            state.is_error = True
            state.error = f"OperatorParser: no valid operator found at index '{state.index}'"
            return state

        state.result = self._supported_operators[state.result]
        return state
