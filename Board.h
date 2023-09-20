#include <string>
#include <iostream>
#include<vector>

using namespace std;

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
	const int DOWN_LEFT = -7;
	const int UP_RIGHT = 9;
	const int DOWN_RIGHT = -9;
	const int UP_STRAIGHT = 8;
	const int DOWN_STRAIGHT = 8;
}

class Board
{
public:
	Board();
	~Board();
	Board(const Board& b1);
	
	int boardArray[64];
	vector<int> blackPieces[16]; // array of what squares are occupied by black pieces
	vector<int> whitePieces[16]; // array of what squares are occupied by white pices
	int distanceToLeftEdge[64];
	int distanceToRightEdge[64];
	int distanceToTopEdge[64];
	int distanceToBottomEdge[64];
	void calculateDistanceArrays();


	char printPiece(int piece);
	void printBoard(ostream &os);	
	void movePiece(int initial, int destination);
	float evaluatePosition();
	int getPiece(int position);
	int getPieceColor(int position);
	void generateAlongDirection(vector<int>& validSquares, int color, int position, int offset, int *distanceMatrix);
	vector<int> generateValidSquaresSlidingPiece(int piece, int position);
	vector<int> generateValidSquaresHorse(int color, int position);
	vector<int> generateValidSquaresPawn(int color, int position);
	vector<int> generateValidSquaresKing(int color, int position);
};

Board::Board()
{
	boardArray[0] = Pieces::WHITE_ROOK;
	boardArray[1] = Pieces::WHITE_KNIGHT;
	boardArray[2] = Pieces::WHITE_BISHOP;
	boardArray[3] = Pieces::WHITE_QUEEN;
	boardArray[4] = Pieces::WHITE_KING;
	boardArray[5] = Pieces::WHITE_BISHOP;
	boardArray[6] = Pieces::WHITE_KNIGHT;
	boardArray[7] = Pieces::WHITE_ROOK;

	boardArray[56] = Pieces::BLACK_ROOK;
	boardArray[57] = Pieces::BLACK_KNIGHT;
	boardArray[58] = Pieces::BLACK_BISHOP;
	boardArray[59] = Pieces::BLACK_QUEEN;
	boardArray[60] = Pieces::BLACK_KING;
	boardArray[61] = Pieces::BLACK_BISHOP;
	boardArray[62] = Pieces::BLACK_KNIGHT;
	boardArray[63] = Pieces::BLACK_ROOK;

	for (auto column = 0; column < 8; ++column) {
		boardArray[8 + column] = Pieces::WHITE_PAWN;
		boardArray[(8 * 6) + column] = Pieces::BLACK_PAWN;
	}

	for (auto row = 2; row < 6; ++row) {
		for (auto column = 0; column < 8; ++column) {
			boardArray[(8 * row) + column] = Pieces::NO_PIECE;
		}
	}

	calculateDistanceArrays();
}

Board::~Board()
{
}

Board::Board(const Board& b1) {
	for (int i = 0; i < 64; ++i) {
		boardArray[i] = b1.boardArray[i];
	}
}

void Board::calculateDistanceArrays() {
	for (int i = 0; i < 64; ++i) {
		int row = (i / 8);
		int col = i % 8;
		Board::distanceToLeftEdge[i] = col;
		Board::distanceToRightEdge[i] = 7 - col;
		Board::distanceToTopEdge[i] = 7 - row;
		Board::distanceToBottomEdge[i] = row;
	}
}

char Board::printPiece(int piece) {
		switch (piece)
		{
		case Pieces::WHITE_KING:
			return 'K';
			break;
		case Pieces::WHITE_QUEEN:
			return 'Q';
			break;
		case Pieces::WHITE_ROOK:
			return 'R';
			break;
		case Pieces::WHITE_BISHOP:
			return 'B';
			break;
		case Pieces::WHITE_KNIGHT:
			return 'N';
			break;
		case Pieces::WHITE_PAWN:
			return 'P';
			break;
		case Pieces::BLACK_KING:
			return 'k';
			break;
		case Pieces::BLACK_QUEEN:
			return 'q';
			break;
		case Pieces::BLACK_ROOK:
			return 'r';
			break;
		case Pieces::BLACK_BISHOP:
			return 'b';
			break;
		case Pieces::BLACK_KNIGHT:
			return 'n';
			break;
		case Pieces::BLACK_PAWN:
			return 'p';
			break;
		default:
			return ' ';
			break;
		}
	}

