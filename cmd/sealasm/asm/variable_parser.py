from typing import Any

import parser_combinator as parser


class VariableParser(parser.BaseParser):
    """
    parses variables for the SealASM grammer
    variables must consist of an exclamation mark, an upper or lowercase letter or an underscore,
        then upper or lowercase letters, digits, or an underscore (i.e. !_Var9) (invalid: !9_Var)
    """

    def __init__(self, runner: parser.Runner, map_method: Any = None):
        self._runner: parser.Runner = runner
        super().__init__(map_method)

    def run(self, state: parser.State) -> parser.State:
        if state.is_error:
            return state

        # get denotion of variable '!'
        state = self._runner.run(parser.CharParser(), state.source, state=state)
        if state.is_error:
            return state
        elif state.result != "!":
            state.is_error = True
            state.error = f"VariableParser: no variable found at index '{state.index}'"
            return state

        # TODO: '[' and ']' are being considered as acceptable, this behaviour needs to be changed, for now just add whitespace to src code

        # get first character of variable identifier, should only be uppercase/lowercase/underscore
        state = self._runner.run(parser.RegexParser("^[a-zA-z_]"), state.source, state=state)
        if state.is_error:
            state.error = f"VariableParser: invalid variable definition at index '{state.index}'"
            return state

        result = state.result

        # get optional remainder of variable identifier, can be uppercase/lowercase/underscore/number
        state = self._runner.possibly(parser.RegexParser("^[a-zA-z0-9_]+"), state.source, state=state)
        if state.result is not None:
            result += str(state.result)

        return parser.State(source=state.source, index=state.index, result=result).map(self._map_method)

    @staticmethod
    def _map_variable_as_type(state: parser.State) -> parser.State:
        "maps the loaded result as a variable type"
        if not state.is_error:
            state.result = {"type": "VARIABLE", "value": state.result}
        return state
