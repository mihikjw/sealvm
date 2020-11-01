from typing import Optional, Tuple, List

from parser_combinator.base_parser import BaseParser
from parser_combinator.state import State


class Runner():
    "runner executes parsers"

    def run(self, parser: BaseParser, src: str, state: Optional[State] = None) -> State:
        "executes given parser"
        if state is None:
            state = State(source=src)

        return parser.run(state)

    def sequence_of(self, parsers: Tuple[BaseParser], src: str, state: Optional[State] = None) -> State:
        "executes a sequence of parsers one after the other"
        if state is None:
            state = State(source=src)

        results: List[State] = []

        for parser in parsers:
            if state.is_error:
                return state
            state = parser.run(state)
            results.append(State(state=state))

        state.result = results
        return State(state=state)

    def choice(self, parsers: Tuple[BaseParser], src: str, state: Optional[State] = None) -> State:
        "executes the given parsers on the same source until a match is found"
        if state is None:
            state = State(source=src)

        start_index = state.index

        for parser in parsers:
            state = parser.run(state)

            if not state.is_error:
                return state

            state.index = start_index
            state.is_error = False
            state.error = ""

        state.error = f"Runner.choice: unable to match with any parser at index '{state.index}'"
        state.is_error = True
        return state

    def many(self, parser: BaseParser, src: str, state: Optional[State] = None, many1: bool = False) -> State:
        "executes the given parser as many times as it can, many1 tells to mark error if no matches, default is false"
        if state is None:
            state = State(source=src)

        results: List[State] = []
        done = False
        count = 0

        while not done:
            tmp_state = parser.run(state)

            if not tmp_state.is_error:
                results.append(State(state=tmp_state))
                state = tmp_state
                count += 1
            else:
                done = True

        if many1 and not count:
            state.error = f"Runner.many: unable to match any input using parser at index '{state.index}'"
            state.is_error = True
        else:
            state.result = results
            state.error = ""
            state.is_error = False

        return State(state=state)

    def peek(self, parser: BaseParser, src: str, state: Optional[State] = None, distance: int = 0) -> State:
        "looks ahead using the given parser, without incrementing the index"
        if state is None:
            state = State(source=src)

        start_input = state.source
        start_index = state.index

        if distance:
            state.source = state.source[state.index:(state.index + distance) + 1]

        state = parser.run(state)
        state.index = start_index
        state.source = start_input
        return state

    def possibly(self, parser: BaseParser, src: str, state: Optional[State] = None) -> State:
        "allows a failure to be returned as None instead of an error"
        if state is None:
            state = State(source=src)

        state = self.run(parser, state.source, state=state)
        if not state.is_error:
            return state

        state.is_error = False
        state.error = ""
        state.result = None
        return state
