from typing import Any

from parser_combinator.base_parser import BaseParser
from parser_combinator.state import State


class BetweenParser(BaseParser):
    "used to extract text from between two chars"

    def __init__(self, left_find: str, right_find: str, map_method: Any = None):
        self.left = left_find
        self.right = right_find
        super().__init__(map_method)

    def run(self, state: State) -> State:
        if state.is_error:
            return state

        left_pos = state.source.find(self.left, state.index)
        if left_pos == -1:
            return self._set_error_state(state, f"BetweenParser: tried to match {self.left} but got {state.source}")

        right_pos = state.source.find(self.right, left_pos)
        if right_pos == -1:
            return self._set_error_state(state, f"BetweenParser: tried to match {self.right} but got {state.source}")

        state.index = right_pos + 1
        state.result = state.source[left_pos:state.index]
        state.error = ""
        state.is_error = False
        return State(state=state).map(self._map_method)
