#include <string>
#include <iostream>
#include<vector>

using namespace std;

enum class PieceColor {
	black,
	white,
	noColor
};

enum class PieceType {
	king,
	queen,
	rook,
	bishop,
	knight,
	pawn,
	noType
};

struct Piece {
	PieceColor color;
	PieceType type;
	int row;
	int col;
};

// white pieces
const char WHITE_KING = 'K';
const char WHITE_QUEEN = 'Q';
const char WHITE_ROOK = 'R';
const char WHITE_BISHOP = 'B';
const char WHITE_KNIGHT = 'N';
const char WHITE_PAWN = 'P';

// black pieces
const char BLACK_KING = 'k';
const char BLACK_QUEEN = 'q';
const char BLACK_ROOK = 'r';
const char BLACK_BISHOP = 'b';
const char BLACK_KNIGHT = 'n';
const char BLACK_PAWN = 'p';

class Board
{
public:
	Board();
	~Board();

	//Unicode pieces
	/*
	// white pieces
	const string WHITE_KING = "\u2655";
	const string WHITE_QUEEN = "\u2655";
	const string WHITE_ROOK = "\u2656";
	const string WHITE_BISHOP = "\u2657";
	const string WHITE_KNIGHT = "\u2658";
	const string WHITE_PAWN = "\u2659";

	// black pieces
	const string BLACK_KING = "\u265A";
	const string BLACK_QUEEN = "\u265B";
	const string BLACK_ROOK = "\u265C";
	const string BLACK_BISHOP = "\u265D";
	const string BLACK_KNIGHT = "\u265E";
	const string BLACK_PAWN = "\u265F";
	*/


	char boardArray[64];
	PieceColor boardColor[64];
	vector<Piece> pieces;
	
	void printBoard(ostream &os) {
		os << " _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _" << endl;
		for (auto row = 7; row > 0; --row) {
			os << "|" << row + 1 << "    |     |     |     |     |     |     |     |" << endl;
			for (auto column = 0; column < 8; ++column) {
				os << "|  " << boardArray[(8 * row) + column] << "  ";
			}
			os << "|" << endl;
			os << "|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|" << endl;
		}
		os << "|" << 1 << "    |     |     |     |     |     |     |     |" << endl;
		for (auto column = 0; column < 8; ++column) {
			os << "|  " << boardArray[column] << "  ";
		}
		os << "|" << endl;
		os << "|_ _ a|_ _ b|_ _ c|_ _ d|_ _ e|_ _ f|_ _ g|_ _ h|" << endl;
		
	}
};

Board::Board()
{
	boardArray[0] = WHITE_ROOK;
	//pieces.push_back({ PieceColor::white, PieceType::rook, 0, 0 });
	boardArray[1] = WHITE_KNIGHT;
	//pieces.push_back({ PieceColor::white, PieceType::knight, 0, 1 });
	boardArray[2] = WHITE_BISHOP;
	//pieces.push_back({ PieceColor::white, PieceType::bishop, 0, 2 });
	boardArray[3] = WHITE_QUEEN;
	//pieces.push_back({ PieceColor::white, PieceType::queen, 0, 3 });
	boardArray[4] = WHITE_KING;
	//pieces.push_back({ PieceColor::white, PieceType::king, 0, 4 });
	boardArray[5] = WHITE_BISHOP;
	//pieces.push_back({ PieceColor::white, PieceType::bishop, 0, 5 });
	boardArray[6] = WHITE_KNIGHT;
	//pieces.push_back({ PieceColor::white, PieceType::knight, 0, 6 });
	boardArray[7] = WHITE_ROOK;
	//pieces.push_back({ PieceColor::white, PieceType::rook, 0, 7 });

	for (auto column = 0; column < 8; ++column) {
		boardArray[8 + column] = WHITE_PAWN;
		pieces.push_back({ PieceColor::white, PieceType::pawn, 1, column });
	}

	boardArray[56] = BLACK_ROOK;
	//pieces.push_back({ PieceColor::black, PieceType::rook, 7, 0 });
	boardArray[57] = BLACK_KNIGHT;
	//pieces.push_back({ PieceColor::black, PieceType::knight, 7, 1 });
	boardArray[58] = BLACK_BISHOP;
	//pieces.push_back({ PieceColor::black, PieceType::bishop, 7, 2 });
	boardArray[59] = BLACK_QUEEN;
	//pieces.push_back({ PieceColor::black, PieceType::queen, 7, 3 });
	boardArray[60] = BLACK_KING;
	//pieces.push_back({ PieceColor::black, PieceType::king, 7, 4 });
	boardArray[61] = BLACK_BISHOP;
	//pieces.push_back({ PieceColor::black, PieceType::bishop, 7, 5 });
	boardArray[62] = BLACK_KNIGHT;
	//pieces.push_back({ PieceColor::black, PieceType::knight, 7, 6 });
	boardArray[63] = BLACK_ROOK;
	//pieces.push_back({ PieceColor::black, PieceType::rook, 7, 7 });

	for (auto column = 0; column < 8; ++column) {
		boardArray[48 + column] = BLACK_PAWN;
		pieces.push_back({ PieceColor::black, PieceType::pawn, 6, column });
	}

	for (auto row = 2; row < 6; ++row) {
		for (auto column = 0; column < 8; ++column) {
			boardArray[(8 * row) + column] = ' ';
		}
	}

	// Initialize boardType array
	for (auto square = 0; square < 16; ++square) {
		boardColor[square] = PieceColor::white;
	}
	for (auto square = 16; square < 48; ++square) {
		boardColor[square] = PieceColor::noColor;
	}
	for (auto square = 48; square < 64; ++square) {
		boardColor[square] = PieceColor::black;
	}
	
	
}

Board::~Board()
{
}
