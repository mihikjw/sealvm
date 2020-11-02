from typing import Any

from parser_combinator.base_parser import BaseParser
from parser_combinator.state import State


class StringParser(BaseParser):
    "parser for locating strings"

    def __init__(self, locate: str, look_ahead: int = -1, map_method: Any = None):
        self._locate: str = locate
        self._look_ahead: int = look_ahead
        super().__init__(map_method)

    def run(self, state: State) -> State:
        if state.is_error:
            return state

        if self._look_ahead > -1:
            start_index = state.source.find(self._locate, state.index, state.index + self._look_ahead)
        else:
            start_index = state.source.find(self._locate, state.index)

        if start_index == -1:
            return self._set_error_state(state, f"StringParser: tried to match '{self._locate}', but got {state.source}")

        if len(self._locate) == 1:
            end_index = state.source.find(self._locate[-1], start_index)
        else:
            end_index = state.source.find(self._locate[-1], start_index + 1)

            # this method will not support double+ letters (i.e. ADD becomes AD), so we need to check this edge case
            # ensures the next final char is not equal to the final char
            while end_index + 1 < len(state.source) and state.source[end_index] == state.source[end_index + 1] \
                    and end_index < start_index + (len(self._locate) - 1):
                end_index += 1

        if end_index == -1:
            return self._set_error_state(state, f"StringParser: tried to match '{self._locate}', but got {state.source}")

        end_index += 1
        state.result = state.source[start_index:end_index]
        state.index = end_index
        state.error = ""
        state.is_error = False
        return State(state=state).map(self._map_method)
