from hypothesis import given, strategies as st

import oracle as eng


@st.composite
def fen_string(draw):
    # 1. Pick the pieces to put on the board
    pieces = "ppppppppPPPPPPPPrnbqbnrRNBQBNR"
    shuffled = draw(st.permutations(list(pieces)))
    n = draw(st.integers(0, len(pieces)))
    piece_list = shuffled[:n]
    piece_list.append("K")
    piece_list.append("k")

    # 2. Randomly pick the ranks
    ranks = [[] for _ in range(8)]
    for piece in piece_list:
        if piece.lower() == "p":
            rank_min = 1
            rank_max = 6
        else:
            rank_min = 0
            rank_max = 7
        rank = draw(st.integers(rank_min, rank_max).filter(lambda n: len(ranks[n]) < 8))
        ranks[rank].append(piece)

    # 3. Randomly choose num spaces in a rank
    fen_ranks = []
    for rank in ranks:
        fen_rank = []
        file = 0
        while file < 8:
            if len(rank) == 0:
                fen_rank.append(f"{8 - file}")
                break
            if 8 - file > len(rank) and draw(st.booleans()):
                if len(fen_rank) > 0 and fen_rank[-1].isnumeric():
                    prev_space = int(fen_rank.pop())
                    fen_rank.append(f"{1 + prev_space}")
                else:
                    fen_rank.append(f"{1}")
            else:
                fen_rank.append(rank.pop())
            file += 1
        fen_ranks.append("".join(fen_rank))
    
    return "/".join(fen_ranks)


@given(fen_string())
def test_hypothesis_pseudolegal_moves(fen):
    position = eng.parse_fen(fen)
    for mv in position.get_pseudo_legal_moves():
        print(mv)


if __name__ == "__main__":
    test_hypothesis_pseudolegal_moves()