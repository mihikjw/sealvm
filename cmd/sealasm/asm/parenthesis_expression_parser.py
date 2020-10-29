from typing import Tuple, Optional, Callable

import parser

from asm.variable_parser import VariableParser
from asm.operator_parser import OperatorParser
from asm.map_methods import _sqr_expr_as_type, _hex_value_as_type, _operator_value_as_type, _var_value_as_type


class ParenthesisExpParserState():
    "enum representing the states used in the ParenthesisExpressionParser state machine"
    OPEN_PARENTHESIS = 0
    OPERATOR_OR_CLOSING = 1
    ELEMENT_OR_OPENING = 2
    CLOSE_PARENTHESIS = 3
    END = 4


class ParenthesisExpressionParser(parser.BaseParser):
    "parses parenthesis expressions for the SealASM grammer"

    def __init__(self, runner: parser.Runner, map_method: Optional[Callable] = None):
        self._runner: parser.Runner = runner
        self._whitespace_opt = parser.WhitespaceParser(optional=True)
        super().__init__(map_method)

    def run(self, state: parser.State) -> parser.State:
        "state machine for processing expressions in parenthesis"
        if state.is_error:
            return state

        # get opening and optional whitespace
        state = self._runner.run(parser.CharParser(locate="("), state.source, state=state)
        if state.is_error:
            return state

        state = self._runner.run(self._whitespace_opt, state.source, state=state)
        if state.is_error:
            return state

        # process expression
        expr: list = []
        stack: list = [expr]
        sm_state = ParenthesisExpParserState.ELEMENT_OR_OPENING

        while sm_state != ParenthesisExpParserState.END:
            state = self._runner.peek(parser.CharParser(), state.source, state=state)
            if state.is_error:
                return state
            next_char = state.result

            if sm_state == ParenthesisExpParserState.OPEN_PARENTHESIS:
                state, sm_state = self._open_parenthesis(state, expr, stack)
            elif sm_state == ParenthesisExpParserState.OPERATOR_OR_CLOSING:
                state, sm_state = self._operator_or_closing(next_char, state, expr, stack)
            elif sm_state == ParenthesisExpParserState.ELEMENT_OR_OPENING:
                state, sm_state = self._element_or_opening(next_char, state, expr, stack)
            elif sm_state == ParenthesisExpParserState.CLOSE_PARENTHESIS:
                state, sm_state = self._close_parenthesis(state, expr, stack)
            else:
                raise RuntimeError(f"Unknown State: {sm_state}")

        if state.is_error:
            return state

        return parser.State(source=state.source, index=state.index, result=expr).map(self._map_method)

    def _open_parenthesis(self, state: parser.State, expr: list, stack: list) -> Tuple[parser.State, ParenthesisExpParserState]:
        "sets up a new open parenthesis in the expression and stack, sets to ELEMENT_OR_OPENING state"
        state = self._runner.run(parser.CharParser(locate="("), state.source, state=state)
        if state.is_error:
            return state, ParenthesisExpParserState.END

        expr.append([])
        stack.append(expr[len(expr)-1])
        return self._runner.run(self._whitespace_opt, state.source, state=state), ParenthesisExpParserState.ELEMENT_OR_OPENING

    def _close_parenthesis(self, state: parser.State, expr: list, stack: list) -> Tuple[parser.State, ParenthesisExpParserState]:
        "closes the current parenthesis expression in the expr and stack, sets to OPERATOR_OR_CLOSING state"
        state = self._runner.run(parser.CharParser(locate=")"), state.source, state=state)
        if state.is_error:
            return state, ParenthesisExpParserState.END

        stack.pop()

        # check if expression parsing fully complete
        if not len(stack):
            return state, ParenthesisExpParserState.END

        return self._runner.run(self._whitespace_opt, state.source, state=state), ParenthesisExpParserState.OPERATOR_OR_CLOSING

    def _element_or_opening(self, next_char: str, state: parser.State, expr: list, stack: list) -> Tuple[parser.State, ParenthesisExpParserState]:
        """
        ensures an invalid parenthesis close is not present, handles opening a new expression or processes the current element 
            and prepares the state for the next step
        """
        if next_char == ")":
            state.is_error = True
            state.error = f"ParenthesisExpressionParser: unexpected end of expression at index '{state.index}'"
            return state
        elif next_char == "(":
            return self._runner.run(self._whitespace_opt, state.source, state=state), ParenthesisExpParserState.OPEN_PARENTHESIS
        else:
            state = self._runner.choice(
                (
                    parser.HexParser(map_method=_hex_value_as_type),
                    VariableParser(self._runner, map_method=_var_value_as_type),
                ),
                state.source,
                state=state,
            )
            if state.is_error:
                return state, ParenthesisExpParserState.END
            stack[len(stack)-1].append(parser.State(state=state))
            return self._runner.run(self._whitespace_opt, state.source, state=state), ParenthesisExpParserState.OPERATOR_OR_CLOSING

    def _operator_or_closing(self, next_char: str, state: parser.State, expr: list, stack: list) -> Tuple[parser.State, ParenthesisExpParserState]:
        """
        checks for closing parenthesis and returns CLOSE state if so, otherwise we should only expect an operator, so parse the operator and set to
            next state ELEMENT_OR_OPENING
        """
        if next_char == ")":
            return self._runner.run(self._whitespace_opt, state.source, state=state), ParenthesisExpParserState.CLOSE_PARENTHESIS

        state = self._runner.run(OperatorParser(self._runner, map_method=_operator_value_as_type), state.source, state=state)
        if state.is_error:
            return state, ParenthesisExpParserState.END

        stack[len(stack)-1].append(parser.State(state=state))
        return self._runner.run(self._whitespace_opt, state.source, state=state), ParenthesisExpParserState.ELEMENT_OR_OPENING
