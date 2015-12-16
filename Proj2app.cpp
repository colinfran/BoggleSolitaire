// File : Proj2app.cpp
// Description : This is the driver program for a "Solitaire Boggle Game".
// 		 The main function included here will accept input from
//		 the user (player) and will call the appropriate functions 
//		 from the Game class.

#include <iostream>
#include "SetLimits.h"
#include "Game.h"
using namespace std;

int main ()
{
    SetLimits();
    char play = 'y';
    int size = 4, boards = 3;
    Game game ("Colin Franceschini's Amazing Boggle Game");
    game.Instructions (cout, cin);
    while (tolower (play) == 'y')
    {
	game.Init(size, boards);
	game_states state = GO;
	while (state == GO)
	{
		char col = ' ', row = ' ';
		string rest;
		game.Display (cout);
		cout << "\nEnter column letter and row number\n";
		cout << "or enter n for a new board\n";
		cout << "or enter i for instructions\n";
		cout << "or enter q to quit: ";
		cin >> col;
		col = tolower (col);
		if (col == 'q')
			state = QUITTER;
		else
		{
			if (col == 'i')
				game.Instructions (cout, cin);
			else if (col == 'n')
				game.Reset (cout);
			else
			{
				cin >> row;
				while (game.Click(tolower (row), col, cout) == false)
				{
					cout << "Invalid selection; try again: ";
					cin >> col >> row;
				}
			}
			getline (cin, rest);
			cin.clear();
			state = game.Done();
		}
	}
	game.Message (state, cout);
	if (state == WINNER)
	{
		size = size < 6 ? size + 1 : size;
		boards = boards > 1 ? boards - 1 : boards;
	}
	cout << "Would you like to play again (y/n)? ";
	cin >> play;
	cin.clear ();
    }
    cout << endl;
    return 0;
}
