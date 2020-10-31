from typing import Any

import parser
from asm.types import Operators


def _hex_value_as_type(state: parser.State) -> parser.State:
    "method for mapping hex literals as an AST type"
    if not state.is_error:
        state.result = {"type": "HEX_LITERAL", "value": state.result}
    return state


def _sqr_expr_as_type(state: parser.State) -> parser.State:
    "method for mapping square expressions as an AST type"
    if not state.is_error:
        state.result = {
            "type": "SQUARE_BRACKET_EXPRESSION",
            "value": state.result,
        }
    return state


def _parenthesis_expr_as_type(state: parser.State) -> parser.State:
    "method for mapping parenthesis expressions as an AST type"
    if not state.is_error:
        state.result = _parenthesis_expr_array_as_type(state.result).result
    return state


def _parenthesis_expr_array_as_type(element) -> parser.State:
    if isinstance(element, list) and len(element):
        for i, e in enumerate(element):
            element[i] = _parenthesis_expr_array_as_type(e)

        index = element[0].index
        source = element[0].source
        output = {
            "type": "PARENTHESIS_EXPRESSION",
            "value": element,
        }
        element = parser.State(source=source, result=output, index=index)
    return element


def _var_value_as_type(state: parser.State) -> parser.State:
    "method for mapping variables as an AST type"
    if not state.is_error:
        state.result = {
            "type": "VARIABLE",
            "value": state.result,
        }
    return state


def _operator_value_as_type(state: parser.State) -> parser.State:
    "method for mapping operators as an AST type"
    if not state.is_error:
        if state.result in Operators.operator_code_map:
            state.result = {
                "type": Operators.operator_code_map[state.result],
                "value": state.result,
            }
        else:
            state.is_error = True
            state.error = f"OperatorValueAsType: operator {state.result} not supported at index {state.index}"
    return state