void Board::printBoard(ostream &os) {
	os << " _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _" << endl;
	for (auto row = 7; row > 0; --row) {
		os << "|" << row + 1 << "    |     |     |     |     |     |     |     |" << endl;
		for (auto column = 0; column < 8; ++column) {
			os << "|  " << printPiece(boardArray[(8 * row) + column]) << "  ";
		}
		os << "|" << endl;
		os << "|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|" << endl;
	}
	os << "|" << 1 << "    |     |     |     |     |     |     |     |" << endl;
	for (auto column = 0; column < 8; ++column) {
		os << "|  " << printPiece(boardArray[column]) << "  ";
	}
	os << "|" << endl;
	os << "|_ _ a|_ _ b|_ _ c|_ _ d|_ _ e|_ _ f|_ _ g|_ _ h|" << endl;
}

void Board::movePiece(int initial, int destination) {
	boardArray[destination] = boardArray[initial];
	boardArray[initial] = Pieces::NO_PIECE;
}

float Board::evaluatePosition() {
	return 0;
}

int Board::getPiece(int position) {
	return boardArray[position];
}

int Board::getPieceColor(int position) {
	int piece = boardArray[position];
	if (piece == Pieces::NO_PIECE) {
		return Pieces::NO_COLOR;
	}
	return piece >> 3;
}

void Board::generateAlongDirection(vector<int>& validSquares, int color, int position, int offset, int *distanceMatrix) {
	for (int i = 0; i < distanceMatrix[position]; ++i) {
		int potentialSquare = position + (offset * i);
		int potentialSquarePieceColor = getPieceColor(potentialSquare);
		if (potentialSquarePieceColor == color) {
			break;
		}
		else if (potentialSquarePieceColor == !color) {
			validSquares.push_back(potentialSquare);
			break;
		}
		else {
			validSquares.push_back(potentialSquare);
		}
	}
} 

vector<int> Board::generateValidSquaresSlidingPiece(int piece, int position) {
	vector<int> validSquares;
	int color = getPieceColor(position);
	if (piece == Pieces::BLACK_ROOK || piece == Pieces::WHITE_ROOK) {
		generateAlongDirection(validSquares, color, position, Offsets::DOWN_STRAIGHT, distanceToBottomEdge);
		generateAlongDirection(validSquares, color, position, Offsets::UP_STRAIGHT, distanceToTopEdge);
		return validSquares;
	}
	else if (piece == Pieces::BLACK_BISHOP || piece == Pieces::WHITE_BISHOP) {
		generateAlongDirection(validSquares, color, position, Offsets::UP_LEFT, distanceToLeftEdge);
		generateAlongDirection(validSquares, color, position, Offsets::UP_RIGHT, distanceToRightEdge);
		generateAlongDirection(validSquares, color, position, Offsets::DOWN_LEFT, distanceToLeftEdge);
		generateAlongDirection(validSquares, color, position, Offsets::DOWN_RIGHT, distanceToRightEdge);
		return validSquares;
	}
	else {
		generateAlongDirection(validSquares, color, position, Offsets::DOWN_STRAIGHT, distanceToBottomEdge);
		generateAlongDirection(validSquares, color, position, Offsets::UP_STRAIGHT, distanceToTopEdge);
		generateAlongDirection(validSquares, color, position, Offsets::UP_LEFT, distanceToLeftEdge);
		generateAlongDirection(validSquares, color, position, Offsets::UP_RIGHT, distanceToRightEdge);
		generateAlongDirection(validSquares, color, position, Offsets::DOWN_LEFT, distanceToLeftEdge);
		generateAlongDirection(validSquares, color, position, Offsets::DOWN_RIGHT, distanceToRightEdge);
		return validSquares;
	}
}