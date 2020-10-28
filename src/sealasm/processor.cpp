#include "sealasm/processor.hpp"

using namespace SealASM;

Processor::Processor(Parser::Runner* runner) { this->runner = runner; }

void Processor::Process(const std::string& input) {
    /*
    this function is entierly placeholder at the moment, and just contains whatever
        functionality I'm currently working on/testing. The terminal output will be
        removed and again is only placeholder.
    */
    auto state = movLitToReg(input);

    if (!state->IsError) {
        std::cout << "No Error\n";

        auto result = static_cast<ASMStateResult*>(state->MappedResult);
        int i = 1;
    } else {
        std::cerr << "Error: " << state->Error << std::endl;
    }
}

Parser::State* Processor::upperOrLowerStr(std::string locate, const std::string& src, Parser::State* state) {
    std::transform(locate.begin(), locate.end(), locate.begin(), ::toupper);
    auto uppercaseParser = Parser::StringParser(locate);
    std::transform(locate.begin(), locate.end(), locate.begin(), ::tolower);
    auto lowercaseParser = Parser::StringParser(locate);
    auto parsers = std::vector<Parser::BaseParser*>{&uppercaseParser, &lowercaseParser};
    return runner->Choice(&parsers, src, state);
}

Parser::State* Processor::getRegister(const std::string& src, Parser::State* state) {
    for (auto const& reg : SealVM::RegisterStrings) {
        state = upperOrLowerStr(reg, src, state);

        if (!state->IsError) {
            break;
        }
    }

    if (!state->IsError) {
        return state;
    }

    state->Error = "Processor: unable to match a register";
    return state;
}

Parser::State* Processor::movLitToReg(const std::string& src) {
    auto result = ASMStateResult{OperationType::INSTRUCTION, Instruction{SealVM::Instructions::MOV_LIT_REG}};
    auto whitespaceParserForce = Parser::WhitespaceParser();
    auto whitespaceParserOpt = Parser::WhitespaceParser(true);
    auto comma = Parser::StringParser(",");

    auto state = upperOrLowerStr("mov", src);
    state = runner->Run(&whitespaceParserForce, src, state);

    auto hexParser = Parser::HexParser();
    state = runner->Run(&hexParser, src, state);
    result.Ins.Args["HEX_LITERAL"] = state->Result;

    state = runner->Run(&comma, src, state);
    state = runner->Run(&whitespaceParserOpt, src, state);

    state = getRegister(src, state);
    result.Ins.Args["REGISTER"] = state->Result;

    auto output = runner->Run(&whitespaceParserOpt, src, state); // skip any trailing whitespace
    result.Ins.Type = SealVM::Instructions::MOV_LIT_REG;
    output->MappedResult = static_cast<void*>(&result);

    return output;
}