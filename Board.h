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
	const int DOWN_LEFT = -9;
	const int UP_RIGHT = 9;
	const int DOWN_RIGHT = -7;
	const int UP_STRAIGHT = 8;
	const int DOWN_STRAIGHT = -8;
	const int LEFT_STRAIGHT = -1;
	const int RIGHT_STRAIGHT = 1;
}

class Board
{
public:
	Board();
	Board(const string& FEN);
	Board(const Board& b1);
	~Board();
	
	int boardArray[64];
	vector<int> blackPieces[16]; // array of what squares are occupied by black pieces
	vector<int> whitePieces[16]; // array of what squares are occupied by white pices
	int distanceToLeftEdge[64];
	int distanceToRightEdge[64];
	int distanceToTopEdge[64];
	int distanceToBottomEdge[64];

	void calculateDistanceArrays();
	int charToPiece(char symbol);
	char printPiece(int piece);
	void printBoard(ostream &os);	
	void movePiece(int initial, int destination);
	float evaluatePosition();
	int getPiece(int position);
	int getPieceColor(int position);
	bool checkFriendly(int color, int destination);
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

Board::Board(const string& FEN) {
	int row = 7; 
	int col = 0;
	for (size_t i = 0; i < FEN.size(); ++i) {
		if (FEN[i] == ' ') {
			break;
		}

		if (FEN[i] == '/') {
			--row;
			col = 0;
			continue;
		}

		if (48 <= FEN[i] && FEN[i] <= 57) {
			int x = int(FEN[i]) - 48;
			std::cout << x << endl;
			for (int j = 0; j < int(FEN[i]) - 48; ++j) {
				boardArray[row * 8 + col] = Pieces::NO_PIECE;
				++col;
			}
			continue;
		}
		
		boardArray[8 * row + col] = charToPiece(FEN[i]);
		++col;
	}

	calculateDistanceArrays();
}



Board::Board(const Board& b1) {
	for (int i = 0; i < 64; ++i) {
		boardArray[i] = b1.boardArray[i];
	}

	calculateDistanceArrays();
}

Board::~Board()
{
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

int Board::charToPiece(char symbol) {
	switch (symbol)
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
		cout << "Error, undefined piece" << endl;
		exit(1);
		break;
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
	for (int i = 1; i <= distanceMatrix[position]; ++i) {
		int potentialSquare = position + (offset * i);
		if (potentialSquare < 0 || potentialSquare > 63) {
			break;
		}
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
		generateAlongDirection(validSquares, color, position, Offsets::LEFT_STRAIGHT, distanceToLeftEdge);
		generateAlongDirection(validSquares, color, position, Offsets::RIGHT_STRAIGHT, distanceToRightEdge);
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
		generateAlongDirection(validSquares, color, position, Offsets::LEFT_STRAIGHT, distanceToLeftEdge);
		generateAlongDirection(validSquares, color, position, Offsets::RIGHT_STRAIGHT, distanceToRightEdge);
		return validSquares;
	}
}

// helper function
bool Board::checkFriendly(int color, int destination) {
	if (getPieceColor(destination) == color) {
		return false;
	}
	return true;
}

vector<int> Board::generateValidSquaresHorse(int color, int position) {
	int row = position / 8;
	int column = position % 8;

	const int SHORT_LEFT_UP = position + 8 - 2;
	const int SHORT_LEFT_DOWN = position - 8 - 2;
	const int LONG_LEFT_UP = position + 16 - 1;
	const int LONG_LEFT_DOWN = position - 16 - 1;

	const int SHORT_RIGHT_UP = position + 8 + 2;
	const int SHORT_RIGHT_DOWN = position - 8 + 2;
	const int LONG_RIGHT_UP = position + 16 + 1;
	const int LONG_RIGHT_DOWN = position - 16 + 1;

	vector<int> possibleKnightMoves {SHORT_LEFT_UP, SHORT_LEFT_DOWN, LONG_LEFT_UP, LONG_LEFT_DOWN,
									SHORT_RIGHT_UP, SHORT_RIGHT_DOWN, LONG_RIGHT_UP, LONG_RIGHT_DOWN};
	
	vector<int> validMoves;

	for (int move : possibleKnightMoves) {
		if ((move < 0) || (move > 63)) { // off the board
			continue;
		}

		if (move == SHORT_LEFT_UP) {
			if (row > 6 || column < 2) continue;
		}
		else if (move == SHORT_LEFT_DOWN) {
			if (row < 1 || column < 2) continue;
		}
		else if (move == LONG_LEFT_UP) {
			if (row > 5 || column < 1) continue;
		}
		else if (move == LONG_LEFT_DOWN) {
			if (row < 2 || column < 1) continue;
		}
		else if (move == SHORT_RIGHT_UP) {
			if (row > 6 || column > 5) continue;
		}
		else if (move == SHORT_RIGHT_DOWN) {
			if (row < 1 || column > 5) continue;
		}
		else if (move == LONG_RIGHT_UP) {
			if (row > 5 || column > 6) continue;
		}
		else if (move == LONG_RIGHT_DOWN) {
			if (row < 2 || column > 6) continue;
		}
		
		if (checkFriendly(color, move)) {
			validMoves.push_back(move);
		}
	}

	return validMoves;
}

vector<int> Board::generateValidSquaresPawn(int color, int position) {
	int row = position / 8;
	int col = position % 8;
	vector<int> validSquares;
	if(color == Pieces::BLACK) {
		// if on starting position can move two squares
		if (row == 6) {
			int twoSquaresAheadColor = getPieceColor(position - 16);
			if (twoSquaresAheadColor == Pieces::NO_COLOR) {
				validSquares.push_back(position - 16);
			}
		}

		// check square immediately in front
		if (!(row == 0)) {
			int squareAheadColor = getPieceColor(position - 8);
			if (squareAheadColor == Pieces::NO_COLOR) {
				validSquares.push_back(position - 8);
			}
		}
		else {
			return {}; // this would be an error
		} 
		
		// check right diagonal square
		if (!(col == 0)) {
			int rightDiagonalColor = getPieceColor(position - 8 - 1);
			if (rightDiagonalColor == Pieces::WHITE) {
				validSquares.push_back(position - 8 - 1);
			}
		}

		// check left diagonal square
		if (!(col == 7)) {
			int leftDiagonalColor = getPieceColor(position - 8 + 1);
			if (leftDiagonalColor == Pieces::WHITE) {
				validSquares.push_back(position - 8 + 1);
			}

		}

		return validSquares;
	}
	else if (color == Pieces::WHITE) {
		// if on starting position can move two squares
		if (row == 1) {
			int twoSquaresAheadColor = getPieceColor(position + 16);
			if (twoSquaresAheadColor == Pieces::NO_COLOR) {
				validSquares.push_back(position + 16);
			}
		}

		// check square immediately in front
		if (!(row == 7)) {
			int squareAheadColor = getPieceColor(position + 8);
			if (squareAheadColor == Pieces::NO_COLOR) {
				validSquares.push_back(position + 8);
			}
		}
		else {
			return {}; // this would be an error
		} 
		
		// check right diagonal square
		if (!(col == 7)) {
			int rightDiagonalColor = getPieceColor(position + 8 + 1);
			if (rightDiagonalColor == Pieces::BLACK) {
				validSquares.push_back(position + 8 + 1);
			}
		}

		// check left diagonal square
		if (!(col == 0)) {
			int leftDiagonalColor = getPieceColor(position + 8 - 1);
			if (leftDiagonalColor == Pieces::BLACK) {
				validSquares.push_back(position + 8 - 1);
			}
		}

		return validSquares;
	}
	else {
		std::cout << "Error: invalid color" << std::endl;
		return {};
	}
}