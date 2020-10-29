import asm
import parser


def main():
    # source = "MOV $42, r1"
    source = "MOV [$42 + !loc ], r1"    # - ($05 * ($31 + !var) - $07)
    processor = asm.SealASMProcessor(parser.Runner(), asm.Registers)

    state = processor.process(source)

    if not state.is_error:
        print(state.result)
    else:
        print(state.error)


if __name__ == "__main__":
    main()
