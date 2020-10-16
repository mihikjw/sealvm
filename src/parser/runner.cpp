#include "parser/runner.hpp"

using namespace Parser;

State* Runner::Run(BaseParser* parser, const std::string& in) {
    auto state = State{in};
    return parser->Run(&state);
}

State* Runner::SequenceOf(std::vector<std::unique_ptr<BaseParser>>* parsers, const std::string& in) {
    auto results = std::make_shared<std::list<std::shared_ptr<State>>>();
    auto nextState = new State(in);

    for (auto const& parser : *parsers) {
        if (!nextState->IsError) {
            return nextState;
        }
        nextState = parser->Run(nextState);
        results->push_back(std::make_shared<State>(nextState));
    }

    nextState->Results = results;
    return nextState;
}

State* Runner::Choice(std::vector<std::unique_ptr<BaseParser>>* parsers, const std::string& in) {
    auto state = new State(in);

    for (auto const& parser : *parsers) {
        state = parser->Run(state);

        if (!state->IsError) {
            return state;
        }
    }

    state->Error = "Choice: unable to match with any parser at index '" + std::to_string(state->Index) + "'";
    state->IsError = true;
    return state;
}

State* Runner::Many(BaseParser* parser, const std::string& in, bool many1) {
    auto results = std::make_shared<std::list<std::shared_ptr<State>>>();
    auto state = new State(in);
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
    }

    return state;
}