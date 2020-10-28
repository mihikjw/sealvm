import parser

# MOV [$42 + (!loc - ($05 * $31))], r1


def main():
    source = "MOV $42, r1"
    runner = parser.Runner()

    state = runner.run(parser.HexParser(), source)

    if not state.is_error:
        print(state.result)
    else:
        print(state.error)


if __name__ == "__main__":
    main()
