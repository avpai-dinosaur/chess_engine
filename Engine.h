#include <list>
#include "Board.h"

class Engine
{
private:
	int playerTurn;
	std::list<Board> history;

	int coordinateToArrayNumber(int row, char col);

public:
	Engine();
	Engine(const string &FEN);
	~Engine();

	Board getCurrentPosition();
	pair<int, int> parseUserInput(int rowInitial, int colInitial, int rowDestination, int colDestination);
	bool move(int initial, int destination);
	bool userMove(std::string piece, std::string initial, std::string destination);
	void undoMove();
	int perft(Board board, int depthTarget);
};
