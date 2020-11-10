from typing import Tuple, Any

import parser_combinator as parser

from asm.lit_reg_parser import LitRegParser
from asm.reg_reg_parser import RegRegParser
from asm.reg_mem_parser import RegMemParser
from asm.mem_reg_parser import MemRegParser
from asm.lit_mem_parser import LitMemParser
from asm.reg_ptr_reg_parser import RegPtrRegParser
from asm.lit_off_reg_parser import LitOffRegParser
from asm.no_arg_parser import NoArgParser
from asm.lit_parser import LitParser
from asm.reg_parser import RegParser
from asm.reg_lit_parser import RegLitParser


class MovParser(parser.BaseParser):
    "parses a SealASM MOV instruction"

    def __init__(self, runner: parser.Runner, map_method: Any = None):
        self._runner: parser.Runner = runner
        super().__init__(map_method)

    def run(self, state: parser.State) -> parser.State:
        if state.is_error:
            return state

        return self._runner.choice((
            RegRegParser(self._runner, "MOV", "MOV_REG_REG", map_method=self._map_method),  # type: ignore
            LitRegParser(self._runner, "MOV", "MOV_LIT_REG", map_method=self._map_method),    
            RegMemParser(self._runner, "MOV", "MOV_REG_MEM", map_method=self._map_method),
            MemRegParser(self._runner, "MOV", "MOV_MEM_REG", map_method=self._map_method),
            LitMemParser(self._runner, "MOV", "MOV_LIT_MEM", map_method=self._map_method),
            RegPtrRegParser(self._runner, "MOV", "MOV_REG_PTR_REG", map_method=self._map_method),
            LitOffRegParser(self._runner, "MOV", "MOV_LIT_OFF_REG", map_method=self._map_method),
        ), state.source, state=state)


class AddParser(parser.BaseParser):
    "parses a SealASM ADD instruction"

    def __init__(self, runner: parser.Runner, map_method: Any = None):
        self._runner: parser.Runner = runner
        super().__init__(map_method)

    def run(self, state: parser.State) -> parser.State:
        if state.is_error:
            return state

        return self._runner.choice((
            LitRegParser(self._runner, "ADD", "ADD_LIT_REG", map_method=self._map_method),    # type: ignore
            RegRegParser(self._runner, "ADD", "ADD_REG_REG", map_method=self._map_method),
            RegLitParser(self._runner, "ADD", "ADD_REG_LIT", map_method=self._map_method),
        ), state.source, state=state)


class SubParser(parser.BaseParser):
    "parses a SealASM SUB instruction"

    def __init__(self, runner: parser.Runner, map_method: Any = None):
        self._runner: parser.Runner = runner
        super().__init__(map_method)

    def run(self, state: parser.State) -> parser.State:
        if state.is_error:
            return state

        return self._runner.choice((
            LitRegParser(self._runner, "SUB", "SUB_LIT_REG", map_method=self._map_method),    # type: ignore
            RegLitParser(self._runner, "SUB", "SUB_REG_LIT", map_method=self._map_method),
            RegRegParser(self._runner, "SUB", "SUB_REG_REG", map_method=self._map_method),
        ), state.source, state=state)


class MulParser(parser.BaseParser):
    "parses a SealASM MUL instruction"

    def __init__(self, runner: parser.Runner, map_method: Any = None):
        self._runner: parser.Runner = runner
        super().__init__(map_method)

    def run(self, state: parser.State) -> parser.State:
        if state.is_error:
            return state

        return self._runner.choice((
            LitRegParser(self._runner, "MUL", "MUL_LIT_REG", map_method=self._map_method),    # type: ignore
            RegRegParser(self._runner, "MUL", "MUL_REG_REG", map_method=self._map_method),
        ), state.source, state=state)


class LeftShiftParser(parser.BaseParser):
    "parses a SealASM LSF instruction"

    def __init__(self, runner: parser.Runner, map_method: Any = None):
        self._runner: parser.Runner = runner
        super().__init__(map_method)

    def run(self, state: parser.State) -> parser.State:
        if state.is_error:
            return state

        return self._runner.choice((
            RegRegParser(self._runner, "LSF", "LSF_REG_REG", map_method=self._map_method),  # type: ignore
            RegLitParser(self._runner, "LSF", "LSF_REG_LIT", map_method=self._map_method),
        ), state.source, state=state)


