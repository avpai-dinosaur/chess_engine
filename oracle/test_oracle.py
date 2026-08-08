import unittest

from oracle import (
    print_board,
    fen_to_board,
    get_pseudo_legal_knight_moves,
    get_pseudo_legal_rook_moves,
    get_pseudo_legal_bishop_moves,
    get_pseudo_legal_queen_moves,
    get_pseudo_legal_king_moves,
    get_pseudo_legal_pawn_moves,
    get_all_pseudo_legal_moves
)


class TestKnightMoves(unittest.TestCase):
    def test_knight_center_of_empty_board(self):
        # Lone white knight on d4 (row 4, col 3), otherwise empty board.
        board = fen_to_board("8/8/8/8/3N4/8/8/8 w - - 0 1")
        moves = get_pseudo_legal_knight_moves(board, 4, 3, "white")
        expected = {
            ((4, 3), (2, 2)), ((4, 3), (2, 4)),
            ((4, 3), (3, 1)), ((4, 3), (3, 5)),
            ((4, 3), (5, 1)), ((4, 3), (5, 5)),
            ((4, 3), (6, 2)), ((4, 3), (6, 4)),
        }
        self.assertEqual(moves, expected)

    def test_knight_in_corner_has_only_two_moves(self):
        board = fen_to_board("N7/8/8/8/8/8/8/8 w - - 0 1")
        moves = get_pseudo_legal_knight_moves(board, 0, 0, "white")
        expected = {((0, 0), (1, 2)), ((0, 0), (2, 1))}
        self.assertEqual(moves, expected)

    def test_knight_blocked_by_own_piece(self):
        # White knight a1, white pawn on the only square within a1's L-reach: b3/c2 etc.
        board = fen_to_board("8/8/8/8/8/1P6/8/N7 w - - 0 1")
        moves = get_pseudo_legal_knight_moves(board, 7, 0, "white")
        # b3 (row 5, col 1) is occupied by own pawn, should be excluded
        self.assertNotIn(((7, 0), (5, 1)), moves)

    def test_knight_can_capture_enemy_piece(self):
        board = fen_to_board("8/8/8/8/8/1p6/8/N7 w - - 0 1")
        moves = get_pseudo_legal_knight_moves(board, 7, 0, "white")
        self.assertIn(((7, 0), (5, 1)), moves)


class TestRookMoves(unittest.TestCase):
    def test_rook_center_of_empty_board(self):
        board = fen_to_board("8/8/8/8/3R4/8/8/8 w - - 0 1")
        moves = get_pseudo_legal_rook_moves(board, 4, 3, "white")
        expected_col = {((4, 3), (i, 3)) for i in range(8) if i != 4}
        expected_row = {((4, 3), (4, j)) for j in range(8) if j != 3}
        self.assertEqual(moves, expected_col | expected_row)

    def test_rook_blocked_by_own_piece(self):
        board = fen_to_board("8/8/8/3P4/3R4/8/8/8 w - - 0 1")
        moves = get_pseudo_legal_rook_moves(board, 4, 3, "white")
        self.assertNotIn(((4, 3), (3, 3)), moves)  # own pawn square excluded
        self.assertNotIn(((4, 3), (2, 3)), moves)  # can't jump over it

    def test_rook_can_capture_but_not_pass_through(self):
        board = fen_to_board("8/8/8/3p4/3R4/8/8/8 w - - 0 1")
        moves = get_pseudo_legal_rook_moves(board, 4, 3, "white")
        self.assertIn(((4, 3), (3, 3)), moves)     # capture allowed
        self.assertNotIn(((4, 3), (2, 3)), moves)  # can't continue past capture


class TestBishopMoves(unittest.TestCase):
    def test_bishop_center_of_empty_board(self):
        board = fen_to_board("8/8/8/8/3B4/8/8/8 w - - 0 1")
        moves = get_pseudo_legal_bishop_moves(board, 4, 3, "white")
        expected = {
            ((4, 3), (5, 4)), ((4, 3), (6, 5)), ((4, 3), (7, 6)),
            ((4, 3), (3, 2)), ((4, 3), (2, 1)), ((4, 3), (1, 0)),
            ((4, 3), (5, 2)), ((4, 3), (6, 1)), ((4, 3), (7, 0)),
            ((4, 3), (3, 4)), ((4, 3), (2, 5)), ((4, 3), (1, 6)), ((4, 3), (0, 7)),
        }
        self.assertEqual(moves, expected)

    def test_bishop_in_corner(self):
        board = fen_to_board("8/8/8/8/8/8/8/B7 w - - 0 1")
        moves = get_pseudo_legal_bishop_moves(board, 7, 0, "white")
        expected = {((7, 0), (6, 1)), ((7, 0), (5, 2)), ((7, 0), (4, 3)), ((7, 0), (3, 4)), ((7, 0), (2, 5)), ((7, 0), (1, 6)), ((7, 0), (0, 7))}
        self.assertEqual(moves, expected)


