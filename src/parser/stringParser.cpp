#include "parser/stringParser.hpp"

using namespace Parser;

StringParser::StringParser(const std::string &locate) {
    if (locate.empty()){
        throw std::invalid_argument("invalid 'locate' arg");
    }

    this->locate = locate; 
} 

State* StringParser::Run(State* state) {
    if (state->IsError) { 
        return state; 
    }

    std::size_t startPos = state->Input.find(locate, state->Index);
    
    if (startPos != std::string::npos) {
        std::size_t endPos = state->Input.find(locate[locate.size() - 1], startPos);
        
        if (endPos != std::string::npos) {
            state->Result = state->Input.substr(startPos, endPos + 1);
            state->Index = endPos;
            state->Error = "";
            state->IsError = false;
            return state;
        }
    }

    return setErrorState(state, "StringParser: tried to match '" + locate + "', but got '" + state->Input + "'");
}