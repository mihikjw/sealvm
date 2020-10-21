#include "parser/runner.hpp"

using namespace Parser;

State* Runner::Run(BaseParser* parser, const std::string& in, State* state) {
    if (!state) {
        state = new State{in};
    }
    return parser->Run(state);
}

State* Runner::SequenceOf(std::vector<BaseParser*>* parsers, const std::string& in, State* state) {
    if (!state) {
        state = new State{in};
    }

    auto results = std::make_shared<std::vector<std::shared_ptr<State>>>();

    for (auto const& parser : *parsers) {
        if (state->IsError) {
            return state;
        }
        state = parser->Run(state);
        results->push_back(std::make_shared<State>(state));
    }

    if (state->Results.get() && state->Results->empty()) {
        for (auto& res : *(results.get())) {
            state->Results->push_back(std::move(res));
        }
    } else {
        state->Results = results;
    }

    return state;
}

State* Runner::Choice(std::vector<BaseParser*>* parsers, const std::string& in, State* state) {
    if (!state) {
        state = new State{in};
    }

    auto startIndex = state->Index;

    for (auto const& parser : *parsers) {
        state = parser->Run(state);

        if (!state->IsError) {
            return state;
        }

        state->Index = startIndex;
        state->IsError = false;
        state->Error = "";
    }

    state->Error = "Choice: unable to match with any parser at index '" + std::to_string(state->Index) + "'";
    state->IsError = true;
    return state;
}

State* Runner::Many(BaseParser* parser, const std::string& in, bool many1, State* state) {
    if (!state) {
        state = new State(in);
    }

    auto results = std::make_shared<std::vector<std::shared_ptr<State>>>();
    unsigned int count = 0;
    bool done = false;

    while (!done) {
        auto tmpState = parser->Run(state);

        if (!tmpState->IsError) {
            results->push_back(std::make_shared<State>(tmpState));
            state = tmpState;
            count++;
        } else {
            done = true;
        }
    }

    if (many1 && !count) {
        state->Error = "Many: unable to match any input using parser at index '" + std::to_string(state->Index) + "'";
        state->IsError = true;
    } else {
        state->Results = results;
        state->Error = "";
        state->IsError = false;
    }

    return state;
}