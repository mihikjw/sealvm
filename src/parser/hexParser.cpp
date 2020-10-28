#include "parser/hexParser.hpp"

using namespace Parser;

HexParser::HexParser() { regex = std::regex("^[0-9A-Fa-f]+"); }

State* HexParser::Run(State* state) {
    if (state->IsError) {
        return state;
    }

    if (state->Input.empty() || (unsigned int)state->Input.size() < (unsigned int)state->Index + 1) {
        return setErrorState(state, "HexParser: got unexpected end of input");
    }

    auto toCheck = state->Input.substr(state->Index);
    auto toCheckStart = toCheck.begin();

    // bypass definition that this is hex, if present
    if (toCheck.at(0) == *"$") {
        toCheckStart++;
    }

    std::sregex_token_iterator it(toCheckStart, toCheck.end(), regex, 0);
    std::sregex_token_iterator end;

    if (it == end) {
        return setErrorState(state, "HexParser: couldn't match hex at index '" + std::to_string(state->Index) + "'");
    }

    state->Result = *it;
    state->Index = state->Index + it->length();
    state->IsError = false;
    state->Error = "";
    return state;
}