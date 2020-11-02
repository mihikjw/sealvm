from typing import Tuple, Any

import parser_combinator as parser

from asm.asm_parser_base import ASMParser
from asm.sqr_bracket_expression_parser import SqrBracketExpressionParser
from asm.map_methods import _register_as_type


class MovRegRegParser(ASMParser):
    "parses a MOV_REG_REG instruction for the SealASM grammer"

    def __init__(self, runner: parser.Runner, map_method: Any = None):
        super().__init__(runner, map_method)

    def run(self, state: parser.State) -> parser.State:
        instruction_args: List[Dict[str, Any]] = []
        instruction: Dict[str, Any] = {"instruction": "MOV_REG_REG"}
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

        # get source register
        state = self._register(state.source, state).map(_register_as_type)
        if state.is_error:
            return state
        instruction_args.append(self._state_to_ast(state))

        # get comma and optional whitespace
        state = self._runner.run(parser.StringParser(",", 1), state.source, state=state)
        if state.is_error:
            return state

        state = self._runner.run(whitespace_opt, state.source, state=state)
        if state.is_error:
            return state

        # get target register, skip optional whitespace
        state = self._register(state.source, state).map(_register_as_type)
        if state.is_error:
            return state
        instruction_args.append(self._state_to_ast(state))

        state = self._runner.run(whitespace_opt, state.source, state=state)
        if state.is_error:
            return state

        # organise output tree
        instruction["args"] = instruction_args
        result["value"] = instruction
        return parser.State(source=state.source, result=result, index=state.index)
