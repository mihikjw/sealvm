#ifndef SEALVM_PARSER_STATE_HPP
#define SEALVM_PARSER_STATE_HPP

#include <memory>
#include <string>
#include <vector>

namespace Parser {

// State represents the state of the parser
class State {

    public:
    // State default constructor
    State(const std::string& input = "", const std::string& result = "", const std::shared_ptr<std::vector<std::unique_ptr<State>>>& results = nullptr,
          const std::vector<std::string>& resultMultiple = std::vector<std::string>{}, unsigned short index = 0, const std::string& error = "",
          bool isError = false);

    // State copy constructor
    State(State* in);

    // Map takes a function pointer to map the held data into any other custom type, sets MappedResult to given function result
    State* Map(void*(mapper)(State*));

    // Transform applies the given transformation function to the State and returns it if no error exists on the state
    State* Transform(State*(transformer)(State*));

    // ErrorTransform applies the given transformation function to the State if an error exists on the state
    State* ErrorTransform(State*(transformer)(State*));

    // Input contains the input for the function
    std::string Input;

    // Result contains the output for the single function
    std::string Result;

    // ResultMultiple contains the output for a single parser, which has multiple outputs
    std::vector<std::string> ResultMultiple;

    // Results contains the output for multiple functions chained together (i.e. CoreParser::SequenceOf result)
    std::shared_ptr<std::vector<std::unique_ptr<State>>> Results;

    // Index contains the current index in the input of the parser function
    unsigned short Index;

    // Error contains any error message generated from the last executed function
    std::string Error;

    // IsError is a flag for the error message
    bool IsError;

    // MappedResult is a custom user-defined object, configured with the Map() function
    void* MappedResult;
};

} // namespace Parser

#endif // SEALVM_PARSER_STATE_HPP