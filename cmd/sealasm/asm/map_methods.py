import parser


def _hex_value_as_type(state: parser.State) -> parser.State:
    "method for mapping hex literals as an AST type"
    if not state.is_error:
        state.result = {"type": "HEX_LITERAL", "value": state.result}
    return state


def _sqr_expr_as_type(state: parser.State) -> parser.State:
    "method for mapping square expressions as an AST type"
    if not state.is_error:
        output = []

        for s in state.result:
            output.append(s.result)

        state.result = {
            "type": "SQUARE_BRACKET_EXPRESSION",
            "value": output,
        }
    return state


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
        state.result = {
            "type": "OPERATOR",
            "value": state.result,
        }
    return state
