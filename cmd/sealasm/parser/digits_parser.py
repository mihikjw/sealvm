import re

from parser.base_parser import BaseParser
from parser.state import State


class DigitsParser(BaseParser):
    "digits parser is used to check a given string only contains numerical digits"

    def __init__(self):
        self._regex: Pattern[AnyStr] = re.compile("^[0-9]+")

    def run(self, state: State) -> State:
        if state.is_error:
            return state

        if not len(state.source) or len(state.source) < state.index + 1:
            return self._set_error_state(state, "DigitsParser: got unexpected end of input")

        source = state.source[state.index:]
        output = self._regex.match(source)

        if output:
            state.result = output.string[output.start():output.end()]
            state.index = output.end()
            state.is_error = False
            state.error = ""
        else:
            state.error = f"DigitsParser: couldn't match digits at index '{state.index}'"
            state.is_error = True

        return State(state=state)