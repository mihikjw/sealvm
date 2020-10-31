import asm
import parser_combinator


def main():
    source = "MOV [$42 + !loc - ($05 * ($31 + !var) - $07)], r1"
    processor = asm.SealASMProcessor(parser_combinator.Runner(), asm.Registers)
    state = processor.process(source)

    if not state.is_error:
        print(state.result)
    else:
        print(state.error)


if __name__ == "__main__":
    main()
