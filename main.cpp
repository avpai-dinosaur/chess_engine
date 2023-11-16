#include <iostream>
#include <fstream>
#include "Game.h"

using namespace std;

int main(int argv, char** argc) {
	if (argv == 1) {
		Game game;
		char piece;
		int rowInitial;
		char colInitial;
		int rowDestination;
		char colDestination;
		game.perft(game.history.front(), 4);
		cout << "Enter move (Ex: P d2 d3): " << endl;
		while (cin >> piece >> colInitial >> rowInitial >> colDestination >> rowDestination) {
			game.move(rowInitial, colInitial, rowDestination, colDestination);
			cout << "Enter move (Ex: P d2 d3): " << endl;
		}

		return 0;
	}
	else {
		ifstream fin;
		fin.open(argc[1]);

		if (!fin.is_open()) {
			cout << "failed to open " << argc[1] << endl;
			return 1;
		}

		string FEN;
		std::getline(fin, FEN);
		Game game(FEN);

		char piece;
		int rowInitial;
		char colInitial;
		int rowDestination;
		char colDestination;

		cout << "Enter move (Ex: P d2 d3): " << endl;
		while (fin >> piece >> colInitial >> rowInitial >> colDestination >> rowDestination) {
			game.move(rowInitial, colInitial, rowDestination, colDestination);
			cout << "Enter move (Ex: P d2 d3): " << endl;
		}

		return 0;
	}
}

