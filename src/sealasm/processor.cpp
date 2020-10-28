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

    if (state->IsError) {
        state->IsError = false;
        state->Error = "";
        state = squareBracketExpression(src, state);
        InstructionArg arg(state->Results.get());
        result.Ins.Args["SQUARE_BRACKET_EXPRESSION"] = arg;
    } else {
        InstructionArg arg(state->Result);
        result.Ins.Args["HEX_LITERAL"] = arg;
    }

    state = runner->Run(&comma, src, state);
    state = runner->Run(&whitespaceParserOpt, src, state);

    state = getRegister(src, state);
    InstructionArg arg(state->Result);
    result.Ins.Args["REGISTER"] = arg;

    auto output = runner->Run(&whitespaceParserOpt, src, state); // skip any trailing whitespace
    result.Ins.Type = SealVM::Instructions::MOV_LIT_REG;
    output->MappedResult = static_cast<void*>(&result);

    return output;
}

// SquareBracketState is represents the state's used in the squareBracketExpression state machine, only used in this function
enum SquareBracketState {
    ExpectElement,
    ExpectOperator,
};

Parser::State* Processor::squareBracketExpression(const std::string& src, Parser::State* state) {
    auto openSquareParser = Parser::StringParser("[");
    auto closeSquareParser = Parser::StringParser("]");
    auto optionWhitespace = Parser::WhitespaceParser(true);

    state = runner->Run(&openSquareParser, src, state);
    state = runner->Run(&optionWhitespace, src, state);

    auto expr = std::make_shared<std::vector<std::unique_ptr<Parser::State>>>();
    SquareBracketState s = ExpectElement;

    while (true) {
        switch (s) {
            case ExpectElement: {
                // choice between bracketedExpr, hexLiteral, variable
                // push into expr vector
                s = SquareBracketState::ExpectOperator;
                state = optionWhitespace.Run(state);
                break;
            }
            case ExpectOperator: {
                // get closing square bracket if this is the end
                state = runner->Peek(&closeSquareParser, src, 1, state);
                if (state->Result == "]") {
                    state = runner->Run(&closeSquareParser, src, state);
                    state = runner->Run(&optionWhitespace, src, state);
                    break;
                }

                // get the operator and add to the expression
                state = getOperator(src, state);
                if (state->IsError) {
                    return state;
                }
                expr->push_back(std::make_unique<Parser::State>(state->Result));
                s = SquareBracketState::ExpectElement;
                runner->Run(&optionWhitespace, src, state);
                break;
            }
        }
    }

    state->Results = expr;
    return state;
}

Parser::State* Processor::getOperator(const std::string& src, Parser::State* state) {
    auto parser = Parser::CharParser();
    state = runner->Run(&parser, src, state);

    if (state->IsError) {
        return state;
    }

    Operators op;

    if (state->Result == "+") {
        op = OP_PLUS;
    } else if (state->Result == "-") {
        op = OP_MINUS;
    } else if (state->Result == "*") {
        op = OP_MULTIPLY;
    } else {
        state->Error = "getOperator: Operator Not Found At Index '" + std::to_string(state->Index - 1) + "'";
        state->IsError = true;
        return state;
    }

    state->MappedResult = static_cast<void*>(&op);
    return state;
}
