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
        if (nextState->IsError) {
            return nextState;
        }
        nextState = parser->Run(nextState);
        results->push_back(std::make_shared<State>(nextState));
    }

    nextState->Results = results;
    return nextState;
}