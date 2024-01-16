#include <iostream>
#include <fstream>
#include "Engine.h"

using namespace std;

int main(int argv, char **argc)
{
	Engine game;
	char piece;
	int rowInitial;
	char colInitial;
	int rowDestination;
	char colDestination;
	cout << "Enter move (Ex: P d2 d3): " << endl;
	while (cin >> piece >> colInitial >> rowInitial >> colDestination >> rowDestination)
	{
		pair<int, int> move = game.parseUserInput(rowInitial, colInitial, rowDestination, colDestination);
		game.move(move.first, move.second);
		cout << "Enter move (Ex: P d2 d3): " << endl;
	}
	return 0;
}
