import sys
from typing import Optional

import cli
import asm
import parser_combinator
import compiler


def main():
    src_path: Optional[str]
    bin_out_path: Optional[str]
    ast_out_path: Optional[str]

    try:
        src_path, bin_out_path, ast_out_path = cli.get_args()
        if src_path is None or bin_out_path is None:
            sys.exit(0)
    except ValueError as ex:
        print(str(ex))
        sys.exit(1)

    runner = parser_combinator.Runner()
    parser = asm.InstructionParser(runner)
    compile = compiler.Compiler()

    try:
        if ast_out_path is not None:
            write_ast = True
        else:
            write_ast = False

        machine_code, ast = cli.read_code(src_path, runner, parser, compile, ast=write_ast)
        if not len(machine_code):
            raise RuntimeError("machine code is empty")

        cli.write_binary(bin_out_path, machine_code)

        if write_ast:
            if ast is None:
                raise RuntimeError("ast requested, but not generated")
            cli.write_ast(ast_out_path, ast)
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
