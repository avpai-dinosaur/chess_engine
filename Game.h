#include "Board.h"
#include <cassert>

int decodePiece(char piece);

class Game
{
public:
	Game();
	~Game();

	Board board;

	int coordinateToArrayNumber(int row, char col) {
		return (8 * (row - 1)) + (col - 97);
	}

	/* vector<int> generateKnightMoves(int rowInitial, char colInitial) {
		int arrayNumber = userSquareInputToArrayNumber(rowInitial, colInitial);
		return;
	} */

	void start() {
		board.printBoard(cout);
	}

	void move(char pieceChar, int rowInitial, int colInitial, int rowDestination, int colDestination) {
		int initial = coordinateToArrayNumber(rowInitial, colInitial);
		int destination = coordinateToArrayNumber(rowDestination, colDestination);
		board.movePiece(initial, destination);
		board.printBoard(cout);
	}

	/* vector<int> generateValidSquares(char piece, int rowInitial, char colInitial) {
		int arrayNumber = userSquareInputToArrayNumber(rowInitial, colInitial);
		vector<int> validSquares;
		
		// black pawns
		if (piece == BLACK_PAWN) {
			// If pawn is on back rank
			if (0 <= arrayNumber && arrayNumber <= 7) {
				//TODO promote
				return validSquares;
			}
			
			// Moving pawns forwards (if we get here our pawn is not on the back rank)
			// option to move two squares forwards if pawn has not moved
			if (48 <= arrayNumber && arrayNumber <= 55) {
				if (board.boardArray[arrayNumber - 16] == ' ') {
					validSquares.push_back(arrayNumber - 16);
				}
			}
			// One move forwards
			if ((arrayNumber - 8) >= 0 && board.boardArray[arrayNumber - 8] == ' ') {
				validSquares.push_back(arrayNumber - 8);
			}
			
			// Capturing Diagonally
			// Case 1: pawn is on a rank
			if (arrayNumber % 8 == 0) {
				int rightDiagonal = arrayNumber - 8 + 1;
				if ((rightDiagonal >= 0)
					&& (board.boardColor[rightDiagonal] == PieceColor::white)) {
					validSquares.push_back(rightDiagonal);
				}
			}
			// Case 2: pawn is on h rank
			else if (arrayNumber % 8 == 7) {
				int leftDiagonal = arrayNumber - 8 - 1;
				if ((leftDiagonal >= 0)
					&& (board.boardColor[leftDiagonal] == PieceColor::white)) {
					validSquares.push_back(leftDiagonal);
				}
			}
			// Case 3: pawn is on any other rank
			else {
				int rightDiagonal = arrayNumber - 8 + 1;
				if ((rightDiagonal >= 0)
					&& (board.boardColor[rightDiagonal] == PieceColor::white)) {
					validSquares.push_back(rightDiagonal);
				}

				int leftDiagonal = arrayNumber - 8 - 1;
				if ((leftDiagonal >= 0)
					&& (board.boardColor[leftDiagonal] == PieceColor::white)) {
					validSquares.push_back(leftDiagonal);
				}
			}

		}
		// white pawns
		else if (piece == WHITE_PAWN) {
			// If pawn is on back rank
			if (56 <= arrayNumber && arrayNumber <= 63) {
				//TODO promote
				return validSquares;
			}

			// Moving pawns forwards (if we get here our pawn is not on the back rank)
			// option to move two squares forwards if pawn has not moved
			if (8 <= arrayNumber && arrayNumber <= 15) {
				if (board.boardArray[arrayNumber + 16] == ' ') {
					validSquares.push_back(arrayNumber + 16);
				}
			}
			// One move forwards
			if (((arrayNumber + 8) <= 63) && board.boardArray[arrayNumber + 8] == ' ') {
				validSquares.push_back(arrayNumber + 8);
			}

			// Capturing Diagonally
			// Case 1: pawn is on a rank
			if (arrayNumber % 8 == 0) {
				int rightDiagonal = arrayNumber + 8 + 1;
				if ((rightDiagonal <= 63)
					&& (board.boardColor[rightDiagonal] == PieceColor::black)) {
					validSquares.push_back(rightDiagonal);
				}
			}
			// Case 2: pawn is on h rank
			else if (arrayNumber % 8 == 7) {
				int leftDiagonal = arrayNumber + 8 - 1;
				if ((leftDiagonal <= 63)
					&& (board.boardColor[leftDiagonal] == PieceColor::black)) {
					validSquares.push_back(leftDiagonal);
				}
			}
			// Case 3: pawn is on any other rank
			else {
				int rightDiagonal = arrayNumber + 8 + 1;
				if ((rightDiagonal <= 63)
					&& (board.boardColor[rightDiagonal] == PieceColor::black)) {
					validSquares.push_back(rightDiagonal);
				}

				int leftDiagonal = arrayNumber + 8 - 1;
				if ((leftDiagonal <= 63)
					&& (board.boardColor[leftDiagonal] == PieceColor::black)) {
					validSquares.push_back(leftDiagonal);
				}
			}
		}
		// black rooks
		else if (piece == BLACK_ROOK) {
			// look at squares in north direction
			for (int square = arrayNumber + 8; square < 64; square += 8) {
				if (board.boardColor[square] == PieceColor::black) {
					break;
				}
				else if (board.boardColor[square] == PieceColor::white) {
					validSquares.push_back(square);
					break;
				}
				else {
					validSquares.push_back(square);
				}
			}
			// look at squares in south direction
			for (int square = arrayNumber - 8; square >= 0; square -= 8) {
				if (board.boardColor[square] == PieceColor::black) {
					break;
				}
				else if (board.boardColor[square] == PieceColor::white) {
					validSquares.push_back(square);
					break;
				}
				else {
					validSquares.push_back(square);
				}
			}
			// look at squares in east direction
			for (int square = arrayNumber + 1; square < rowInitial * 8; ++square) {
				if (board.boardColor[square] == PieceColor::black) {
					break;
				}
				else if (board.boardColor[square] == PieceColor::white) {
					validSquares.push_back(square);
					break;
				}
				else {
					validSquares.push_back(square);
				}
			}
			// look at squares in west directoin
			for (int square = arrayNumber - 1; square > (rowInitial - 1) * 8; --square) {
				if (board.boardColor[square] == PieceColor::black) {
					break;
				}
				else if (board.boardColor[square] == PieceColor::white) {
					validSquares.push_back(square);
					break;
				}
				else {
					validSquares.push_back(square);
				}
			}
		}
		// white rooks
		else if (piece == WHITE_ROOK) {
			// look at squares in north direction
			for (int square = arrayNumber + 8; square < 64; square += 8) {
				if (board.boardColor[square] == PieceColor::white) {
					break;
				}
				else if (board.boardColor[square] == PieceColor::black) {
					validSquares.push_back(square);
					break;
				}
				else {
					validSquares.push_back(square);
				}
			}
			// look at squares in south direction
			for (int square = arrayNumber - 8; square >= 0; square -= 8) {
				if (board.boardColor[square] == PieceColor::white) {
					break;
				}
				else if (board.boardColor[square] == PieceColor::black) {
					validSquares.push_back(square);
					break;
				}
				else {
					validSquares.push_back(square);
				}
			}
			// look at squares in east direction
			for (int square = arrayNumber + 1; square < rowInitial * 8; ++square) {
				if (board.boardColor[square] == PieceColor::white) {
					break;
				}
				else if (board.boardColor[square] == PieceColor::black) {
					validSquares.push_back(square);
					break;
				}
				else {
					validSquares.push_back(square);
				}
			}
			// look at squares in west directoin
			for (int square = arrayNumber - 1; square > (rowInitial - 1) * 8; --square) {
				if (board.boardColor[square] == PieceColor::white) {
					break;
				}
				else if (board.boardColor[square] == PieceColor::black) {
					validSquares.push_back(square);
					break;
				}
				else {
					validSquares.push_back(square);
				}
			}
		}
		// black bishops
		else if (piece == BLACK_BISHOP) {
			// NE diagonal
			for (auto square = arrayNumber + 9; square < 64; square += 9) {
				if (board.boardColor[square] == PieceColor::black) {
					break;
				}
				else if (board.boardColor[square] == PieceColor::white) {
					validSquares.push_back(square);
					break;
				}
				else {
					validSquares.push_back(square);
				}

				if (square % 8 == 7) {
					break;
				}
			}
			// NW diagonal
			for (auto square = arrayNumber + 7; square < 64; square += 7) {
				if (board.boardColor[square] == PieceColor::black) {
					break;
				}
				else if (board.boardColor[square] == PieceColor::white) {
					validSquares.push_back(square);
					break;
				}
				else {
					validSquares.push_back(square);
				}

				if (square % 8 == 0) {
					break;
				}
			}
			// SE diagonal
			for (auto square = arrayNumber - 7; square >= 0; square -= 7) {
				if (board.boardColor[square] == PieceColor::black) {
					break;
				}
				else if (board.boardColor[square] == PieceColor::white) {
					validSquares.push_back(square);
					break;
				}
				else {
					validSquares.push_back(square);
				}

				if (square % 8 == 7) {
					break;
				}
			}
			// SW diagonal
			for (auto square = arrayNumber - 9; square >= 0; square -= 9) {
				if (board.boardColor[square] == PieceColor::black) {
					break;
				}
				else if (board.boardColor[square] == PieceColor::white) {
					validSquares.push_back(square);
					break;
				}
				else {
					validSquares.push_back(square);
				}

				if (square % 8 == 0) {
					break;
				}
			}
		}
		// white bishops
		else if (piece == WHITE_BISHOP) {
			// NE diagonal
			for (auto square = arrayNumber + 9; square < 64; square += 9) {
				if (board.boardColor[square] == PieceColor::white) {
					break;
				}
				else if (board.boardColor[square] == PieceColor::black) {
					validSquares.push_back(square);
					break;
				}
				else {
					validSquares.push_back(square);
				}

				if (square % 8 == 7) {
					break;
				}
			}
			// NW diagonal
			for (auto square = arrayNumber + 7; square < 64; square += 7) {
				if (board.boardColor[square] == PieceColor::white) {
					break;
				}
				else if (board.boardColor[square] == PieceColor::black) {
					validSquares.push_back(square);
					break;
				}
				else {
					validSquares.push_back(square);
				}

				if (square % 8 == 0) {
					break;
				}
			}
			// SE diagonal
			for (auto square = arrayNumber - 7; square >= 0; square -= 7) {
				if (board.boardColor[square] == PieceColor::white) {
					break;
				}
				else if (board.boardColor[square] == PieceColor::black) {
					validSquares.push_back(square);
					break;
				}
				else {
					validSquares.push_back(square);
				}

				if (square % 8 == 7) {
					break;
				}
			}
			// SW diagonal
			for (auto square = arrayNumber - 9; square >= 0; square -= 9) {
				if (board.boardColor[square] == PieceColor::white) {
					break;
				}
				else if (board.boardColor[square] == PieceColor::black) {
					validSquares.push_back(square);
					break;
				}
				else {
					validSquares.push_back(square);
				}

				if (square % 8 == 0) {
					break;
				}
			}
		}
		// black knights
		else if (piece == BLACK_KNIGHT) {
			int upRightShift = arrayNumber + 16 + 1;
			int upLeftShift = arrayNumber + 16 - 1;
			int downRightShift = arrayNumber - 16 + 1;
			int downLeftShift = arrayNumber - 16 - 1;

			int leftUpShift = arrayNumber - 2 + 8;
			int leftDownShift = arrayNumber - 2 - 8;
			int rightUpShift = arrayNumber + 2 + 8;
			int rightDownShift = arrayNumber + 2 - 8;

			// check up shifts
			bool upRightShiftValid = true;
			bool upLeftShiftValid = true;
			if (48 <= arrayNumber && arrayNumber <= 63) {
				upRightShiftValid = false;
				upLeftShiftValid = false;
			}
			else {
				if (arrayNumber % 8 == 7) {
					upRightShiftValid = false;
				}
				if (arrayNumber % 8 == 0) {
					upLeftShiftValid = false;
				}
			}

			// check down shifts
			bool downRightShiftValid = true;
			bool downLeftShiftValid = true;
			if (0 <= arrayNumber && arrayNumber <= 15) {
				downRightShiftValid = false;
				downLeftShiftValid = false;
			}
			else {
				if (arrayNumber % 8 == 7) {
					downRightShiftValid = false;
				}
				if (arrayNumber % 8 == 0) {
					downLeftShiftValid = false;
				}
			}

			// check left shifts
			bool leftUpShiftValid = true;
			bool leftDownShiftValid = true;
			if ((arrayNumber % 8 == 0) || (arrayNumber % 8 == 1)) {
				leftUpShiftValid = false;
				leftDownShiftValid = false;
			}
			else {
				if (56 <= arrayNumber && arrayNumber <= 63) {
					leftUpShiftValid = false;
				}
				if (0 <= arrayNumber && arrayNumber <= 7) {
					leftDownShiftValid = false;
				}
			}

			// check right shifts
			bool rightUpShiftValid = true;
			bool rightDownShiftValid = true;
			if ((arrayNumber % 8 == 6) || (arrayNumber % 8 == 7)) {
				rightUpShiftValid = false;
				rightDownShiftValid = false;
			}
			else {
				if (56 <= arrayNumber && arrayNumber <= 63) {
					rightUpShiftValid = false;
				}
				if (0 <= arrayNumber && arrayNumber <= 7) {
					rightDownShiftValid = false;
				}
			}

			if (upRightShiftValid) {
				if (board.boardColor[upRightShift] == PieceColor::white
					|| board.boardColor[upRightShift] == PieceColor::noColor) {
					validSquares.push_back(upRightShift);
				}
			}
			if (upLeftShiftValid) {
				if (board.boardColor[upLeftShift] == PieceColor::white
					|| board.boardColor[upLeftShift] == PieceColor::noColor) {
					validSquares.push_back(upLeftShift);
				}
			}
			if (downLeftShiftValid) {
				if (board.boardColor[downLeftShift] == PieceColor::white
					|| board.boardColor[downLeftShift] == PieceColor::noColor) {
					validSquares.push_back(downLeftShift);
				}
			}
			if (downRightShiftValid) {
				if (board.boardColor[downRightShift] == PieceColor::white
					|| board.boardColor[downRightShift] == PieceColor::noColor) {
					validSquares.push_back(downRightShift);
				}
			}
			if (leftUpShiftValid) {
				if (board.boardColor[leftUpShift] == PieceColor::white
					|| board.boardColor[leftUpShift] == PieceColor::noColor) {
					validSquares.push_back(leftUpShift);
				}
			}
			if (leftDownShiftValid) {
				if (board.boardColor[leftDownShift] == PieceColor::white
					|| board.boardColor[leftDownShift] == PieceColor::noColor) {
					validSquares.push_back(leftDownShift);
				}
			}
			if (rightUpShiftValid) {
				if (board.boardColor[rightUpShift] == PieceColor::white
					|| board.boardColor[rightUpShift] == PieceColor::noColor) {
					validSquares.push_back(rightUpShift);
				}
			}
			if (rightDownShiftValid) {
				if (board.boardColor[rightDownShift] == PieceColor::white
					|| board.boardColor[rightDownShift] == PieceColor::noColor) {
					validSquares.push_back(rightDownShift);
				}
			}
		}
		// white knights
		else if (piece == WHITE_KNIGHT) {
			int upRightShift = arrayNumber + 16 + 1;
			int upLeftShift = arrayNumber + 16 - 1;
			int downRightShift = arrayNumber - 16 + 1;
			int downLeftShift = arrayNumber - 16 - 1;

			int leftUpShift = arrayNumber - 2 + 8;
			int leftDownShift = arrayNumber - 2 - 8;
			int rightUpShift = arrayNumber + 2 + 8;
			int rightDownShift = arrayNumber + 2 - 8;

			// check up shifts
			bool upRightShiftValid = true;
			bool upLeftShiftValid = true;
			if (48 <= arrayNumber && arrayNumber <= 63) {
				upRightShiftValid = false;
				upLeftShiftValid = false;
			}
			else {
				if (arrayNumber % 8 == 7) {
					upRightShiftValid = false;
				}
				if (arrayNumber % 8 == 0) {
					upLeftShiftValid = false;
				}
			}

			// check down shifts
			bool downRightShiftValid = true;
			bool downLeftShiftValid = true;
			if (0 <= arrayNumber && arrayNumber <= 15) {
				downRightShiftValid = false;
				downLeftShiftValid = false;
			}
			else {
				if (arrayNumber % 8 == 7) {
					downRightShiftValid = false;
				}
				if (arrayNumber % 8 == 0) {
					downLeftShiftValid = false;
				}
			}

			// check left shifts
			bool leftUpShiftValid = true;
			bool leftDownShiftValid = true;
			if ((arrayNumber % 8 == 0) || (arrayNumber % 8 == 1)) {
				leftUpShiftValid = false;
				leftDownShiftValid = false;
			}
			else {
				if (56 <= arrayNumber && arrayNumber <= 63) {
					leftUpShiftValid = false;
				}
				if (0 <= arrayNumber && arrayNumber <= 7) {
					leftDownShiftValid = false;
				}
			}

			// check right shifts
			bool rightUpShiftValid = true;
			bool rightDownShiftValid = true;
			if ((arrayNumber % 8 == 6) || (arrayNumber % 8 == 7)) {
				rightUpShiftValid = false;
				rightDownShiftValid = false;
			}
			else {
				if (56 <= arrayNumber && arrayNumber <= 63) {
					rightUpShiftValid = false;
				}
				if (0 <= arrayNumber && arrayNumber <= 7) {
					rightDownShiftValid = false;
				}
			}

			if (upRightShiftValid) {
				if (board.boardColor[upRightShift] == PieceColor::black 
					|| board.boardColor[upRightShift] == PieceColor::noColor) {
					validSquares.push_back(upRightShift);
				}
			}
			if (upLeftShiftValid) {
				if (board.boardColor[upLeftShift] == PieceColor::black
					|| board.boardColor[upLeftShift] == PieceColor::noColor) {
					validSquares.push_back(upLeftShift);
				}
			}
			if (downLeftShiftValid) {
				if (board.boardColor[downLeftShift] == PieceColor::black
					|| board.boardColor[downLeftShift] == PieceColor::noColor) {
					validSquares.push_back(downLeftShift);
				}
			}
			if (downRightShiftValid) {
				if (board.boardColor[downRightShift] == PieceColor::black
					|| board.boardColor[downRightShift] == PieceColor::noColor) {
					validSquares.push_back(downRightShift);
				}
			}
			if (leftUpShiftValid) {
				if (board.boardColor[leftUpShift] == PieceColor::black
					|| board.boardColor[leftUpShift] == PieceColor::noColor) {
					validSquares.push_back(leftUpShift);
				}
			}
			if (leftDownShiftValid) {
				if (board.boardColor[leftDownShift] == PieceColor::black
					|| board.boardColor[leftDownShift] == PieceColor::noColor) {
					validSquares.push_back(leftDownShift);
				}
			}
			if (rightUpShiftValid) {
				if (board.boardColor[rightUpShift] == PieceColor::black
					|| board.boardColor[rightUpShift] == PieceColor::noColor) {
					validSquares.push_back(rightUpShift);
				}
			}
			if (rightDownShiftValid) {
				if (board.boardColor[rightDownShift] == PieceColor::black
					|| board.boardColor[rightDownShift] == PieceColor::noColor) {
					validSquares.push_back(rightDownShift);
				}
			}
		}
		// black queen
		else if (piece == BLACK_QUEEN) {
			// generate diagonal squares
			// NE diagonal
			for (auto square = arrayNumber + 9; square < 64; square += 9) {
				if (board.boardColor[square] == PieceColor::black) {
					break;
				}
				else if (board.boardColor[square] == PieceColor::white) {
					validSquares.push_back(square);
					break;
				}
				else {
					validSquares.push_back(square);
				}

				if (square % 8 == 7) {
					break;
				}
			}
			// NW diagonal
			for (auto square = arrayNumber + 7; square < 64; square += 7) {
				if (board.boardColor[square] == PieceColor::black) {
					break;
				}
				else if (board.boardColor[square] == PieceColor::white) {
					validSquares.push_back(square);
					break;
				}
				else {
					validSquares.push_back(square);
				}

				if (square % 8 == 0) {
					break;
				}
			}
			// SE diagonal
			for (auto square = arrayNumber - 7; square >= 0; square -= 7) {
				if (board.boardColor[square] == PieceColor::black) {
					break;
				}
				else if (board.boardColor[square] == PieceColor::white) {
					validSquares.push_back(square);
					break;
				}
				else {
					validSquares.push_back(square);
				}

				if (square % 8 == 7) {
					break;
				}
			}
			// SW diagonal
			for (auto square = arrayNumber - 9; square >= 0; square -= 9) {
				if (board.boardColor[square] == PieceColor::black) {
					break;
				}
				else if (board.boardColor[square] == PieceColor::white) {
					validSquares.push_back(square);
					break;
				}
				else {
					validSquares.push_back(square);
				}

				if (square % 8 == 0) {
					break;
				}
			}

			// generate ranks and files
			// look at squares in north direction
			for (int square = arrayNumber + 8; square < 64; square += 8) {
				if (board.boardColor[square] == PieceColor::black) {
					break;
				}
				else if (board.boardColor[square] == PieceColor::white) {
					validSquares.push_back(square);
					break;
				}
				else {
					validSquares.push_back(square);
				}
			}
			// look at squares in south direction
			for (int square = arrayNumber - 8; square >= 0; square -= 8) {
				if (board.boardColor[square] == PieceColor::black) {
					break;
				}
				else if (board.boardColor[square] == PieceColor::white) {
					validSquares.push_back(square);
					break;
				}
				else {
					validSquares.push_back(square);
				}
			}
			// look at squares in east direction
			for (int square = arrayNumber + 1; square < rowInitial * 8; ++square) {
				if (board.boardColor[square] == PieceColor::black) {
					break;
				}
				else if (board.boardColor[square] == PieceColor::white) {
					validSquares.push_back(square);
					break;
				}
				else {
					validSquares.push_back(square);
				}
			}
			// look at squares in west directoin
			for (int square = arrayNumber - 1; square > (rowInitial - 1) * 8; --square) {
				if (board.boardColor[square] == PieceColor::black) {
					break;
				}
				else if (board.boardColor[square] == PieceColor::white) {
					validSquares.push_back(square);
					break;
				}
				else {
					validSquares.push_back(square);
				}
			}
		}
		// white queen
		else if (piece == WHITE_QUEEN) {
			// generate diagonal squares
			// NE diagonal
			for (auto square = arrayNumber + 9; square < 64; square += 9) {
				if (board.boardColor[square] == PieceColor::white) {
					break;
				}
				else if (board.boardColor[square] == PieceColor::black) {
					validSquares.push_back(square);
					break;
				}
				else {
					validSquares.push_back(square);
				}

				if (square % 8 == 7) {
					break;
				}
			}
			// NW diagonal
			for (auto square = arrayNumber + 7; square < 64; square += 7) {
				if (board.boardColor[square] == PieceColor::white) {
					break;
				}
				else if (board.boardColor[square] == PieceColor::black) {
					validSquares.push_back(square);
					break;
				}
				else {
					validSquares.push_back(square);
				}

				if (square % 8 == 0) {
					break;
				}
			}
			// SE diagonal
			for (auto square = arrayNumber - 7; square >= 0; square -= 7) {
				if (board.boardColor[square] == PieceColor::white) {
					break;
				}
				else if (board.boardColor[square] == PieceColor::black) {
					validSquares.push_back(square);
					break;
				}
				else {
					validSquares.push_back(square);
				}

				if (square % 8 == 7) {
					break;
				}
			}
			// SW diagonal
			for (auto square = arrayNumber - 9; square >= 0; square -= 9) {
				if (board.boardColor[square] == PieceColor::white) {
					break;
				}
				else if (board.boardColor[square] == PieceColor::black) {
					validSquares.push_back(square);
					break;
				}
				else {
					validSquares.push_back(square);
				}

				if (square % 8 == 0) {
					break;
				}
			}

			// generate ranks and files
			// look at squares in north direction
			for (int square = arrayNumber + 8; square < 64; square += 8) {
				if (board.boardColor[square] == PieceColor::white) {
					break;
				}
				else if (board.boardColor[square] == PieceColor::black) {
					validSquares.push_back(square);
					break;
				}
				else {
					validSquares.push_back(square);
				}
			}
			// look at squares in south direction
			for (int square = arrayNumber - 8; square >= 0; square -= 8) {
				if (board.boardColor[square] == PieceColor::white) {
					break;
				}
				else if (board.boardColor[square] == PieceColor::black) {
					validSquares.push_back(square);
					break;
				}
				else {
					validSquares.push_back(square);
				}
			}
			// look at squares in east direction
			for (int square = arrayNumber + 1; square < rowInitial * 8; ++square) {
				if (board.boardColor[square] == PieceColor::white) {
					break;
				}
				else if (board.boardColor[square] == PieceColor::black) {
					validSquares.push_back(square);
					break;
				}
				else {
					validSquares.push_back(square);
				}
			}
			// look at squares in west directoin
			for (int square = arrayNumber - 1; square > (rowInitial - 1) * 8; --square) {
				if (board.boardColor[square] == PieceColor::white) {
					break;
				}
				else if (board.boardColor[square] == PieceColor::black) {
					validSquares.push_back(square);
					break;
				}
				else {
					validSquares.push_back(square);
				}
			}
		}

		return validSquares;
	} */

