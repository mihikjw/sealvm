import sys
import os
import json
from typing import Tuple, List, Dict, Any, Optional

import asm
import sealvm
import parser_combinator
import compiler

# ---------------------
# this program is a bit rough and ready at the moment, it will be improved soon.
# ---------------------


def _get_args() -> Tuple[Optional[str], Optional[str]]:
    """
    looks at the cmd-line args and establishes actions
    will raise ValueError if incorrectly configured
    will return (None, None) is a simple exit without any errors is required
    """
    # TODO: refactor this method to make it resiliant and support flags etc
    if len(sys.argv) < 2:
        raise ValueError("Invalid Number Of Args, Use '-h' For Usage Details")

    arg_1: str = sys.argv[1]

    if arg_1.lower() == "-h":
        # output help
        print("USAGE: parser [source_file.asm] {bin_output_dir}\n\n-h: output help")
        return None, None

    # process as source file
    if not os.path.isfile(arg_1):
        raise ValueError(f"Source File {arg_1} Does Not Exist")

    file_name = os.path.basename(arg_1)
    split_file_name = file_name.split(".")

    if len(split_file_name):
        file_name = split_file_name[0]

    # get optional binary path
    if len(sys.argv) >= 3:
        bin_out = f"{sys.argv[2]}/{file_name}.seal"
    else:
        bin_out = f"{os.getcwd()}/{file_name}.seal"

    return arg_1, bin_out


def main():
    "program entrypoint"
    src_path: str
    bin_out_path: str

    try:
        src_path, bin_out_path = _get_args()
        if src_path is None or bin_out_path is None:
            sys.exit(0)
    except ValueError as ex:
        print(str(ex))
        sys.exit(1)

    runner = parser_combinator.Runner()
    parser = asm.InstructionParser(runner)
    compile = compiler.Compiler()

    try:
        machine_code: list = []
        line_number = 1

        with open(src_path, "r") as fhandle:
            for line in fhandle:
                line = line.rstrip().lstrip()
                if not len(line):
                    # skip empty lines
                    continue

                state: parser.State = runner.choice(
                    (

                        asm.InstructionParser(runner),
                        asm.LabelParser(runner, map_method=asm._label_value_as_type)
                    ),
                    line
                )

                if state.is_error:
                    raise ValueError(f"Line {line_number}: {state.error}")

                if state.result["type"] != "LABEL":
                    value = state.result["value"]
                    metadata: sealvm.InstructionDef = sealvm.InstructionMap[value["instruction"]]
                    compile.current_address += metadata.size

                    compiled_code = compile.line(state.result)
                    machine_code.extend(compiled_code)
                else:
                    compile.labels[state.result["value"]] = compile.current_address

                line_number += 1

        if not len(machine_code):
            raise RuntimeError("Machine Code Is Empty")

        # write executable
        with open(bin_out_path, "w") as fhandle:
            for code in machine_code:
                fhandle.write(f"{hex(code)} ")

    except ValueError as ex:
        # treat ValueError as an error in the source code, exit code 2
        print(str(ex))
        sys.exit(2)
    except KeyError as ex:
        # treat KeyError as an invalid AST being produced
        print(f"Invalid AST: {str(ex)}")
        sys.exit(1)
    except Exception as ex:
        # all other exceptions are invalid args/non existing file/parser bug etc, exit code 1
        print(f"Exception Parsing File {src_path}: {str(ex)}")
        sys.exit(1)


if __name__ == "__main__":
    main()
