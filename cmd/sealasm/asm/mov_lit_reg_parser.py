from typing import Tuple, Any

import parser_combinator as parser

from asm.asm_parser_base import ASMParser
from asm.sqr_bracket_expression_parser import SqrBracketExpressionParser
from asm.map_methods import _hex_value_as_type, _sqr_expr_as_type, _disambiguate_expression, _register_as_type


class MovLitRegParser(ASMParser):
    "parses a MOV_LIT_REG instruction for the SealASM grammer"

    def __init__(self, runner: parser.Runner, map_method: Any = None):
        super().__init__(runner, map_method)

    def run(self, state: parser.State) -> parser.State:
        instruction_args: List[Dict[str, Any]] = []
        instruction: Dict[str, Any] = {"instruction": "MOV_LIT_REG"}
        result: Dict[str, Any] = {"type": "INSTRUCTION"}

        whitespace_force = parser.WhitespaceParser()
        whitespace_opt = parser.WhitespaceParser(optional=True)

        # get mov and skip whitespace
        state = self._upper_or_lower_string("mov", state.source, state)
        if state.is_error:
            return state

        state = self._runner.run(whitespace_force, state.source, state=state)
        if state.is_error:
            return state

        # get hex value or parse expression
        state = self._runner.choice((
            parser.HexParser(map_method=_hex_value_as_type),    # type: ignore
            SqrBracketExpressionParser(self._runner, map_method=(_sqr_expr_as_type, _disambiguate_expression)),
        ), state.source, state=state)
        if state.is_error:
            return state
        instruction_args.append(self._state_to_ast(state))

        # get comma and optional whitespace
        state = self._runner.run(parser.StringParser(","), state.source, state=state)
        if state.is_error:
            return state

        state = self._runner.run(whitespace_opt, state.source, state=state)
        if state.is_error:
            return state

        # get register, skip optional whitespace
        state = self._register(state.source, state).map(_register_as_type)
        if state.is_error:
            return state
        instruction_args.append(state.result)

        state = self._runner.run(whitespace_opt, state.source, state=state)
        if state.is_error:
            return state

        # organise output tree
        instruction["args"] = instruction_args
        result["value"] = instruction
        return parser.State(source=state.source, result=result, index=state.index)
