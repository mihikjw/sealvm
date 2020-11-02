from typing import Tuple, Any

import parser_combinator as parser

from asm.registers import Registers


class ASMParser(parser.BaseParser):
    "parses a SealASM instruction"

    def __init__(self, runner: parser.Runner, map_method: Any = None):
        self._runner: parser.Runner = runner
        self._whitespace_opt = parser.WhitespaceParser(optional=True)
        super().__init__(map_method)

    def run(self, state: parser.State) -> parser.State:
        raise NotImplementedError("Not Implemented")

    def _upper_or_lower_string(self, locate: str, src: str, state: parser.State, look_ahead: int = -1) -> parser.State:
        "locates the given upper or lowercase string in the given src string"
        upper = parser.StringParser(locate.upper(), look_ahead=look_ahead)
        lower = parser.StringParser(locate.lower(), look_ahead=look_ahead)
        return self._runner.choice((upper, lower), src, state=state)  # type: ignore

    def _register(self, src: str, state: parser.State) -> parser.State:
        "reads a register from the given src and state"
        for reg in Registers.keys():
            state = self._upper_or_lower_string(reg, src, state, 2)
            if not state.is_error:
                break
            state.is_error = False
            state.error = ""

        if not state.is_error:
            return state

        state.error = "ASMParser._register: unable to match register"
        return state

    def _state_to_ast(self, state: parser.State) -> dict:
        "transforms an tree comprised of State objects to an AST"
        if isinstance(state.result["value"], list):
            output = []
            for i, elem in enumerate(state.result["value"]):
                output.append(self._state_to_ast(elem))
            state.result["value"] = output
        elif isinstance(state.result["value"], dict) and state.result["type"] == "BINARY_OPERATION":
            tmp_val = state.result["value"]
            tmp_val["a"] = self._state_to_ast(tmp_val["a"])
            tmp_val["b"] = self._state_to_ast(tmp_val["b"])
            tmp_val["op"] = self._state_to_ast(tmp_val["op"])
            state.result["value"] = tmp_val

        return state.result