class TestQueenMoves(unittest.TestCase):
    def test_queen_moves_is_union_of_rook_and_bishop(self):
        board = fen_to_board("8/8/8/8/3Q4/8/8/8 w - - 0 1")
        queen_moves = get_pseudo_legal_queen_moves(board, 4, 3, "white")

        rook_board = fen_to_board("8/8/8/8/3R4/8/8/8 w - - 0 1")
        bishop_board = fen_to_board("8/8/8/8/3B4/8/8/8 w - - 0 1")
        rook_moves = get_pseudo_legal_rook_moves(rook_board, 4, 3, "white")
        bishop_moves = get_pseudo_legal_bishop_moves(bishop_board, 4, 3, "white")

        self.assertEqual(queen_moves, rook_moves | bishop_moves)

    def test_queen_blocked_and_capture(self):
        board = fen_to_board("8/8/8/8/3Qp3/8/8/8 w - - 0 1")
        moves = get_pseudo_legal_queen_moves(board, 4, 3, "white")
        self.assertIn(((4, 3), (4, 4)), moves)      # capture the black pawn
        self.assertNotIn(((4, 3), (4, 5)), moves)   # can't pass through it


class TestKingMoves(unittest.TestCase):
    def test_king_center_of_empty_board(self):
        board = fen_to_board("8/8/8/8/3K4/8/8/8 w - - 0 1")
        moves = get_pseudo_legal_king_moves(board, 4, 3, "white")
        expected = {
            ((4, 3), (3, 2)), ((4, 3), (3, 3)), ((4, 3), (3, 4)),
            ((4, 3), (4, 2)),                   ((4, 3), (4, 4)),
            ((4, 3), (5, 2)), ((4, 3), (5, 3)), ((4, 3), (5, 4)),
        }
        self.assertEqual(moves, expected)
 
    def test_king_in_corner_has_only_three_moves(self):
        board = fen_to_board("8/8/8/8/8/8/8/K7 w - - 0 1")
        moves = get_pseudo_legal_king_moves(board, 7, 0, "white")
        expected = {((7, 0), (6, 0)), ((7, 0), (6, 1)), ((7, 0), (7, 1))}
        self.assertEqual(moves, expected)
 
    def test_king_blocked_by_own_piece(self):
        board = fen_to_board("8/8/8/8/3K4/3P4/8/8 w - - 0 1")
        moves = get_pseudo_legal_king_moves(board, 4, 3, "white")
        self.assertNotIn(((4, 3), (5, 3)), moves)
 
    def test_king_can_capture_enemy_piece(self):
        board = fen_to_board("8/8/8/8/3K4/3p4/8/8 w - - 0 1")
        moves = get_pseudo_legal_king_moves(board, 4, 3, "white")
        self.assertIn(((4, 3), (5, 3)), moves)
 
    def test_king_never_moves_two_squares(self):
        # Sanity check that castling isn't accidentally included.
        board = fen_to_board("8/8/8/8/8/8/8/R3K2R w KQ - 0 1")
        moves = get_pseudo_legal_king_moves(board, 7, 4, "white")
        self.assertNotIn(((7, 4), (7, 2)), moves)
        self.assertNotIn(((7, 4), (7, 6)), moves)
 
 
