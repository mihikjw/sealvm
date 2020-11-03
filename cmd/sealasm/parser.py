import asm
import parser_combinator

mov_reg_reg_src_test = "MOV r2, r1"
mov_lit_reg_src_test = "MOV [$42 + !loc - ($05 * ($31 + !var) - $07)], r1"
mov_reg_mem_src_test = "MOV r4, &[!loc + $4200]"
mov_mem_reg_src_test = "MOV &[!loc + $4200], r4"
mov_lit_mem_src_test = "MOV [$42 + !loc - ($05 * ($31 + !var) - $07)], &[!loc + $4200]"
mov_reg_ptr_reg_src_test = "MOV &r2, r1"
mov_lit_off_reg_src_test = "MOV [!loc * $4200], &r7, r2"
all_mov_instructions = (mov_reg_reg_src_test, mov_lit_reg_src_test, mov_reg_mem_src_test, mov_mem_reg_src_test,
                        mov_lit_mem_src_test, mov_reg_ptr_reg_src_test, mov_lit_off_reg_src_test)

add_reg_reg_src_test = "ADD r1, r2"
add_lit_reg_src_test = "ADD [$42 + !loc - ($05 * ($31 + !var) - $07)], r6"
all_add_instructions = (add_reg_reg_src_test, add_lit_reg_src_test)

misc_1_test = "LSF r1, [ !shiftAmount ]"
misc_2_test = "RET"
all_misc_instructions = (misc_1_test, misc_2_test)


def main():
    runner = parser_combinator.Runner()
    parser = asm.InstructionParser(runner)

    for src in all_mov_instructions:
        state = runner.run(parser, src)

        if not state.is_error:
            instruction_entry = state.result["value"]
            print(f"{instruction_entry['instruction']}: passed")
        else:
            print(state.error)

    for src in all_add_instructions:
        state = runner.run(parser, src)

        if not state.is_error:
            instruction_entry = state.result["value"]
            print(f"{instruction_entry['instruction']}: passed")
        else:
            print(f"{src} ERROR: {state.error}")

    for src in all_misc_instructions:
        state = runner.run(parser, src)

        if not state.is_error:
            instruction_entry = state.result["value"]
            print(f"{instruction_entry['instruction']}: passed")
        else:
            print(f"{src} ERROR: {state.error}")


if __name__ == "__main__":
    main()
