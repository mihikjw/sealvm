from typing import Dict

import parser

from asm.sqr_bracket_expression_parser import SqrBracketExpressionParser
from asm.map_methods import _hex_value_as_type, _sqr_expr_as_type


class SealASMProcessor():
    "processes SealASM into an AST"

    def __init__(self, runner: parser.Runner, registers: Dict[str, int]):
        self._runner: parser.Runner = runner
        self._registers: Dict[str, int] = registers

    def process(self, src: str) -> parser.State:
        """
        process a line of asm into an AST
        this method is wip, currently just contains whatever I'm testing
        """
        return self._mov_lit_to_reg(src)

    def _mov_lit_to_reg(self, src: str) -> parser.State:
        "processes a mov literal to register instruction"
        instruction_args = []
        instruction = {"instruction": "MOV_LIT_REG"}
        result = {"type": "INSTRUCTION"}

        whitespace_force = parser.WhitespaceParser()
        whitespace_opt = parser.WhitespaceParser(optional=True)

        state = parser.State(source=src)

        # get mov and skip whitespace
        state = self._upper_or_lower_string("mov", src, state)
        if state.is_error:
            return state

        state = self._runner.run(whitespace_force, src, state=state)
        if state.is_error:
            return state

        # get hex value or parse expression
        state = self._runner.choice((
            parser.HexParser(map_method=_hex_value_as_type),
            SqrBracketExpressionParser(self._runner, map_method=_sqr_expr_as_type),
        ), src, state=state)
        if state.is_error:
            return state
        instruction_args.append(state.result)

        # get comma and optional whitespace
        state = self._runner.run(parser.StringParser(","), src, state=state)
        if state.is_error:
            return state

        state = self._runner.run(whitespace_opt, src, state=state)
        if state.is_error:
            return state

        # get register, skip optional whitespace
        state = self._register(src, state)
        if state.is_error:
            return state
        instruction_args.append({"type": "REGISTER", "value": state.result})

        state = self._runner.run(whitespace_opt, src, state=state)
        if state.is_error:
            return state

        # organise output tree
        instruction["args"] = instruction_args
        result["value"] = instruction
        return parser.State(source=state.source, result=result, index=state.index)

    def _upper_or_lower_string(self, locate: str, src: str, state: parser.State) -> parser.State:
        "locates the given upper or lowercase string in the given src string"
        upper = parser.StringParser(locate.upper())
        lower = parser.StringParser(locate.lower())
        return self._runner.choice((upper, lower), src)

    def _register(self, src: str, state: parser.State) -> parser.State:
        "reads a register from the given src and state"
        for reg in self._registers.keys():
            state = self._upper_or_lower_string(reg, src, state)
            if not state.is_error:
                break

        if not state.is_error:
            return state

        state.error = "Processor._register: unable to match register"
        return state
