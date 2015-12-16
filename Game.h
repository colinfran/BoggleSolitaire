// Title: Game.h 
// Author: Colin Franceschini
// Description: This header file is used to hold declarations for other files to use throughout the game.

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
using namespace std;

enum game_states { GO, WINNER, LOSER, QUITTER };
enum flag_types { NONE, SELECTED, USED };

class Game
{
    public:
        Game (const string & T);
        ~Game ();
	void Init (int RC, int B);
	void Reset (ostream & outs);
        void Instructions (ostream & outs, istream & ins);
        void Display (ostream & outs);
        bool Click (char row, char col, ostream & outs);
        void Message (game_states state, ostream & outs);
	game_states Done ();

    private:
        void FillIn ();
	bool IsDuplicate (string maybe);
	int FindWords ( ostream & outs);
        int FindWordsInString (const string & line);
	bool FirstClick (int row, int col, ostream & outs);
        bool SecondClick (int row, int col, ostream & outs);
	struct GameSquare
	{
	    GameSquare ();
	    void Display (ostream & outs);
	    int what;
	    flag_types flag;
	};
        GameSquare ** grid;
	string title;
        int numRC;
	int numBoards;
	vector <string> words;

    // The following are suggested useful variables
	int boardsLeft;
	int previousPoints;
	int currentPoints;
	int score;
	int clickedRow1, clickedCol1;
	int clickedRow2, clickedCol2;
	bool firstClickDone;
};

#endif
