#include <iostream>
#include <fstream>
#include "Game.h"

using namespace std;

int main() {
	const string FEN = "2k5/8/8/8/8/3B4/K1B5/3R4 w - - 0 1";
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

