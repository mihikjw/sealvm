#include "parser/state.hpp"

using namespace Parser;

State::State(const std::string& input, const std::string& result, std::shared_ptr<std::list<std::shared_ptr<State>>> results, unsigned short index,
             const std::string& error, bool isError) {
    this->Input = input;
    this->Result = result;
    this->Results = results;
    this->Index = index;
    this->Error = error;
    this->IsError = isError;
}

State::State(State* in) {
    this->Input = in->Input;
    this->Result = in->Result;
    this->Results = in->Results;
    this->Index = in->Index;
    this->Error = in->Error;
    this->IsError = in->IsError;
}

State* State::Transform(State*(transformer)(State*)) {
    if (!IsError) {
        return transformer(this);
    }
    return this;
}

State* State::ErrorTransform(State*(transformer)(State*)) {
    if (IsError) {
        return transformer(this);
    }
    return this;
}