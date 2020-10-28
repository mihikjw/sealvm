#include "parser/regexParser.hpp"

using namespace Parser;

RegexParser::RegexParser(const std::regex* regex) { this->regex = regex; }

State* RegexParser::Run(State* state) {
    if (state->IsError) {
        return state;
    }

    if (state->Input.empty() || (unsigned int)state->Input.size() < (unsigned int)state->Index + 1) {
        return setErrorState(state, "RegexParser: got unexpected end of input");
    }

    std::smatch match;
    auto toCheck = state->Input.substr(state->Index);

    if (!std::regex_search(toCheck, match, *regex)) {
        return setErrorState(state, "RegexParser: couldn't match regex at index '" + std::to_string(state->Index) + "'");
    }

    if (match.empty()) {
        return setErrorState(state, "RegexParser: couldn't match regex at index '" + std::to_string(state->Index) + "'");
    }

    auto output = std::vector<std::string>();

    for (auto const& matchedString : match) {
        if (matchedString.matched) {
            output.push_back(matchedString.str());
        }
    }

    state->ResultMultiple = output;
    state->Index = state->Index + state->Result.size();
    state->IsError = false;
    state->Error = "";
    return state;
}