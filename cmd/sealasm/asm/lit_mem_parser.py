from typing import Tuple, Any, List, Dict

import parser_combinator as parser

from asm.asm_parser_base import ASMParser
from asm.sqr_bracket_expression_parser import SqrBracketExpressionParser
from asm.map_methods import _register_as_type, _memory_address_as_type, _hex_value_as_type, _sqr_expr_as_type, _disambiguate_expression, _register_as_type


class LitMemParser(ASMParser):
    "parses a '{literal}, {address}' instruction for the SealASM grammer"

    def __init__(self, runner: parser.Runner, instruction_mnemonic: str, instruction: str, map_method: Any = None):
        super().__init__(runner, instruction_mnemonic, instruction, map_method=map_method)

    def run(self, state: parser.State) -> parser.State:
        instruction_args: List[Dict[str, Any]] = []

        # get mov
        state = self._upper_or_lower_string(self._instruction_mnemonic, state.source, state)
        if state.is_error:
            return state

        state = self._whitespace(state)
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

        state = self._comma_skip_whitespace(state)
        if state.is_error:
            return state

        # get target memory address
        state = self._address(state).map(_memory_address_as_type)
        if state.is_error:
            return state
        instruction_args.append(self._state_to_ast(state))

        state = self._optional_whitespace(state)
        if state.is_error:
            return state

        # setup result tree
        result = {
            "type": self._instruction_mnemonic,
            "value": {
                "instruction": self._instruction,
                "args": instruction_args,
            }
        }
        return parser.State(source=state.source, result=result, index=state.index)