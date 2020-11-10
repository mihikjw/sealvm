from typing import List, Dict, Any
import json


def write_binary(out_path: str, machine_code: List[int]) -> None:
    "writes the given machine code to the given output file"
    if not len(out_path):
        raise ValueError("write_binary: out_path is empty")
    if not len(machine_code):
        raise ValueError("write_binary: no machine_code provided")

    try:
        with open(out_path, "w") as fhandle:
            for code in machine_code:
                fhandle.write(f"{hex(code)} ")
    except Exception as ex:
        raise RuntimeError(str(ex))


def write_ast(out_path: str, ast: List[Dict[str, Any]]) -> None:
    "writes the given AST to the given output file as JSON"
    if not len(out_path):
        raise ValueError("write_ast: out_path is empty")
    if not len(ast):
        raise ValueError("write_ast: no ast provided")

    with open(out_path, "w", encoding="utf-8") as fhandle:
        json.dump(ast, fhandle, ensure_ascii=False)