	// Returns true if a piece move is allowed. Returns false otherwise.
	// Inputs: piece, initial square, destination square
	/* bool isValidMove(char piece, int rowInitial, char colInitial, int rowDestination, char colDestination) {
		// first generate squares this piece can reach
		vector<int> validSquares = generateValidSquares(piece, rowInitial, colInitial);
		int destinationArrayNumber = userSquareInputToArrayNumber(rowDestination, colDestination);
		for (size_t square = 0; square < validSquares.size(); ++square) {
			if (validSquares[square] == userSquareInputToArrayNumber(rowDestination, colDestination)) {
				return true;
			}
		}

		return false;
	} */

};

Game::Game()
{
}

Game::~Game()
{
}

int decodePiece(char piece) {
	switch (piece)
	{
	case 'K':
		return Pieces::WHITE_KING;
		break;
	case 'Q':
		return Pieces::WHITE_QUEEN;
		break;
	case 'R':
		return Pieces::WHITE_ROOK;
		break;
	case 'B':
		return Pieces::WHITE_BISHOP;
		break;
	case 'N':
		return Pieces::WHITE_KNIGHT;
		break;
	case 'P':
		return Pieces::WHITE_PAWN;
		break;
	case 'k':
		return Pieces::BLACK_KING;
		break;
	case 'q':
		return Pieces::BLACK_QUEEN;
		break;
	case 'r':
		return Pieces::BLACK_ROOK;
		break;
	case 'b':
		return Pieces::BLACK_BISHOP;
		break;
	case 'n':
		return Pieces::BLACK_KNIGHT;
		break;
	case 'p':
		return Pieces::BLACK_PAWN;
		break;
	default:
		cout << "error: not a valid piece" << endl;
		exit(-1);
		break;
	}
	return 0;
}