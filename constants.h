namespace Pieces {
	// white pieces
	const int WHITE_KING = 0b0101;
	const int WHITE_QUEEN = 0b0100;
	const int WHITE_ROOK = 0b0011;
	const int WHITE_BISHOP = 0b0010;
	const int WHITE_KNIGHT = 0b0001;
	const int WHITE_PAWN = 0b0000;

	// black pieces
	const int BLACK_KING = 0b1101;
	const int BLACK_QUEEN = 0b1100;
	const int BLACK_ROOK = 0b1011;
	const int BLACK_BISHOP = 0b1010;
	const int BLACK_KNIGHT = 0b1001;
	const int BLACK_PAWN = 0b1000;

	// no piece
	const int NO_PIECE = 0b1111;

	// colors
	const int BLACK = 1;
	const int WHITE = 0;
	const int NO_COLOR = -1;
}

namespace Offsets {
	const int UP_LEFT = 7;
	const int DOWN_LEFT = -9;
	const int UP_RIGHT = 9;
	const int DOWN_RIGHT = -7;
	const int UP_STRAIGHT = 8;
	const int DOWN_STRAIGHT = -8;
	const int LEFT_STRAIGHT = -1;
	const int RIGHT_STRAIGHT = 1;
}