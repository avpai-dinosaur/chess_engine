from hypothesis import given, strategies as st

import oracle as eng


@st.composite
def fen_string(draw):
    # Pick the pieces to put on the board
    pieces = "ppppppppPPPPPPPPrnbqbnrRNBQBNR"
    n = draw(st.integers(0, len(pieces)))
    piece_list = draw(st.permutations(list(pieces)))[:n]
    piece_list.append("K")
    piece_list.append("k")
    pawns = [p for p in piece_list if p in ("p", "P")]
    rest = [p for p in piece_list if p not in ("p", "P")]

    # Randomly pick the squares the pieces go on
    pawn_squares = draw(st.permutations(list(range(8, 56))))[:len(pawns)]
    rest_squares = draw(st.permutations([i for i in range(64) if i not in pawn_squares]))[:len(rest)]
    board = ["." for _ in range(64)]
    for i, piece in zip(pawn_squares, pawns):
        board[i] = piece
    for i, piece in zip(rest_squares, rest):
        board[i] = piece

    # Construct the rank strings
    fen_ranks = []
    for i in range(8):
        fen_rank = []
        start_idx = i * 8
        end_idx = start_idx + 8
        for piece in board[start_idx:end_idx]:
            if piece == ".":
                if len(fen_rank) > 0 and fen_rank[-1].isnumeric():
                    prev_space = int(fen_rank.pop())
                    fen_rank.append(f"{prev_space + 1}")
                else:
                    fen_rank.append("1")
            else:
                fen_rank.append(piece)
        fen_ranks.append("".join(fen_rank))
    piece_positions = "/".join(fen_ranks)

    # Choose the active color
    active_color = "w" if draw(st.booleans()) else "b"

    # Figure out if we have castling rights.
    # Simplifying assumption that if rook and king are on starting squares we do
    # which is not technically correct.
    castling_rights = ""
    if board[63] == "R" and board[60] == "K":
        castling_rights += "K"
    if board[56] == "R" and board[60] == "K":
        castling_rights += "Q"
    if board[7] == "r" and board[4] == "k":
        castling_rights += "k"
    if board[0] == "r" and board[4] == "k":
        castling_rights += "q"
    castling_rights = "-" if castling_rights == "" else castling_rights

    # Find all pawns that have potentially been pushed up twice 
    en_passant_squares = []
    # black pawns
    for i in range(24, 24 + 8):
        if board[i] == "p" and board[i - 8] == "." and board[i - 16] == ".":
            en_passant_squares.append(i - 8)
    # white pawns
    for i in range(32, 32 + 8):
        if board[i] == "P" and board[i + 8] == "." and board[i + 16] == ".":
            en_passant_squares.append(i + 8)

    # Choose an en passant square
    if len(en_passant_squares) > 0:
        idx = draw(st.integers(0, len(en_passant_squares) - 1))
        en_passant_square_number = en_passant_squares[idx]
        rank = en_passant_square_number // 8
        file = en_passant_square_number % 8 
        file_char =  chr(ord("a") + file)
        rank_char = str(8 - rank)
        en_passant_square = f"{file_char}{rank_char}"
    else:
        en_passant_square = "-"

    return " ".join([piece_positions, active_color, castling_rights, en_passant_square])


@given(fen_string())
def test_hypothesis_pseudolegal_moves(fen):
    position = eng.parse_fen(fen)
    position.print()
    print(fen)
    for mv in position.get_pseudo_legal_moves():
        pass


if __name__ == "__main__":
    test_hypothesis_pseudolegal_moves()