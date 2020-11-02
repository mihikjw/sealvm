import asm
import parser_combinator

mov_reg_reg_src_test = "MOV r2, r1"
mov_lit_reg_src_test = "MOV [$42 + !loc - ($05 * ($31 + !var) - $07)], r1"


def main():
    source = mov_reg_reg_src_test
    runner = parser_combinator.Runner()
    parser = asm.MovRegRegParser(runner, asm.Registers)
    state = runner.run(parser, source)

    if not state.is_error:
        print(state.result)
    else:
        print(state.error)


if __name__ == "__main__":
    main()
