from typing import Any, Optional, Callable
import json


class State():
    "parser state"

    def __init__(self, state: Optional["State"] = None, source: str = "", result=None, index: int = 0, error: str = "", is_error: bool = False):
        if state is not None:
            self.source: str = state.source
            self.result: Any = state.result
            self.index: int = state.index
            self.error: str = state.error
            self.is_error: bool = state.is_error
        else:
            self.source = source
            self.result = result
            self.index = index
            self.error = error
            self.is_error = is_error

    def map(self, func: Any):
        """
        run the given method or iterable of methods with access to the state fields, allows manipulation of the result before returning
        ARGS: given method must take a State object as the first and only argument
        """
        if func is not None:
            if isinstance(func, list) or isinstance(func, tuple):
                for method in func:
                    method(self)
            else:
                func(self)
        return self

    def __str__(self):
        return json.dumps(vars(self))