class RightShiftParser(parser.BaseParser):
    "parses a SealASM RSF instruction"

    def __init__(self, runner: parser.Runner, map_method: Any = None):
        self._runner: parser.Runner = runner
        super().__init__(map_method)

    def run(self, state: parser.State) -> parser.State:
        if state.is_error:
            return state

        return self._runner.choice((
            LitRegParser(self._runner, "RSF", "RSF_REG_LIT", map_method=self._map_method),    # type: ignore
            RegRegParser(self._runner, "RSF", "RSF_REG_REG", map_method=self._map_method),
        ), state.source, state=state)


class AndParser(parser.BaseParser):
    "parses a SealASM AND instruction"

    def __init__(self, runner: parser.Runner, map_method: Any = None):
        self._runner: parser.Runner = runner
        super().__init__(map_method)

    def run(self, state: parser.State) -> parser.State:
        if state.is_error:
            return state

        return self._runner.choice((
            LitRegParser(self._runner, "AND", "AND_LIT_REG", map_method=self._map_method),    # type: ignore
            RegRegParser(self._runner, "AND", "AND_REG_REG", map_method=self._map_method),
        ), state.source, state=state)


class OrParser(parser.BaseParser):
    "parses a SealASM OR instruction"

    def __init__(self, runner: parser.Runner, map_method: Any = None):
        self._runner: parser.Runner = runner
        super().__init__(map_method)

    def run(self, state: parser.State) -> parser.State:
        if state.is_error:
            return state

        return self._runner.choice((
            LitRegParser(self._runner, "OR", "OR_LIT_REG", map_method=self._map_method),    # type: ignore
            RegRegParser(self._runner, "OR", "OR_REG_REG", map_method=self._map_method),
        ), state.source, state=state)


class XorParser(parser.BaseParser):
    "parses a SealASM XOR instruction"

    def __init__(self, runner: parser.Runner, map_method: Any = None):
        self._runner: parser.Runner = runner
        super().__init__(map_method)

    def run(self, state: parser.State) -> parser.State:
        if state.is_error:
            return state

        return self._runner.choice((
            LitRegParser(self._runner, "XOR", "XOR_LIT_REG", map_method=self._map_method),    # type: ignore
            RegRegParser(self._runner, "XOR", "XOR_REG_REG", map_method=self._map_method),
        ), state.source, state=state)


class IncParser(parser.BaseParser):
    "parses a SealASM INC instruction"

    def __init__(self, runner: parser.Runner, map_method: Any = None):
        self._runner: parser.Runner = runner
        super().__init__(map_method)

    def run(self, state: parser.State) -> parser.State:
        if state.is_error:
            return state

        return self._runner.choice((
            RegParser(self._runner, "INC", "INC_REG", map_method=self._map_method),    # type: ignore
        ), state.source, state=state)


class DecParser(parser.BaseParser):
    "parses a SealASM DEC instruction"

    def __init__(self, runner: parser.Runner, map_method: Any = None):
        self._runner: parser.Runner = runner
        super().__init__(map_method)

    def run(self, state: parser.State) -> parser.State:
        if state.is_error:
            return state

        return self._runner.choice((
            RegParser(self._runner, "DEC", "DEC_REG", map_method=self._map_method),    # type: ignore
        ), state.source, state=state)


class NotParser(parser.BaseParser):
    "parses a SealASM NOT instruction"

    def __init__(self, runner: parser.Runner, map_method: Any = None):
        self._runner: parser.Runner = runner
        super().__init__(map_method)

    def run(self, state: parser.State) -> parser.State:
        if state.is_error:
            return state

        return self._runner.choice((
            RegParser(self._runner, "NOT", "NOT", map_method=self._map_method),    # type: ignore
        ), state.source, state=state)


class JeqParser(parser.BaseParser):
    "parses a SealASM JEQ instruction"

    def __init__(self, runner: parser.Runner, map_method: Any = None):
        self._runner: parser.Runner = runner
        super().__init__(map_method)

    def run(self, state: parser.State) -> parser.State:
        if state.is_error:
            return state

        return self._runner.choice((
            RegMemParser(self._runner, "JEQ", "JEQ_REG", map_method=self._map_method),    # type: ignore
            LitMemParser(self._runner, "JEQ", "JEQ_LIT", map_method=self._map_method),
        ), state.source, state=state)


