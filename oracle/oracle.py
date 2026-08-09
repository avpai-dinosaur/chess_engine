from typing import NamedTuple
from itertools import count


START_BOARD = (
    "         \n"  # 0 - 9
    "         \n"  # 10 - 19
    " rnbqkbnr\n"  # 20 - 29
    " pppppppp\n"  # 30 - 39 
    " ........\n"  # 40 - 49
    " ........\n"  # 50 = 59 
    " ........\n"  # 60 - 69 
    " ........\n"  # 70 - 79 
    " PPPPPPPP\n"  # 80 - 89 
    " RNBQKBNR\n"  # 90 - 99 
    "         \n"  # 100 - 109 
    "         \n"  # 100 - 119
)

NORTH, SOUTH, EAST, WEST = -10, 10, 1, -1
PIECE_DIRECTIONS = {
    "P": {NORTH, NORTH * 2, NORTH + EAST, NORTH + WEST},
    "R": {NORTH, SOUTH, EAST, WEST},
    "N": {NORTH * 2 + WEST, NORTH * 2 + EAST, SOUTH * 2 + WEST, SOUTH * 2 + EAST,
          NORTH + WEST * 2, NORTH + EAST * 2, SOUTH + WEST * 2, SOUTH + EAST * 2},
    "B": {NORTH + EAST, NORTH + WEST, SOUTH + EAST, SOUTH + WEST},
    "Q": {NORTH, SOUTH, EAST, WEST,
          NORTH + EAST, NORTH + WEST, SOUTH + EAST, SOUTH + WEST},
    "K": {NORTH, SOUTH, EAST, WEST,
          NORTH + EAST, NORTH + WEST, SOUTH + EAST, SOUTH + WEST}
}


class Move(NamedTuple):
    start_square: int
    end_square: int
    promotion: str | None = None


class Castle(NamedTuple):
    queen_side: bool = True
    king_side: bool = True


class Position(NamedTuple):
    board: str = START_BOARD
    en_passant_square: int | None = None
    white_castle: Castle = Castle()
    black_castle: Castle = Castle()

    def get_square(self, file_char: str, rank: int) -> int:
        file_idx = ord(file_char) - ord("a") + 1
        rank = rank - 1
        rank = rank + 2
        rank = 11 - rank
        return rank * 10 + file_idx

    def rotate_board(self):
        return Position(
            self.board[::-1].swapcase(), 
            119 - self.en_passant_square if self.en_passant_square != None else None,
            self.black_castle,
            self.white_castle
        )


    def get_pseudo_legal_moves(self):
        for start_square, piece in enumerate(self.board):
            if piece not in "PRNBQK":
                continue
            for direction in PIECE_DIRECTIONS[piece]:
                # Shoot a ray across all squares this piece could move to
                for end_square in count(start_square + direction, direction):
                    target = self.board[end_square]
                    # Can't move to square piece of same color is on
                    if target in "PRNBQK \n":
                        break
                    # Pawn edge cases
                    if piece == "P":
                        # Pawn can only move forward onto empty squares
                        if direction in (NORTH, NORTH * 2) and target != ".":
                            break
                        # Pawn can only move forward twice if its on start rank
                        if direction == NORTH * 2 and (start_square <= 80 or self.board[start_square + NORTH] != "."):
                            break
                        # Pawn can only move diagonal to capture an enemy piece or for en passant
                        if direction in (NORTH + EAST, NORTH + WEST) and target not in "prnbqk" and end_square != self.en_passant_square:
                            break
                        if 0 <= end_square <= 9:
                            for promotion in "NBRQ":
                                yield Move(start_square, end_square, promotion)
                            break
                    yield Move(start_square, end_square)
                    # Stop non-sliding pieces and rays ending in a capture
                    if piece in "PNK" or target in "prnbqk":
                        break
                    # Castling-note we skip checking the piece type; if piece 
                    # is on the corner square and we have castling rights then piece must be a rook 
                    if start_square == 100 and self.board[end_square + WEST] == "K" and self.queen_side_castle:
                        # Small subtlety. We are following the ray from the Rook's perspective but will
                        # encode the move as moving two squares from the King's perspective so it
                        # is easier to tell this is a castling move after the fact
                        yield Move(end_square + WEST, end_square + EAST)
                    if start_square == 119 and self.board[end_square + EAST] == "K" and self.king_side_castle:
                        yield Move(end_square + EAST, end_square + WEST)

    def print(self):
        cell_width = 3
        label_width = 3

        top_border = " " * label_width + (" " + "_" * cell_width) * 8

        lines = [top_border]

        for rank_index, rank in enumerate(self.board.split()):
            rank_label = 8 - rank_index

            blank_line = "   |" + "|".join(" " * cell_width for _ in range(8)) + "|"
            piece_line = f" {rank_label} |"
            bottom_line = "   |" + "|".join("_" * cell_width for _ in range(8)) + "|"

            for square in rank:
                symbol = " " if square == "."  else square
                piece_line += symbol.center(cell_width) + "|"

            lines.append(blank_line)
            lines.append(piece_line)
            lines.append(bottom_line)

        file_labels = " " * (label_width + 1) + " ".join(f" {chr(ord('a') + i)} " for i in range(8))
        lines.append(file_labels)

        print("\n".join(lines))


def parse_fen(fen):
    fen = fen.split(" ")

    ranks = fen[0].split("/")
    buffer_rank = " " * 9 + "\n"
    board = ""
    board += buffer_rank * 2
    for rank in ranks:
        board += " "
        for char in rank:
            if char.isdigit():
                board += "." * int(char)
            else:
                board += char
        board += " "
    board += buffer_rank * 2

    white_castle = Castle("Q" in fen[2], "K" in fen[2])
    black_castle = Castle("q" in fen[2], "k" in fen[2])

    if fen[3] == "-":
        en_passant_square = None
    else:
        ep_file_char, ep_rank_char = fen[3]
        rank = int(ep_rank_char) - 1
        file = ord(ep_file_char) - ord("a")
        row = rank + 2
        col = file + 1
        en_passant_square = row * 10 + col

    return Position(board, en_passant_square, white_castle, black_castle)
        

if __name__ == "__main__":
    parse_fen("rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2").print()