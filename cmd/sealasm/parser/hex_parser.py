import re
from typing import Callable, Optional

from parser.base_parser import BaseParser
from parser.state import State


class HexParser(BaseParser):
    "used to check a given string only contains hex-allowed values"

    def __init__(self, map_method: Optional[Callable] = None):
        self._regex: Pattern[AnyStr] = re.compile("^[0-9A-Fa-f]+")
        super().__init__(map_method)

    def run(self, state: State) -> State:
        if state.is_error:
            return state

        if not len(state.source) or len(state.source) < state.index + 1:
            return self._set_error_state(state, "HexParser: got unexpected end of input")

        if state.source[state.index] == "$":
            state.index += 1

        source = state.source[state.index:]
        output = self._regex.match(source)

        if output:
            state.result = output.string[output.start():output.end()]
            state.index = state.index + output.end()
            state.is_error = False
            state.error = ""
        else:
            state.error = f"HexParser: couldn't match digits at index '{state.index}'"
            state.is_error = True

        return State(state=state).map(self._map_method)
