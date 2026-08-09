import unittest

import oracle as eng


def moves_from(position, from_square) -> set:
    return {m for m in position.get_pseudo_legal_moves() if m.start_square == from_square}


class TestKnightMoves(unittest.TestCase):
    def test_knight_center_of_empty_board(self):
        # Lone white knight on d4 (row 4, col 3), otherwise empty board.
        position = eng.parse_fen("8/8/8/8/3N4/8/8/8 w - - 0 1")
        moves = set()
        for m in position.get_pseudo_legal_moves():
            moves.add(m)
        d4 = position.get_square("d", 4)
        expected = {
            eng.Move(d4, d4 + eng.NORTH * 2 + eng.EAST), eng.Move(d4, d4 + eng.NORTH * 2 + eng.WEST),
            eng.Move(d4, d4 + eng.NORTH + eng.EAST * 2), eng.Move(d4, d4 + eng.NORTH + eng.WEST * 2),
            eng.Move(d4, d4 + eng.SOUTH + eng.EAST * 2), eng.Move(d4, d4 + eng.SOUTH + eng.WEST * 2),
            eng.Move(d4, d4 + eng.SOUTH * 2 + eng.EAST), eng.Move(d4, d4 + eng.SOUTH * 2 + eng.WEST),
        }
        self.assertEqual(moves, expected)

    def test_knight_in_corner_has_only_two_moves(self):
        position = eng.parse_fen("N7/8/8/8/8/8/8/8 w - - 0 1")
        a8 = position.get_square("a", 8)
        moves = moves_from(position, a8)
        expected = {eng.Move(a8, position.get_square("b", 6)), eng.Move(a8, position.get_square("c", 7))}
        self.assertEqual(moves, expected)

    def test_knight_blocked_by_own_piece(self):
        # White knight a1, white pawn on the only square within a1's L-reach: b3.
        position = eng.parse_fen("8/8/8/8/8/1P6/8/N7 w - - 0 1")
        a1 = position.get_square("a", 1)
        moves = moves_from(position, a1)
        self.assertNotIn(eng.Move(a1, position.get_square("b", 3)), moves)

    def test_knight_can_capture_enemy_piece(self):
        position = eng.parse_fen("8/8/8/8/8/1p6/8/N7 w - - 0 1")
        a1 = position.get_square("a", 1)
        moves = moves_from(position, a1)
        self.assertIn(eng.Move(a1, position.get_square("b", 3)), moves)


class TestRookMoves(unittest.TestCase):
    def test_rook_center_of_empty_board(self):
        position = eng.parse_fen("8/8/8/8/3R4/8/8/8 w - - 0 1")
        d4 = position.get_square("d", 4)
        moves = moves_from(position, d4)
        expected_file = {eng.Move(d4, position.get_square("d", r)) for r in range(1, 9) if r != 4}
        expected_rank = {eng.Move(d4, position.get_square(f, 4)) for f in "abcdefgh" if f != "d"}
        self.assertEqual(moves, expected_file | expected_rank)

    def test_rook_blocked_by_own_piece(self):
        position = eng.parse_fen("8/8/8/3P4/3R4/8/8/8 w - - 0 1")
        d4 = position.get_square("d", 4)
        moves = moves_from(position, d4)
        self.assertNotIn(eng.Move(d4, position.get_square("d", 5)), moves)  # own pawn square excluded
        self.assertNotIn(eng.Move(d4, position.get_square("d", 6)), moves)  # can't jump over it

    def test_rook_can_capture_but_not_pass_through(self):
        position = eng.parse_fen("8/8/8/3p4/3R4/8/8/8 w - - 0 1")
        d4 = position.get_square("d", 4)
        moves = moves_from(position, d4)
        self.assertIn(eng.Move(d4, position.get_square("d", 5)), moves)     # capture allowed
        self.assertNotIn(eng.Move(d4, position.get_square("d", 6)), moves)  # can't continue past capture


