from typing import Any

from parser_combinator.base_parser import BaseParser
from parser_combinator.state import State


class WhitespaceParser(BaseParser):
    "used to ensure next character is whitespace, with an optional flag"

    def __init__(self, optional: bool = False, map_method: Any = None):
        self._optional = optional
        super().__init__(map_method)

    def run(self, state: State) -> State:
        if state.is_error:
            return state

        if not len(state.source) or len(state.source) < state.index + 1 and not self._optional:
            return self._set_error_state(state, "WhitespaceParser: got unexpected end of input")

        output = state.source[state.index:state.index + 1]

        if output == " ":
            state.result = output
            state.index += 1
            state.is_error = False
            state.error = ""
        elif self._optional:
            state.result = ""
            state.is_error = False
            state.error = ""
        else:
            state.is_error = True
            state.error = f"WhitespaceParser: No whitespace found at index '{state.index}'"

        return State(state=state).map(self._map_method)
