#include "parser/lettersParser.hpp"

using namespace Parser;

State* LettersParser::Run(State* state) {
    if (state->IsError) { 
        return state; 
    }

    if (state->Input.empty() || (unsigned int)state->Input.size() < (unsigned int)state->Index + 1) {
        return setErrorState(state, "LettersParser: got unexpected end of input");
    }

    auto toCheck = state->Input.substr(state->Index);
    auto output = std::regex_match(state->Input.c_str(), std::regex(regex));

    if (!output) {
        return setErrorState(state, "LettersParser: couldn't match letters at index '" + std::to_string(state->Index) + "'");
    }

    state->Result = toCheck;
    state->Index++;
    state->IsError = false;
    state->Error = "";
    return state;
}