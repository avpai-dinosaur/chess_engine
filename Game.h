#include "Board.h"
#include <list>
#include <cassert>

class Game
{
public:
	Game();
	Game(const string& FEN);
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
		int piece = history.front().getPiece(initial);
		int color = piece >> 3;
		if (color != playerTurn) {
			cout << "Not valid move!" << endl;
			return;
		}
		Board board = history.front();
		board.movePiece(initial, destination);
		history.push_front(board);
		history.front().printBoard(cout);
		playerTurn == Pieces::WHITE ? playerTurn = Pieces::BLACK : playerTurn = Pieces::WHITE; 
	}

	void move(int initial, int destination) {
		if (!isValidMove(initial, destination)) {
			cout << "Not valid move!" << endl;
			return;
		}
		int piece = history.front().getPiece(initial);
		int color = piece >> 3;
		
		if (color != playerTurn) {
			cout << "Not valid move!" << endl;
			return;
		}
		
		Board board = history.front();
		board.movePiece(initial, destination);
		history.push_front(board);
		history.front().printBoard(cout);
		playerTurn == Pieces::WHITE ? playerTurn = Pieces::BLACK : playerTurn = Pieces::WHITE; 
	}

	void undoMove() {
		history.pop_front();
		if (playerTurn == 0) playerTurn = 1;
		else playerTurn = 0;
	}

	vector<int> generateValidSquares(int piece, int position) {
		int color = piece >> 3;

		if (piece == Pieces::BLACK_ROOK ||
			piece == Pieces::WHITE_ROOK ||
			piece == Pieces::BLACK_BISHOP ||
			piece == Pieces::WHITE_BISHOP ||
			piece == Pieces::BLACK_QUEEN ||
			piece == Pieces::WHITE_QUEEN) {
				return history.front().generateValidSquaresSlidingPiece(piece, position, "valid");
		}

		if (piece == Pieces::WHITE_PAWN || piece == Pieces::BLACK_PAWN) {
			return history.front().generateValidSquaresPawn(color, position);
		}

		if (piece == Pieces::WHITE_KNIGHT || piece == Pieces::BLACK_KNIGHT) {
			return history.front().generateValidSquaresHorse(color, position, "valid");
		}

		if (piece == Pieces::WHITE_KING || piece == Pieces::BLACK_KING) {
			return history.front().generateValidSquaresKing(color, position, "valid");
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

	int perft(Board board, int depthTarget) {
		if (depthTarget == 0) {
			return 1;
		}
		int nodes = 0;

		vector<pair<int, int>> pieceVector = board.generatePieceVector(playerTurn);
		for (size_t i = 0; i < pieceVector.size(); ++i) {
			vector<int> validSquares = generateValidSquares(pieceVector[i].second, pieceVector[i].first);
			for (size_t j = 0; j < validSquares.size(); ++j) {
				move(pieceVector[i].first, validSquares[j]);
				nodes += perft(history.front(), depthTarget - 1);
				undoMove();
			}
		}

		cout << "nodes to depth " << depthTarget << " = " << nodes << endl;
		return nodes;
	}
};

Game::Game() {
	playerTurn = Pieces::WHITE;
	Board board;
	history.push_back(board);
	history.front().printBoard(cout);
}

Game::Game(const string& FEN) {
	size_t endOfBoard = 0;
	for (size_t i = 0; i < FEN.size(); ++i) {
		if(FEN[i] == ' ') {
			endOfBoard = i;
			break;
		}
	}

	FEN[endOfBoard + 1] == 'w' ? playerTurn = Pieces::WHITE : playerTurn = Pieces::BLACK;
    
	Board board(FEN);
	history.push_back(board);
	history.front().printBoard(cout);
}

Game::~Game()
{
}