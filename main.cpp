#include <iostream>
#include <fstream>
#include "Game.h"

using namespace std;

int main() {
	const string FEN = "rnbqk1r/ppp1pppp/5n2/3p4/3P4/5N2/PPP1PPPP/RNBQKB1R w KQkq - 0 3";
	Game game(FEN);
	
	char piece;
	int rowInitial;
	char colInitial;
	int rowDestination;
	char colDestination;

	while (true) {
		cout << "Enter move (Ex: P d2 d3): " << endl;
		cin >> piece >> colInitial >> rowInitial;
		cin >> colDestination >> rowDestination;
		game.move(rowInitial, colInitial, rowDestination, colDestination);
	}
	
	return 0;
}

