import re
from typing import Any

from parser_combinator.base_parser import BaseParser
from parser_combinator.state import State


class LettersParser(BaseParser):
    "used to check a given string only contains letters"

    def __init__(self, map_method: Any = None):
        self._regex = re.compile("^[A-Za-z]+")
        super().__init__(map_method)

    def run(self, state: State) -> State:
        if state.is_error:
            return state

        if not len(state.source) or len(state.source) < state.index + 1:
            return self._set_error_state(state, "LettersParser: got unexpected end of input")

        source = state.source[state.index:]
        output = self._regex.match(source)

        if output:
            state.result = output.string[output.start():output.end()]
            state.index = state.index + output.end()
            state.is_error = False
            state.error = ""
        else:
            state.error = f"LettersParser: couldn't match digits at index '{state.index}'"
            state.is_error = True

        return State(state=state).map(self._map_method)
