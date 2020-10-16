#include "parser/coreParser.hpp"

using namespace Parser;

State* CoreParser::Run(StringParser* parser, const std::string &in) {
    auto state = State{in};
    return parser->String(&state);
}

State* CoreParser::SequenceOf(std::vector<std::unique_ptr<StringParser>>* parsers, const std::string &in) {
    auto results = std::make_shared<std::list<std::shared_ptr<State>>>(); 
    auto nextState = new State(in);

    for (auto const &parser: *parsers) {
        if (nextState->IsError) { 
            return nextState; 
        }
        nextState = parser->String(nextState);
        results->push_back(std::make_shared<State>(nextState));
    }
 
    nextState->Results = results;
    return nextState;
}