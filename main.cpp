#include <iostream>
#include <fstream>
#include "Game.h"

using namespace std;

int main() {
	Game game;
	
	char piece;
	int rowInitial;
	char colInitial;
	int rowDestination;
	char colDestination;

	game.start();
	while (true) {
		cout << "Enter move (Ex: P d2 d3): " << endl;
		cin >> piece >> colInitial >> rowInitial;
		cin >> colDestination >> rowDestination;
		// if (!game.isValidMove(piece, rowInitial, colInitial, rowDestination, colDestination)) {
		// 	cout << "Not a valid move!" << endl;
		// 	continue;
		// }
		// else {
		// 	game.humanMove(piece, rowInitial, colInitial, rowDestination, colDestination);
		// }
		game.move(piece, rowInitial, colInitial, rowDestination, colDestination);
	}
	
	return 0;
}

