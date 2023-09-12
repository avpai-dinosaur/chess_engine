#include <iostream>
#include <fstream>
#include "Game.h"

using namespace std;

int main() {
	Game game;
	game.board.printBoard(cout);

	char piece;
	int rowInitial;
	char colInitial;
	int rowDestination;
	char colDestination;

	while (true) {
		cout << "Enter piece to move: " << endl;
		cin >> piece >> colInitial >> rowInitial;
		cout << "Enter square to move to: " << endl;
		cin >> colDestination >> rowDestination;
		if (!game.isValidMove(piece, rowInitial, colInitial, rowDestination, colDestination)) {
			cout << "Not a valid move!" << endl;
			continue;
		}
		else {
			game.humanMove(piece, rowInitial, colInitial, rowDestination, colDestination);
		}
		
		game.board.printBoard(cout);
	}
	


	return 0;
}

