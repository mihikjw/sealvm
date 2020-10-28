from parser.state import State


class BaseParser():
    "base class for parsers"

    def run(self, state: State) -> State:
        "base method, override with derived classes. Should return a COPY of the source state"
        raise NotImplementedError("Not Implemented")

    def _set_error_state(self, state: State, error: str) -> State:
        "sets the error state on the given state and returns"
        state.error = error
        state.is_error = True
        return state
