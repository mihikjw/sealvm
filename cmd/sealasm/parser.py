import sys
import os
import json
from typing import Tuple, List, Dict, Any, Optional

import asm
import parser_combinator


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
        # TODO: improve this
        print("USAGE: parser [source_file.asm] {ast_output_dir}\n\n-h: output help")
        return None, None

    # process as source file
    if not os.path.isfile(arg_1):
        raise ValueError(f"Source File {arg_1} Does Not Exist")

    file_name = os.path.basename(arg_1)
    split_file_name = file_name.split(".")

    if len(split_file_name):
        file_name = split_file_name[0]

    # get optional ast path
    if len(sys.argv) >= 3:
        ast_out = f"{sys.argv[2]}/{file_name}.ast"
    else:
        ast_out = f"{os.getcwd()}/{file_name}.ast"

    return arg_1, ast_out


def main():
    "program entrypoint, creates an AST file for the compiler"
    src_path: str
    ast_out_path: str

    try:
        src_path, ast_out_path = _get_args()
        if src_path is None or ast_out_path is None:
            sys.exit(0)
    except ValueError as ex:
        print(str(ex))
        sys.exit(1)

    runner = parser_combinator.Runner()
    parser = asm.InstructionParser(runner)

    try:
        ast: List[Dict[str, Any]] = []

        with open(src_path, "r") as fhandle:
            line = fhandle.readline()
            line_number = 1

            if not len(line):
                raise RuntimeError(f"Line {line_number}: EOF Reached At Start Of File")

            for line in fhandle:
                line = line.rstrip()
                if not len(line):
                    # skip empty lines
                    continue

                state: parser.State = runner.run(parser, line)
                if state.is_error:
                    raise ValueError(f"Line {line_number}: {state.error}")

                ast.append(state.result)
                line_number += 1

        if not len(ast):
            raise RuntimeError("Parser AST Is Empty")

        with open(ast_out_path, "w", encoding="utf-8") as fhandle:
            json.dump(ast, fhandle, ensure_ascii=False)
    except ValueError as ex:
        # treat ValueError as an error in the source code, exit code 2
        print(str(ex))
        sys.exit(2)
    except Exception as ex:
        # all other exceptions are invalid args/non existing file/parser bug etc, exit code 1
        print(f"Exception Parsing File {src_path}: {str(ex)}")
        sys.exit(1)


if __name__ == "__main__":
    main()
