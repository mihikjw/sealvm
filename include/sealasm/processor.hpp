#ifndef SEALVM_PROCESSOR_HPP
#define SEALVM_PROCESSOR_HPP

#include <iostream>
#include <string>

#include "parser/parser.hpp"
#include "sealvm/sealvm.hpp"

#include "sealasm/types.hpp"

namespace SealASM {

class Processor {
    public:
    Processor(Parser::Runner* runner);
    ~Processor() = default;

    // Process is a placeholder function for processing a given string of ASM
    void Process(const std::string& input);

    private:
    // runner is used to run the parser combinators
    Parser::Runner* runner;

    // upperOrLowerStr is used to extract an uppercase or lowercase string
    Parser::State* upperOrLowerStr(std::string locate, const std::string& src, Parser::State* state = nullptr);

    // getRegister is used to extract a register name
    Parser::State* getRegister(const std::string& src, Parser::State* state = nullptr);

    // movLitToReg currently works for simple instructions, however we need to support expressions such as MOV [$42 + (!loc - ($05 * $31))], r1 and
    //  not just read a hex value. Need to change this function into a finite state machine which allows this to be processed
    Parser::State* movLitToReg(const std::string& src);
};

} // namespace SealASM

#endif // SEALVM_PROCESSOR_HPP