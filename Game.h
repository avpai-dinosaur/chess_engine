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
	void move(int rowInitial, int colInitial, int rowDestination, int colDestination) {
		int initial = coordinateToArrayNumber(rowInitial, colInitial);
		int destination = coordinateToArrayNumber(rowDestination, colDestination);
		if (!isValidMove) {
			cout << "Not valid move!" << endl;
			return;
		}
		Board board = history.front();
		board.movePiece(initial, destination);
		history.push_front(board);
		history.front().printBoard(cout);
	}

	vector<int> generateValidSquares(int piece, int position) {
		return {0};
	}

	bool isValidMove(int initial, int destination) {
		return true;
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