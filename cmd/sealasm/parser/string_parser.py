from typing import Callable, Optional

from parser.base_parser import BaseParser
from parser.state import State


class StringParser(BaseParser):
    "parser for locating strings"

    def __init__(self, locate: str, map_method: Optional[Callable] = None):
        self.locate: str = locate
        super().__init__(map_method)

    def run(self, state: State) -> State:
        if state.is_error:
            return state

        start_index = state.source.find(self.locate, state.index)

        if start_index == -1:
            return self._set_error_state(state, f"StringParser: tried to match '{self.locate}', but got {state.source}")

        if len(self.locate) == 1:
            end_index = state.source.find(self.locate[-1], start_index)
        else:
            end_index = state.source.find(self.locate[-1], start_index + 1)

        if end_index == -1:
            return self._set_error_state(state, f"StringParser: tried to match '{self.locate}', but got {state.source}")

        end_index += 1
        state.result = state.source[start_index:end_index]
        state.index = end_index
        state.error = ""
        state.is_error = False
        return State(state=state).map(self._map_method)
