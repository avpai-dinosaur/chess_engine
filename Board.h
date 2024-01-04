#include <string>
#include <iostream>
#include <vector>
#include "constants.h"

using namespace std;

class Board
{
private:
	int boardArray[64];
	int distanceToLeftEdge[64];
	int distanceToRightEdge[64];
	int distanceToTopEdge[64];
	int distanceToBottomEdge[64];
	bool attackedSquaresWhite[64];
	bool attackedSquaresBlack[64];

	bool blackQueenSideCastle;
	bool blackKingSideCastle;
	bool whiteQueenSideCastle;
	bool whiteKingSideCastle;

	int enPassantSquare;

	// helpful pre-processing functions
	void calculateDistanceArrays();
	void calculateAttackedSquaresWhite();
	void calculateAttackedSquaresBlack();
	void boardInit();

	// Helper functions to convert between
	// char representing piece and integer value of piece
	int charToPiece(char symbol);
	char printPiece(int piece);

	// Helper functions to deal with piece movement
	int getPieceColor(int position);
	bool isFriendly(int color, int destination);
	bool isAttackedSquare(int color, int square);	

	// Helper functions to generate valid squares of each piece type
	void generateAlongDirection(vector<int>& validSquares, int color, int position, int offset, int *distanceMatrix, string mode);
	vector<int> generateRaySlidingPiece(int piece, int position, string mode);
	vector<int> generateRayHorse(int color, int position, string mode);
	vector<int> generateRayPawn(int color, int position);
	vector<int> generateRayKing(int color, int position, string mode);

public:
	Board();
	Board(const string& FEN);
	Board(const Board& board);
	~Board();
	
	void printBoard(ostream &os);
	void movePiece(int initial, int destination);
	int getPiece(int position);

	// returns array of all squares a given piece can move to
	vector<int> generateValidSquares(int piece, int position);

	// determines if a move is valid
	bool isValidMove(int initial, int destination);

	// Generates a vector of all pieces on the board of the given color
	// Vector entires pairs ordered like (piece, position)
	vector<pair<int, int>> generatePieceVector(int color);
};