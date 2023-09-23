#include "Board.h"
#include <list>
#include <cassert>

class Game
{
public:
	Game();
	~Game();

	int playerTurn;
	std::list<Board> history;

	int coordinateToArrayNumber(int row, char col) {
		return (8 * (row - 1)) + (col - 97);
	}

	// Creates a new board, makes move, then pushes on to history.
	void move(int rowInitial, char colInitial, int rowDestination, char colDestination) {
		int initial = coordinateToArrayNumber(rowInitial, colInitial);
		int destination = coordinateToArrayNumber(rowDestination, colDestination);
		if (!isValidMove(initial, destination)) {
			cout << "Not valid move!" << endl;
			return;
		}
		Board board = history.front();
		board.movePiece(initial, destination);
		history.push_front(board);
		history.front().printBoard(cout);
	}

	vector<int> generateValidSquares(int piece, int position) {
		if (piece == Pieces::BLACK_ROOK ||
			piece == Pieces::WHITE_ROOK ||
			piece == Pieces::BLACK_BISHOP ||
			piece == Pieces::WHITE_BISHOP ||
			piece == Pieces::BLACK_QUEEN ||
			piece == Pieces::WHITE_QUEEN) {
				return history.front().generateValidSquaresSlidingPiece(piece, position);
		}

		if (piece == Pieces::WHITE_PAWN || piece == Pieces::BLACK_PAWN) {
				int color = piece >> 3;
				return history.front().generateValidSquaresPawn(color, position);
		}

		if (piece == Pieces::WHITE_KNIGHT || piece == Pieces::BLACK_KNIGHT) {
			int color = piece >> 3;
			return history.front().generateValidSquaresHorse(color, position);
		}
		return {};
	}

	bool isValidMove(int initial, int destination) {
		int piece = history.front().getPiece(initial);
		vector<int> validSquares = generateValidSquares(piece, initial);
		for (size_t i = 0; i < validSquares.size(); ++i) {
			if (validSquares[i] == destination) {
				return true;
			}
		}
		return false;
	}

};

Game::Game()
{
	playerTurn = Pieces::WHITE;
	Board board;
	history.push_back(board);
	history.front().printBoard(cout);
}

Game::~Game()
{
}