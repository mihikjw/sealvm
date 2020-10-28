from typing import Any, Optional, Callable
import json


class State():
    "parser state"

    def __init__(self, state: Optional["State"] = None, source: str = "", result=None, index: int = 0, error: str = "", is_error: bool = False):
        if state is not None:
            self.source = state.source
            self.result = state.result
            self.index = state.index
            self.error = state.error
            self.is_error = state.is_error
        else:
            self.source: str = source
            self.result: Any = result
            self.index: int = index
            self.error: str = error
            self.is_error: bool = is_error

    def map(self, func: Callable):
        """
        run the given method with access to the state fields, allows manipulation of the result before returning
        ARGS: given method must take a State object as the first argument
        """
        if func is not None:
            func(self)
        return self

    def __str__(self):
        return json.dumps(vars(self))