class JneParser(parser.BaseParser):
    "parses a SealASM JEN instruction"

    def __init__(self, runner: parser.Runner, map_method: Any = None):
        self._runner: parser.Runner = runner
        super().__init__(map_method)

    def run(self, state: parser.State) -> parser.State:
        if state.is_error:
            return state

        return self._runner.choice((
            RegMemParser(self._runner, "JNE", "JNE_REG", map_method=self._map_method),    # type: ignore
            LitMemParser(self._runner, "JNE", "JNE_LIT", map_method=self._map_method),
        ), state.source, state=state)


class JltParser(parser.BaseParser):
    "parses a SealASM JLT instruction"

    def __init__(self, runner: parser.Runner, map_method: Any = None):
        self._runner: parser.Runner = runner
        super().__init__(map_method)

    def run(self, state: parser.State) -> parser.State:
        if state.is_error:
            return state

        return self._runner.choice((
            RegMemParser(self._runner, "JLT", "JLT_REG", map_method=self._map_method),    # type: ignore
            LitMemParser(self._runner, "JLT", "JLT_LIT", map_method=self._map_method),
        ), state.source, state=state)


class JgtParser(parser.BaseParser):
    "parses a SealASM JGT instruction"

    def __init__(self, runner: parser.Runner, map_method: Any = None):
        self._runner: parser.Runner = runner
        super().__init__(map_method)

    def run(self, state: parser.State) -> parser.State:
        if state.is_error:
            return state

        return self._runner.choice((
            RegMemParser(self._runner, "JGT", "JGT_REG", map_method=self._map_method),    # type: ignore
            LitMemParser(self._runner, "JGT", "JGT_LIT", map_method=self._map_method),
        ), state.source, state=state)


class JleParser(parser.BaseParser):
    "parses a SealASM JLE instruction"

    def __init__(self, runner: parser.Runner, map_method: Any = None):
        self._runner: parser.Runner = runner
        super().__init__(map_method)

    def run(self, state: parser.State) -> parser.State:
        if state.is_error:
            return state

        return self._runner.choice((
            RegMemParser(self._runner, "JLE", "JLE_REG", map_method=self._map_method),    # type: ignore
            LitMemParser(self._runner, "JLE", "JLE_LIT", map_method=self._map_method),
        ), state.source, state=state)


class JgeParser(parser.BaseParser):
    "parses a SealASM JGE instruction"

    def __init__(self, runner: parser.Runner, map_method: Any = None):
        self._runner: parser.Runner = runner
        super().__init__(map_method)

    def run(self, state: parser.State) -> parser.State:
        if state.is_error:
            return state

        return self._runner.choice((
            RegMemParser(self._runner, "JGE", "JGE_REG", map_method=self._map_method),    # type: ignore
            LitMemParser(self._runner, "JGE", "JGE_LIT", map_method=self._map_method),
        ), state.source, state=state)


class PshParser(parser.BaseParser):
    "parses a SealASM PSH instruction"

    def __init__(self, runner: parser.Runner, map_method: Any = None):
        self._runner: parser.Runner = runner
        super().__init__(map_method)

    def run(self, state: parser.State) -> parser.State:
        if state.is_error:
            return state

        return self._runner.choice((
            LitParser(self._runner, "PSH", "PSH_LIT", map_method=self._map_method),    # type: ignore
            RegParser(self._runner, "PSH", "PSH_REG", map_method=self._map_method),
        ), state.source, state=state)


class PopParser(parser.BaseParser):
    "parses a SealASM POP instruction"

    def __init__(self, runner: parser.Runner, map_method: Any = None):
        self._runner: parser.Runner = runner
        super().__init__(map_method)

    def run(self, state: parser.State) -> parser.State:
        if state.is_error:
            return state

        return self._runner.choice((
            RegParser(self._runner, "POP", "POP_REG", map_method=self._map_method),    # type: ignore
        ), state.source, state=state)


