#include "Engine.h"

Engine::Engine() {
	playerTurn = Pieces::WHITE;
	Board board;
	history.push_back(board);
	history.front().printBoard(cout);
}

Engine::Engine(const string& FEN) {
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

Engine::~Engine()
{
}

int Engine::coordinateToArrayNumber(int row, char col) {
	return (8 * (row - 1)) + (col - 97);
}

Board Engine::getCurrentPosition() {
	return history.front();
}

pair<int, int> Engine::parseUserInput(int rowInitial, int rowDestination, int colInitial, int colDestination) {
	int initial = coordinateToArrayNumber(rowInitial, colInitial);
	int destination = coordinateToArrayNumber(rowDestination, colDestination);
	return {initial, destination};
}

void Engine::move(int initial, int destination) {
	if (!history.front().isValidMove(initial, destination)) {
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

void Engine::undoMove() {
	history.pop_front();
	if (playerTurn == Pieces::WHITE) playerTurn = Pieces::BLACK;
	else playerTurn = Pieces::WHITE;
}

int Engine::perft(Board board, int depthTarget) {
	if (depthTarget == 0) {
		return 1;
	}
	int nodes = 0;
	vector<pair<int, int>> pieceVector = board.generatePieceVector(playerTurn);
	for (size_t i = 0; i < pieceVector.size(); ++i) {
		vector<int> validSquares = board.generateValidSquares(pieceVector[i].second, pieceVector[i].first);
		for (size_t j = 0; j < validSquares.size(); ++j) {
			move(pieceVector[i].first, validSquares[j]);
			nodes += perft(history.front(), depthTarget - 1);
			undoMove();
		}
	}
	cout << "nodes to depth " << depthTarget << " = " << nodes << endl;
	return nodes;
}