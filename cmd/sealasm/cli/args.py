from typing import Tuple, Optional, List, Dict
import sys
import os


def get_args() -> Tuple[Optional[str], Optional[str], Optional[str]]:
    """
    looks at the cmd-line args, establishes actions, and extracts required data
    will raise ValueError if incorrectly configured
    will return all results as None if program exit is required
    """
    args = _parse_args(sys.argv)

    if "-h" in args or "--help" in args:
        _output_help()
        return None, None, None
    elif "-v" in args or "--version" in args:
        _output_version()
        return None, None, None
    elif "src" not in args:
        raise ValueError("no source file given")

    if not os.path.isfile(args["src"]):
        raise ValueError(f"source file {args['src']} not found")

    if "-o" in args:
        bin_out = args["-o"]
    else:
        file_name = _get_file_name_no_ext(bin_out)
        bin_out = f"{os.getcwd()}/{file_name}.seal"

    if "--ast" in args:
        file_name = _get_file_name_no_ext(bin_out)
        ast_out_dir = os.path.dirname(bin_out)
        ast_out: Optional[str] = f"{ast_out_dir}/{file_name}.ast"
    elif "-ast" in args:
        ast_out = args["-ast"]
    else:
        ast_out = None

    return args["src"], bin_out, ast_out


def _parse_args(args: List[str]) -> Dict[str, str]:
    "parse command-line arguments into a map"
    result: Dict[str, str] = {}
    flag_name = ""
    flag = False

    for i, arg in enumerate(args):
        if not i:
            continue

        if arg[0] == "-":
            if arg[1] != "-":
                flag_name = arg
                flag = True
            else:
                result[arg] = ""
        elif flag:
            result[flag_name] = arg
            flag = False
        else:
            result["src"] = arg

    return result


def _get_file_name_no_ext(src: str) -> str:
    "returns a filename without extension from a full path"
    file_name = os.path.basename(src)
    split_file_name = file_name.split(".")

    if len(split_file_name):
        file_name = split_file_name[0]

    return file_name


def _output_help():
    _output_version()
    print(
        """USAGE: sealasm [source_file.asm]\n
-h | --help: output help
-v | --version: output version
-o [path]: specify output directory
-ast [path] | --ast: output parsed AST as JSON
        """
    )


def _output_version():
    print("VERSION: 0.1")
