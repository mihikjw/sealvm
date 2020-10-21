#include "parser/whitespaceParser.hpp"

using namespace Parser;

State* WhitespaceParser::Run(State* state) {
    if (state->IsError) {
        return state;
    }

    if (state->Input.empty() || (unsigned int)state->Input.size() < (unsigned int)state->Index + 1) {
        if (!opt) {
            return setErrorState(state, "WhitespaceParser: got unexpected end of input");
        }

        // could be used to trim trailing whitespace on a line, so we should support empty string as valid if opt is defined
        state->Result = "";
        return state;
    }

    auto toCheck = state->Input.substr(state->Index, 1);

    if (toCheck == " ") {
        state->Result = toCheck;
        state->Index++;
    } else if (opt) {
        state->Result = "";
    } else {
        state->IsError = true;
        state->Error = "WhitespaceParser: No whitespace found at index '" + std::to_string(state->Index) + "'";
    }

    return state;
}