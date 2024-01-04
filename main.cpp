#include <iostream>
#include <fstream>
#include "Engine.h"

using namespace std;

int main(int argv, char** argc) {
	if (argv == 1) {
		Engine game;
		char piece;
		int rowInitial;
		char colInitial;
		int rowDestination;
		char colDestination;
		game.perft(game.getCurrentPosition(), 4);
		cout << "Enter move (Ex: P d2 d3): " << endl;
		while (cin >> piece >> colInitial >> rowInitial >> colDestination >> rowDestination) {
			int initial = game.parseUserInput(rowInitial, colInitial, rowDestination, colDestination).first;
			int destination = game.parseUserInput(rowInitial, colInitial, rowDestination, colDestination).second;
			game.move(initial, destination);
			cout << "Enter move (Ex: P d2 d3): " << endl;
		}

		return 0;
	}
	else {
		Engine game;
		char piece;
		int rowInitial;
		char colInitial;
		int rowDestination;
		char colDestination;

		cout << "Enter move (Ex: P d2 d3): " << endl;
		while (cin>> piece >> colInitial >> rowInitial >> colDestination >> rowDestination) {
			int initial = game.parseUserInput(rowInitial, colInitial, rowDestination, colDestination).first;
			int destination = game.parseUserInput(rowInitial, colInitial, rowDestination, colDestination).second;
			game.move(initial, destination);
			cout << "Enter move (Ex: P d2 d3): " << endl;
		}

		return 0;
	}
}