class TestBishopMoves(unittest.TestCase):
    def test_bishop_center_of_empty_board(self):
        position = eng.parse_fen("8/8/8/8/3B4/8/8/8 w - - 0 1")
        d4 = position.get_square("d", 4)
        moves = moves_from(position, d4)
        expected = {
            eng.Move(d4, position.get_square("e", 5)), eng.Move(d4, position.get_square("f", 6)), eng.Move(d4, position.get_square("g", 7)), eng.Move(d4, position.get_square("h", 8)),
            eng.Move(d4, position.get_square("c", 3)), eng.Move(d4, position.get_square("b", 2)), eng.Move(d4, position.get_square("a", 1)),
            eng.Move(d4, position.get_square("c", 5)), eng.Move(d4, position.get_square("b", 6)), eng.Move(d4, position.get_square("a", 7)),
            eng.Move(d4, position.get_square("e", 3)), eng.Move(d4, position.get_square("f", 2)), eng.Move(d4, position.get_square("g", 1)),
        }
        self.assertEqual(moves, expected)

    def test_bishop_in_corner(self):
        position = eng.parse_fen("8/8/8/8/8/8/8/B7 w - - 0 1")
        a1 = position.get_square("a", 1)
        moves = moves_from(position, a1)
        expected = {eng.Move(a1, position.get_square(f, r)) for f, r in zip("bcdefgh", range(2, 9))}
        self.assertEqual(moves, expected)


class TestQueenMoves(unittest.TestCase):
    def test_queen_moves_is_union_of_rook_and_bishop(self):
        queen_position = eng.parse_fen("8/8/8/8/3Q4/8/8/8 w - - 0 1")
        d4 = queen_position.get_square("d", 4)
        queen_moves = moves_from(queen_position, d4)

        rook_position = eng.parse_fen("8/8/8/8/3R4/8/8/8 w - - 0 1")
        bishop_position = eng.parse_fen("8/8/8/8/3B4/8/8/8 w - - 0 1")
        rook_moves = moves_from(rook_position, d4)
        bishop_moves = moves_from(bishop_position, d4)

        self.assertEqual(queen_moves, rook_moves | bishop_moves)

    def test_queen_blocked_and_capture(self):
        position = eng.parse_fen("8/8/8/8/3Qp3/8/8/8 w - - 0 1")
        d4 = position.get_square("d", 4)
        moves = moves_from(position, d4)
        self.assertIn(eng.Move(d4, position.get_square("e", 4)), moves)     # capture the black pawn
        self.assertNotIn(eng.Move(d4, position.get_square("f", 4)), moves)  # can't pass through it


class TestKingMoves(unittest.TestCase):
    def test_king_center_of_empty_board(self):
        position = eng.parse_fen("8/8/8/8/3K4/8/8/8 w - - 0 1")
        d4 = position.get_square("d", 4)
        moves = moves_from(position, d4)
        expected = {
            eng.Move(d4, d4 + eng.NORTH + eng.WEST), eng.Move(d4, d4 + eng.NORTH), eng.Move(d4, d4 + eng.NORTH + eng.EAST),
            eng.Move(d4, d4 + eng.WEST),                                          eng.Move(d4, d4 + eng.EAST),
            eng.Move(d4, d4 + eng.SOUTH + eng.WEST), eng.Move(d4, d4 + eng.SOUTH), eng.Move(d4, d4 + eng.SOUTH + eng.EAST),
        }
        self.assertEqual(moves, expected)

    def test_king_in_corner_has_only_three_moves(self):
        position = eng.parse_fen("8/8/8/8/8/8/8/K7 w - - 0 1")
        a1 = position.get_square("a", 1)
        moves = moves_from(position, a1)
        expected = {
            eng.Move(a1, position.get_square("a", 2)), eng.Move(a1, position.get_square("b", 2)), eng.Move(a1, position.get_square("b", 1)),
        }
        self.assertEqual(moves, expected)

    def test_king_blocked_by_own_piece(self):
        position = eng.parse_fen("8/8/8/8/3K4/3P4/8/8 w - - 0 1")
        d4 = position.get_square("d", 4)
        moves = moves_from(position, d4)
        self.assertNotIn(eng.Move(d4, position.get_square("d", 3)), moves)

    def test_king_can_capture_enemy_piece(self):
        position = eng.parse_fen("8/8/8/8/3K4/3p4/8/8 w - - 0 1")
        d4 = position.get_square("d", 4)
        moves = moves_from(position, d4)
        self.assertIn(eng.Move(d4, position.get_square("d", 3)), moves)

    def test_king_never_moves_two_squares(self):
        # Sanity check that castling isn't accidentally included here.
        position = eng.parse_fen("8/8/8/8/8/8/8/R3K2R w KQ - 0 1")
        e1 = position.get_square("e", 1)
        moves = moves_from(position, e1)
        self.assertNotIn(eng.Move(e1, position.get_square("c", 1)), moves)
        self.assertNotIn(eng.Move(e1, position.get_square("g", 1)), moves)


