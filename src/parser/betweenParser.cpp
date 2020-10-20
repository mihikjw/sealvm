#include "parser/betweenParser.hpp"

using namespace Parser;

State* BetweenParser::Run(State* state) {
    if (state->IsError) {
        return state;
    }

    std::size_t startPos = state->Input.find(left, state->Index);
    if (startPos == std::string::npos) {
        return setErrorState(state, "BetweenParser: tried to match '" + left + "', but got '" + state->Input + "'");
    }
    startPos++;

    std::size_t finalIndex = state->Input.find(right, state->Index);
    if (startPos == std::string::npos) {
        return setErrorState(state, "BetweenParser: tried to match '" + right + "', but got '" + state->Input + "'");
    }

    auto endPos = finalIndex - startPos;
    state->Result = state->Input.substr(startPos, endPos);
    state->Index = finalIndex++;
    state->Error = "";
    state->IsError = false;
    return state;
}
