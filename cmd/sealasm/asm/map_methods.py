from typing import Any, List, Dict

import parser_combinator as parser
from asm.types import Operators
from asm.registers import Registers


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


def _register_as_type(state: parser.State) -> parser.State:
    "method for mapping registers as an AST type"
    if not state.is_error:
        if state.result in Registers:
            state.result = {
                "type": "REGISTER",
                "value": state.result,
            }
        else:
            state.is_error = True
            state.error = f"RegisterAsType: register {state.result} not supported at index {state.index}"
    return state


def _memory_address_as_type(state: parser.State) -> parser.State:
    "method for mapping a memory address as an AST type"
    if not state.is_error:
        if isinstance(state.result, list):
            state.result = _sqr_expr_as_type(state).result
            state.result = _disambiguate_expression(state).result
        else:
            state.result = _hex_value_as_type(state).result
    return state


def _disambiguate_expression(state: parser.State) -> parser.State:
    """
    method to ensure operator precedence in expressions (see asm.types for priorities)
    recursive method, translates all expressions to a single BINARY_EXPRESSION type
    """
    if state.is_error:
        return state

    if state.result["type"] not in ("PARENTHESIS_EXPRESSION", "SQUARE_BRACKET_EXPRESSION"):
        return state

    # complete, translate expression to binary operation
    value: List[parser.State] = state.result["value"]
    if len(value) == 1:
        item = value[0]
        state.result["type"] = item.result["type"]
        state.result["value"] = item.result["value"]
        return state

    candidate_expr: Dict[str, Any] = {
        "priority": -1
    }

    for i in range(1, len(value)):
        # operators only at odd index's, so can skip even values
        if not i % 2:
            continue

        operator_entry: parser.State = value[i]
        operator_priority = Operators.priorities[operator_entry.result["type"]]

        # if the operator priority is more than that which we already have,
        #   process this operator and process the previous on next recursion
        if operator_priority > candidate_expr["priority"]:
            candidate_expr = {
                "priority": operator_priority,
                "a": i - 1,
                "b": i + 1,
                "op": operator_entry,
            }

    # set new type for expression, recurse on A and B sides to ensure they're disambiguated
    binary_expression = parser.State(
        source=operator_entry.source,
        index=operator_entry.index,
        result={
            "type": "BINARY_OPERATION",
            "value": {
                "a": value[candidate_expr["a"]].map(_disambiguate_expression),
                "b": value[candidate_expr["b"]].map(_disambiguate_expression),
                "op": candidate_expr["op"],
            }
        }
    )

    # rebuild result and recursive disambiguate
    state.result["value"] = value[:candidate_expr["a"]] + [binary_expression] + value[candidate_expr["b"] + 1:]
    state.map(_disambiguate_expression)
    return state
