def create_start_board():
    board = [["" for _ in range(8)] for _ in range(8)]
    board[7][0] = "white_rook"
    board[7][1] = "white_knight"
    board[7][2] = "white_bishop"
    board[7][3] = "white_queen"
    board[7][4] = "white_king"
    board[7][5] = "white_bishop"
    board[7][6] = "white_knight"
    board[7][7] = "white_rook"

    board[6][0] = "white_pawn"
    board[6][1] = "white_pawn"
    board[6][2] = "white_pawn"
    board[6][3] = "white_pawn"
    board[6][4] = "white_pawn"
    board[6][5] = "white_pawn"
    board[6][6] = "white_pawn"
    board[6][7] = "white_pawn"

    board[1][0] = "black_pawn"
    board[1][1] = "black_pawn"
    board[1][2] = "black_pawn"
    board[1][3] = "black_pawn"
    board[1][4] = "black_pawn"
    board[1][5] = "black_pawn"
    board[1][6] = "black_pawn"
    board[1][7] = "black_pawn"

    board[0][0] = "black_rook"
    board[0][1] = "black_knight"
    board[0][2] = "black_bishop"
    board[0][3] = "black_queen"
    board[0][4] = "black_king"
    board[0][5] = "black_bishop"
    board[0][6] = "black_knight"
    board[0][7] = "black_rook"

    return board

def fen_to_board(fen):
    piece_map = {
        "p": "black_pawn", "P": "white_pawn",
        "n": "black_knight", "N": "white_knight",
        "b": "black_bishop", "B": "white_bishop",
        "r": "black_rook", "R": "white_rook",
        "q": "black_queen", "Q": "white_queen",
        "k": "black_king", "K": "white_king"
    }
    board_field = fen.split(" ")[0]
    ranks = board_field.split("/")
    board = [["" for _ in range(8)] for _ in range(8)]
    for row, rank in enumerate(ranks):
        col = 0
        for char in rank:
            if char.isdigit():
                col += int(char)
            else:
                board[row][col] = piece_map[char]
                col += 1
    return board
        
def print_piece(piece):
    if piece == "":
        return " "
    
    color, type = piece.split("_")

    if type == "rook":
        result = "r"
    elif type == "knight":
        result = "n"
    elif type == "bishop":
        result = "b"
    elif type == "queen":
        result = "q"
    elif type == "king":
        result = "k"
    elif type == "pawn":
        result = "p"

    if color == "white":
        return result.upper()
    return result


def print_board(board):
    # Assumes board[0] = rank 8 (top row printed), board[7] = rank 1 (bottom).
    # Each entry is a piece string like "white_pawn" or None for empty.

    cell_width = 3
    label_width = 3

    top_border = " " * label_width + (" " + "_" * cell_width) * 8

    lines = [top_border]

    for rank_index, rank in enumerate(board):
        rank_label = 8 - rank_index

        blank_line = "   |" + "|".join(" " * cell_width for _ in range(8)) + "|"
        piece_line = f"{rank_label:>2} |"
        bottom_line = "   |" + "|".join("_" * cell_width for _ in range(8)) + "|"

        for square in rank:
            symbol = print_piece(square)
            piece_line += symbol.center(cell_width) + "|"

        lines.append(blank_line)
        lines.append(piece_line)
        lines.append(bottom_line)

    file_labels = " " * (label_width + 1) + " ".join(f" {chr(ord('a') + i)} " for i in range(8))
    lines.append(file_labels)

    print("\n".join(lines))


def probe_ray_square(board, row, col, color):
    piece = board[row][col]
    if piece == "":
        return (row, col), True
    else:
        piece_color, _ = piece.split("_")
        if piece_color == color:
            return None, False
        else:
            return (row, col), False


def cast_ray(board, row_range, col_range, color):
    moves = set()
    ray = zip(row_range, col_range)
    start_square = ray.__next__()
    for i, j in ray:
        square, cont = probe_ray_square(board, i, j, color)
        if square is not None:
            moves.add((start_square, square))
        if not cont:
            break
    return moves


def get_pseudo_legal_queen_moves(board, row, col, color):
    if [color, "queen"] != board[row][col].split("_"):
        raise ValueError(f"No {color} queen at ({row}, {col})")
    moves = set()
    moves.update(get_pseudo_legal_rank_and_file_moves(board, row, col, color)) 
    moves.update(get_pseudo_legal_diagonal_moves(board, row, col, color)) 
    return moves


def get_pseudo_legal_bishop_moves(board, row, col, color):
    if [color, "bishop"] != board[row][col].split("_"):
        raise ValueError(f"No {color} bishop at ({row}, {col})")
    return get_pseudo_legal_diagonal_moves(board, row, col, color)
    

def get_pseudo_legal_diagonal_moves(board, row, col, color):
    moves = set()
    moves.update(cast_ray(board, range(row, 8), range(col, 8), color))
    moves.update(cast_ray(board, range(row, -1, -1), range(col, 8), color))
    moves.update(cast_ray(board, range(row, 8), range(col, -1, -1), color))
    moves.update(cast_ray(board, range(row, -1, -1), range(col, -1, -1), color))
    return moves


def get_pseudo_legal_rook_moves(board, row, col, color):
    if [color, "rook"] != board[row][col].split("_"):
        raise ValueError(f"No {color} rook at ({row}, {col})")
    return get_pseudo_legal_rank_and_file_moves(board, row, col, color)


