#ifndef SEALVM_PARSER_STATE_HPP
#define SEALVM_PARSER_STATE_HPP

#include <string>
#include <list>
#include <memory>

namespace Parser {

// State represents the state of the parser
class State {
    public:
    State(const std::string &input = "", const std::string &result = "", std::shared_ptr<std::list<std::shared_ptr<State>>> results = nullptr, 
                                                                unsigned short index = 0, const std::string &error = "", bool isError = false){
        this->Input = input;
        this->Result = result;
        this->Results = results;
        this->Index = index;
        this->Error = error;
        this->IsError = isError;
    }
    State(State* in){
        this->Input = in->Input;
        this->Result = in->Result;
        this->Results = in->Results;
        this->Index = in->Index;
        this->Error = in->Error;
        this->IsError = in->IsError;
    }

    // Input contains the input for the function
    std::string Input;

    // Result contains the output for the single function
    std::string Result;

    // Results contains the output for multiple functions chained together (i.e. CoreParser::SequenceOf result)
    std::shared_ptr<std::list<std::shared_ptr<State>>> Results;

    // Index contains the current index in the input of the parser function
    unsigned short Index;

    // Error contains any error message generated from the last executed function
    std::string Error;

    // IsError is a flag for the error message
    bool IsError;
};

}

#endif  // SEALVM_PARSER_STATE_HPP