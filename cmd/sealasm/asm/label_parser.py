from typing import Any

import parser_combinator as parser
from asm.asm_parser_base import ASMParser


class LabelParser(ASMParser):
    """
    parses labels for the SealASM grammer
    labels must consist of an upper or lowercase letter or an underscore, then upper or lowercase letters, digits, or an underscore (i.e. _Var9:) (invalid: 9_Var:)
    """

    def __init__(self, runner: parser.Runner, map_method: Any = None):
        self._runner: parser.Runner = runner
        super().__init__(self._runner, "", "", map_method=map_method)

    def run(self, state: parser.State) -> parser.State:
        if state.is_error:
            return state

        # get first character of label identifier, should only be uppercase/lowercase/underscore
        state = self._runner.run(parser.RegexParser("^[a-zA-z_]"), state.source, state=state)
        if state.is_error:
            state.error = f"LabelParser: invalid label definition at index '{state.index}'"
            return state

        result = state.result

        # get optional remainder of label identifier, can be uppercase/lowercase/underscore/number
        state = self._runner.possibly(parser.RegexParser("^[a-zA-z0-9_]+"), state.source, state=state)
        if state.result is not None:
            result += str(state.result)

        next_state = self._runner.run(parser.CharParser(locate=":"), state.source, state=state)
        if next_state.is_error:
            next_state.error = f"LabelParser: no label terminator found"
            return next_state

        next_state = self._optional_whitespace(next_state)
        if next_state.is_error:
            return next_state

        return parser.State(source=state.source, index=state.index, result=result).map(self._map_method)
