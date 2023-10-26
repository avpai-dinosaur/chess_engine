#include <iostream>
#include <fstream>
#include "Game.h"

using namespace std;

int main(int argv, char** argc) {
	Game game;
	if (argv == 2) {
		const string FEN = argc[1];
		game = Game(FEN);
	}
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