class CalParser(parser.BaseParser):
    "parses a SealASM CAL instruction"

    def __init__(self, runner: parser.Runner, map_method: Any = None):
        self._runner: parser.Runner = runner
        super().__init__(map_method)

    def run(self, state: parser.State) -> parser.State:
        if state.is_error:
            return state

        return self._runner.choice((
            RegParser(self._runner, "CAL", "CAL_REG", map_method=self._map_method),    # type: ignore
            LitParser(self._runner, "CAL", "CAL_LIT", map_method=self._map_method),
        ), state.source, state=state)


class RetParser(parser.BaseParser):
    "parses a SealASM RET instruction"

    def __init__(self, runner: parser.Runner, map_method: Any = None):
        self._runner: parser.Runner = runner
        super().__init__(map_method)

    def run(self, state: parser.State) -> parser.State:
        if state.is_error:
            return state

        return self._runner.choice((
            NoArgParser(self._runner, "RET", "RET", map_method=self._map_method),    # type: ignore
        ), state.source, state=state)


class HltParser(parser.BaseParser):
    "parses a SealASM HLT instruction"

    def __init__(self, runner: parser.Runner, map_method: Any = None):
        self._runner: parser.Runner = runner
        super().__init__(map_method)

    def run(self, state: parser.State) -> parser.State:
        if state.is_error:
            return state

        return self._runner.choice((
            NoArgParser(self._runner, "HLT", "HLT", map_method=self._map_method),    # type: ignore
        ), state.source, state=state)


class IntParser(parser.BaseParser):
    "parses a SealASM INT instruction"

    def __init__(self, runner: parser.Runner, map_method: Any = None):
        self._runner: parser.Runner = runner
        super().__init__(map_method)

    def run(self, state: parser.State) -> parser.State:
        if state.is_error:
            return state

        return self._runner.choice((
            LitParser(self._runner, "INT", "INT", map_method=self._map_method),    # type: ignore
        ), state.source, state=state)


class RetIntParser(parser.BaseParser):
    "parses a SealASM RET_INT instruction"

    def __init__(self, runner: parser.Runner, map_method: Any = None):
        self._runner: parser.Runner = runner
        super().__init__(map_method)

    def run(self, state: parser.State) -> parser.State:
        if state.is_error:
            return state

        return self._runner.choice((
            NoArgParser(self._runner, "RET_INT", "RET_INT", map_method=self._map_method),    # type: ignore
        ), state.source, state=state)


class InstructionParser(parser.BaseParser):
    "parses a single SealASM Instruction"

    def __init__(self, runner: parser.Runner, map_method: Any = None):
        self._runner: parser.Runner = runner
        super().__init__(map_method)

    def run(self, state: parser.State) -> parser.State:
        if state.is_error:
            return state

        return self._runner.choice((
            MovParser(self._runner, map_method=self._map_method),    # type: ignore
            AddParser(self._runner, map_method=self._map_method),
            SubParser(self._runner, map_method=self._map_method),
            MulParser(self._runner, map_method=self._map_method),
            LeftShiftParser(self._runner, map_method=self._map_method),
            RightShiftParser(self._runner, map_method=self._map_method),
            AndParser(self._runner, map_method=self._map_method),
            OrParser(self._runner, map_method=self._map_method),
            XorParser(self._runner, map_method=self._map_method),
            IncParser(self._runner, map_method=self._map_method),
            DecParser(self._runner, map_method=self._map_method),
            NotParser(self._runner, map_method=self._map_method),
            JeqParser(self._runner, map_method=self._map_method),
            JneParser(self._runner, map_method=self._map_method),
            JltParser(self._runner, map_method=self._map_method),
            JgtParser(self._runner, map_method=self._map_method),
            JleParser(self._runner, map_method=self._map_method),
            JgeParser(self._runner, map_method=self._map_method),
            PshParser(self._runner, map_method=self._map_method),
            PopParser(self._runner, map_method=self._map_method),
            CalParser(self._runner, map_method=self._map_method),
            RetParser(self._runner, map_method=self._map_method),
            HltParser(self._runner, map_method=self._map_method),
            IntParser(self._runner, map_method=self._map_method),
            RetIntParser(self._runner, map_method=self._map_method),
        ), state.source, state=state)