class TestPawnMoves(unittest.TestCase):
    def test_white_pawn_single_push_from_non_start_rank(self):
        position = eng.parse_fen("8/8/8/8/8/3P4/8/8 w - - 0 1")
        d3 = position.get_square("d", 3)
        moves = moves_from(position, d3)
        self.assertEqual(moves, {eng.Move(d3, position.get_square("d", 4))})

    def test_white_pawn_double_push_from_start_rank(self):
        position = eng.parse_fen("8/8/8/8/8/8/3P4/8 w - - 0 1")
        d2 = position.get_square("d", 2)
        moves = moves_from(position, d2)
        self.assertEqual(moves, {eng.Move(d2, position.get_square("d", 3)), eng.Move(d2, position.get_square("d", 4))})

    def test_black_pawn_double_push_from_start_rank(self):
        position = eng.parse_fen("8/3p4/8/8/8/8/8/8 b - - 0 1")
        position = position.rotate_board()
        e2 = position.get_square("e", 2)
        moves = moves_from(position, e2)
        self.assertEqual(moves, {eng.Move(e2, position.get_square("e", 3)), eng.Move(e2, position.get_square("e", 4))})

    def test_pawn_blocked_by_piece_directly_ahead(self):
        position = eng.parse_fen("8/8/8/8/8/3p4/3P4/8 w - - 0 1")
        d2 = position.get_square("d", 2)
        moves = moves_from(position, d2)
        self.assertEqual(moves, set())

    def test_pawn_double_push_blocked_by_piece_two_ahead(self):
        position = eng.parse_fen("8/8/8/8/3p4/8/3P4/8 w - - 0 1")
        d2 = position.get_square("d", 2)
        moves = moves_from(position, d2)
        self.assertEqual(moves, {eng.Move(d2, position.get_square("d", 3))})

    def test_pawn_cannot_capture_straight_ahead(self):
        position = eng.parse_fen("8/8/8/8/8/3p4/3P4/8 w - - 0 1")
        d2 = position.get_square("d", 2)
        moves = moves_from(position, d2)
        self.assertNotIn(eng.Move(d2, position.get_square("d", 3)), moves)

    def test_pawn_diagonal_capture(self):
        position = eng.parse_fen("8/8/8/8/2p1p3/3P4/8/8 w - - 0 1")
        d3 = position.get_square("d", 3)
        moves = moves_from(position, d3)
        self.assertEqual(moves, {
            eng.Move(d3, position.get_square("c", 4)), eng.Move(d3, position.get_square("d", 4)), eng.Move(d3, position.get_square("e", 4)),
        })

    def test_pawn_cannot_move_diagonally_without_capture(self):
        position = eng.parse_fen("8/8/8/8/8/3P4/8/8 w - - 0 1")
        d3 = position.get_square("d", 3)
        moves = moves_from(position, d3)
        self.assertNotIn(eng.Move(d3, position.get_square("c", 4)), moves)
        self.assertNotIn(eng.Move(d3, position.get_square("e", 4)), moves)

    def test_pawn_cannot_capture_own_piece_diagonally(self):
        position = eng.parse_fen("8/8/8/8/2P5/3P4/8/8 w - - 0 1")
        d3 = position.get_square("d", 3)
        moves = moves_from(position, d3)
        self.assertNotIn(eng.Move(d3, position.get_square("c", 4)), moves)

    def test_pawn_on_file_edge_has_only_one_diagonal(self):
        # White pawn on a3, no wraparound to a nonexistent file.
        position = eng.parse_fen("8/8/8/8/1p6/P7/8/8 w - - 0 1")
        a3 = position.get_square("a", 3)
        moves = moves_from(position, a3)
        self.assertEqual(moves, {eng.Move(a3, position.get_square("a", 4)), eng.Move(a3, position.get_square("b", 4))})


class TestPseudoLegalMoves(unittest.TestCase):
    def test_pseudo_legal_moves(self):
        position = eng.parse_fen("8/4b3/2p2Q2/2pk4/3P4/B2K4/8/8 b - - 0 1")
        all_moves = set(position.get_pseudo_legal_moves())

        queen_moves = moves_from(position, position.get_square("f", 6))
        bishop_moves = moves_from(position, position.get_square("a", 3)) | moves_from(position, position.get_square("e", 7))
        pawn_moves = (
            moves_from(position, position.get_square("c", 6))
            | moves_from(position, position.get_square("c", 5))
            | moves_from(position, position.get_square("d", 4))
        )
        king_moves = moves_from(position, position.get_square("d", 5)) | moves_from(position, position.get_square("d", 3))

        self.assertEqual(all_moves, bishop_moves | pawn_moves | king_moves | queen_moves)


if __name__ == "__main__":
    unittest.main()