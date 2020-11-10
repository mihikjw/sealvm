from typing import List, Dict, Any, Optional, Tuple

import asm
import parser_combinator
import compiler
import sealvm


def read_code(src_path: str, runner: parser_combinator.Runner, parser: asm.InstructionParser,
              compile: compiler.Compiler, ast: bool = False) -> Tuple[List[int], Optional[List[Dict[str, Any]]]]:
    """
    reads and compiles source code, returns machine code
    will throw exceptions on error
    """
    machine_code: List[int] = []
    line_number = 1

    if ast:
        ast_out: Optional[List[Dict[str, Any]]] = []
    else:
        ast_out = None

    with open(src_path, "r") as fhandle:
        for line in fhandle:
            line = line.rstrip().lstrip()
            if not len(line):
                continue

            state: parser_combinator.State = runner.choice(
                (
                    asm.InstructionParser(runner),  # type: ignore
                    asm.LabelParser(runner, map_method=asm._label_value_as_type)
                ),
                line
            )

            if state.is_error:
                raise ValueError(f"Line {line_number}: {state.error}")

            if ast and ast_out is not None:
                ast_out.append(state.result)

            if state.result["type"] != "LABEL":
                value = state.result["value"]
                metadata: sealvm.InstructionDef = sealvm.InstructionMap[value["instruction"]]
                compile.current_address += metadata.size

                compiled_code = compile.line(state.result)
                machine_code.extend(compiled_code)
            else:
                compile.labels[state.result["value"]] = compile.current_address

            line_number += 1

    return machine_code, ast_out
