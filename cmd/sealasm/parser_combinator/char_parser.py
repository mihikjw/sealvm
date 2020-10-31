from typing import Any

from parser_combinator.base_parser import BaseParser
from parser_combinator.state import State


class CharParser(BaseParser):
    "used to return the next character in the input"

    def __init__(self, locate: str = "", map_method: Any = None):
        self._locate = locate
        super().__init__(map_method)

    def run(self, state: State) -> State:
        if state.is_error:
            return state

        if not len(state.source) or len(state.source) < state.index + 1:
            return self._set_error_state(state, "CharParser: got unexpected end of input")

        valid = False
        located = state.source[state.index:state.index + 1]

        if len(self._locate):
            if self._locate == located:
                valid = True
        else:
            valid = True

        if valid:
            state.result = located
            state.index += 1
            state.is_error = False
            state.error = ""
        else:
            state.is_error = True
            state.error = f"CharParser: tried to match '{self._locate}', but got {state.source}"

        return State(state=state).map(self._map_method)