class TestPawnMoves(unittest.TestCase):
    def test_white_pawn_single_push_from_non_start_rank(self):
        # White pawn on d3 (row 5, col 3), empty board otherwise.
        board = fen_to_board("8/8/8/8/8/3P4/8/8 w - - 0 1")
        moves = get_pseudo_legal_pawn_moves(board, 5, 3, "white")
        self.assertEqual(moves, {((5, 3), (4, 3))})
 
    def test_white_pawn_double_push_from_start_rank(self):
        # White pawn on d2 (row 6, col 3), its start rank.
        board = fen_to_board("8/8/8/8/8/8/3P4/8 w - - 0 1")
        moves = get_pseudo_legal_pawn_moves(board, 6, 3, "white")
        self.assertEqual(moves, {((6, 3), (5, 3)), ((6, 3), (4, 3))})
 
    def test_black_pawn_double_push_from_start_rank(self):
        # Black pawn on d7 (row 1, col 3), its start rank.
        board = fen_to_board("8/3p4/8/8/8/8/8/8 w - - 0 1")
        moves = get_pseudo_legal_pawn_moves(board, 1, 3, "black")
        self.assertEqual(moves, {((1, 3), (2, 3)), ((1, 3), (3, 3))})
 
    def test_pawn_blocked_by_piece_directly_ahead(self):
        # White pawn on d2, black pawn blocking on d3: no moves at all.
        board = fen_to_board("8/8/8/8/8/3p4/3P4/8 w - - 0 1")
        moves = get_pseudo_legal_pawn_moves(board, 6, 3, "white")
        self.assertEqual(moves, set())
 
    def test_pawn_double_push_blocked_by_piece_two_ahead(self):
        # White pawn on d2, black pawn on d4: single push allowed, double blocked.
        board = fen_to_board("8/8/8/8/3p4/8/3P4/8 w - - 0 1")
        moves = get_pseudo_legal_pawn_moves(board, 6, 3, "white")
        self.assertEqual(moves, {((6, 3), (5, 3))})
 
    def test_pawn_cannot_capture_straight_ahead(self):
        # Enemy piece directly ahead blocks the push but isn't a legal capture.
        board = fen_to_board("8/8/8/8/8/3p4/3P4/8 w - - 0 1")
        moves = get_pseudo_legal_pawn_moves(board, 6, 3, "white")
        self.assertNotIn(((6, 3), (5, 3)), moves)
 
    def test_pawn_diagonal_capture(self):
        # White pawn on d3, black pawns on c4 and e4 available to capture.
        board = fen_to_board("8/8/8/8/2p1p3/3P4/8/8 w - - 0 1")
        moves = get_pseudo_legal_pawn_moves(board, 5, 3, "white")
        self.assertEqual(moves, {((5, 3), (4, 2)), ((5, 3), (4, 3)), ((5, 3), (4, 4))})
 
    def test_pawn_cannot_move_diagonally_without_capture(self):
        # No pieces on the diagonals, so only the straight push is legal.
        board = fen_to_board("8/8/8/8/8/3P4/8/8 w - - 0 1")
        moves = get_pseudo_legal_pawn_moves(board, 5, 3, "white")
        self.assertNotIn(((5, 3), (4, 2)), moves)
        self.assertNotIn(((5, 3), (4, 4)), moves)
 
    def test_pawn_cannot_capture_own_piece_diagonally(self):
        board = fen_to_board("8/8/8/8/2P5/3P4/8/8 w - - 0 1")
        moves = get_pseudo_legal_pawn_moves(board, 5, 3, "white")
        self.assertNotIn(((5, 3), (4, 2)), moves)
 
    def test_pawn_on_file_edge_has_only_one_diagonal(self):
        # White pawn on a3, no wraparound to a nonexistent column -1.
        board = fen_to_board("8/8/8/8/1p6/P7/8/8 w - - 0 1")
        moves = get_pseudo_legal_pawn_moves(board, 5, 0, "white")
        self.assertEqual(moves, {((5, 0), (4, 0)), ((5, 0), (4, 1))})


class TestPseudoLegalMoves(unittest.TestCase):
    def test_pseudo_legal_moves(self):
        board = fen_to_board("8/4b3/2p2Q2/2pk4/3P4/B2K4/8/8 b - - 0 1")
        all_moves = get_all_pseudo_legal_moves(board)
        queen_moves = get_pseudo_legal_queen_moves(board, 2, 5, "white")
        bishop_moves = (
            get_pseudo_legal_bishop_moves(board, 5, 0, "white") |
            get_pseudo_legal_bishop_moves(board, 1, 4, "black")
        )
        pawn_moves = (
            get_pseudo_legal_pawn_moves(board, 2, 2, "black") |
            get_pseudo_legal_pawn_moves(board, 3, 2, "black") |
            get_pseudo_legal_pawn_moves(board, 4, 3, "white")
        )
        king_moves = (
            get_pseudo_legal_king_moves(board, 3, 3, "black") |
            get_pseudo_legal_king_moves(board, 5, 3, "white")
        )
        self.assertEqual(all_moves, bishop_moves | pawn_moves | king_moves | queen_moves)


if __name__ == "__main__":
    unittest.main()