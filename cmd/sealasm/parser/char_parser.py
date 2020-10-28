from parser.base_parser import BaseParser
from parser.state import State


class CharParser(BaseParser):
    "used to return the next character in the input"

    def run(self, state: State) -> State:
        if state.is_error:
            return state

        if not len(state.source) or len(state.source) < state.index + 1:
            return self._set_error_state(state, "CharParser: got unexpected end of input")

        state.result = state.source[state.index:state.index + 1]
        state.index += 1
        state.is_error = False
        state.error = ""
        return State(state=state)