def get_pseudo_legal_rank_and_file_moves(board, row, col, color):
    moves = set()
    moves.update(cast_ray(board, range(row, 8), [col] * (8 - row), color))
    moves.update(cast_ray(board, range(row, -1, -1), [col] * (row + 1), color))
    moves.update(cast_ray(board, [row] * (col + 1), range(col, -1, -1), color))
    moves.update(cast_ray(board, [row] * (8 - col), range(col, 8), color))
    return moves


def get_pseudo_legal_knight_moves(board, row, col, color):
    if [color, "knight"] != board[row][col].split("_"):
        raise ValueError(f"No {color} knight at ({row}, {col})")
    offsets = [
        (2, -1), (2, 1), (1, -2), (1, 2),
        (-1, -2), (-1, 2), (-2, -1), (-2, 1)
    ]
    start_square = (row, col)
    moves = set()
    for row_offset, col_offset in offsets:
        i = row + row_offset
        j = col + col_offset
        if -1 < i < 8 and -1 < j < 8:
            probed_square, _ = probe_ray_square(board, i, j, color)
            if probed_square != None:
                moves.add((start_square, probed_square))
    return moves


def get_pseudo_legal_king_moves(board, row, col, color):
    if [color, "king"] != board[row][col].split("_"):
        raise ValueError(f"No {color} king at ({row}, {col})")
    offsets = [
        (1, -1), (1, 0), (1, 1), 
        (0, -1), (0, 1),
        (-1, -1), (-1, 0), (-1, 1)
    ]
    start_square = (row, col)
    moves = set()
    for row_offset, col_offset in offsets:
        i = row + row_offset
        j = col + col_offset
        if -1 < i < 8 and -1 < j < 8:
            probed_square, _ = probe_ray_square(board, i, j, color)
            if probed_square != None:
                moves.add((start_square, probed_square))
    return moves


def get_pseudo_legal_pawn_moves(board, row, col, color):
    if [color, "pawn"] != board[row][col].split("_"):
        raise ValueError(f"No {color} pawn at ({row}, {col})")
    start_square = (row, col)
    moves = set()

    double_advance_row = -1
    double_advance_col = -1

    if color == "black":
        if row == 1:
            double_advance_row, double_advance_col = (row + 2, col)
        advance_row, advance_col = (row + 1, col)
        capture_right_row, capture_right_col = (row + 1, col + 1)
        capture_left_row, capture_left_col = (row + 1, col - 1)
    else:
        if row == 6:
            double_advance_row, double_advance_col = (row - 2, col)
        advance_row, advance_col = (row - 1, col)
        capture_right_row, capture_right_col = (row - 1, col + 1)
        capture_left_row, capture_left_col = (row - 1, col - 1)

    if -1 < advance_row < 8 and -1 < advance_col < 8 and board[advance_row][advance_col] == "":
        moves.add((start_square, (advance_row, advance_col)))
        if -1 < double_advance_row < 8 and -1 < double_advance_col < 8 and board[double_advance_row][double_advance_col] == "":
            moves.add((start_square, (double_advance_row, double_advance_col)))

    if -1 < capture_left_row < 8 and -1 < capture_left_col < 8:
        piece = board[capture_left_row][capture_left_col]
        if piece != "":
            piece_color, _ = piece.split("_")
            if piece_color != color:
                moves.add((start_square, (capture_left_row, capture_left_col)))

    if -1 < capture_right_row < 8 and -1 < capture_right_col < 8:
        piece = board[capture_right_row][capture_right_col]
        if piece != "":
            piece_color, _ = piece.split("_")
            if piece_color != color:
                moves.add((start_square, (capture_right_row, capture_right_col)))

    # TODO: Check en-passant square

    return moves


def get_pseudo_legal_moves(board, row, col):
    piece = board[row][col]
    if piece == "":
        return set()
    color, type = piece.split("_")
    if type == "rook":
        return get_pseudo_legal_rook_moves(board, row, col, color)
    if type == "knight":
        return get_pseudo_legal_knight_moves(board, row, col, color)
    if type == "bishop":
        return get_pseudo_legal_bishop_moves(board, row, col, color)
    if type == "queen":
        return get_pseudo_legal_queen_moves(board, row, col, color)
    if type == "king":
        return get_pseudo_legal_king_moves(board, row, col, color)
    if type == "pawn":
        return get_pseudo_legal_pawn_moves(board, row, col, color)
    return set()


# def get_moves(board, square_of_piece):
#     row, col = square_of_piece
#     piece = board[row][col]
#     color, type = piece.split("_")

#     if type == "rook":
#         return get_rook_moves(board, row, col, color)
#     elif type == "knight":
#         return get_knight_moves(board, row, col, color)
#     elif type == "bishop":
#         return get_bishop_moves(board, row, col, color)
#     elif type == "queen":
#         return get_queen_moves(board, row, col, color)
#     elif type == "king":
#         return get_king_moves(board, row, col, color)
#     elif type == "pawn":
#         return get_pawn_moves(board, row, col, color)

#     return None


def get_all_pseudo_legal_moves(board):
    moves = set()
    for row in range(0, 8):
        for col in range(0, 8):
            moves.update(get_pseudo_legal_moves(board, row, col))
    return moves


if __name__ == "__main__":
    print_board(fen_to_board("rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2"))