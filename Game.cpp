// Assignment : Project 2 - Boggle Solitaire
// File : Game.cpp
// Author : Colin Franceschini
// Description : This is a solitaire boggle game. The user must input rows and characters to change
// the letters position of the grid to make words and accumulate points to win.

#include <iomanip>
#include <ctime>
#include <cstdlib>
#include "Game.h"
#include "ShortWords.h"

const string letters [] = {" ", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",
			   "n", "o", "p", "qu", "r", "s", "t", "u", "v", "w", "x", "y", "z"};

Game::GameSquare::GameSquare ()
{
// This function will initialize the variables what and flag.

	what = 0;
	flag = NONE;
}

void Game::GameSquare::Display (ostream & outs)
{
// This function will display the letter(s) stored in the GameSquare object as well as any
// appropriate flag_type indicators. This function will be called for each GameSquare in the
// grid by the Game::Display function.
	outs << setw (3) << right << letters[what] << ' ';
	
}

Game::Game (const string & T) 
{
// This function will initialize variables used in the game

	title = T;
        numRC = 1;
	numBoards = 0;
        grid = new GameSquare * [3];
	for (int r = 0; r < 3; r++)
        	grid[0] = new GameSquare [3];

//	srand(55);

	srand (time (NULL));
}

Game::~Game ()
{
// This function will delete extra rows in the grid and will also delete the previous grid of the game.

	for (int r = 0; r < numRC+2; r++)
		delete [] grid[r];
	delete [] grid;
}

void Game::Init (int RC, int B)
{
// This function will resize the game and reset all required game variables.

	for (int r = 0; r < numRC+2; r++)
		delete [] grid[r];
	delete [] grid;
        numRC = RC;
	numBoards = B;
	boardsLeft = B;
	firstClickDone = false;
        grid = new GameSquare * [numRC+2];
        for (int r = 0; r < numRC+2; r++)
            grid[r] = new GameSquare [numRC+2];
        FillIn ();
	FindWords (cout);
}

void Game::Reset (ostream & outs)
{
// This function will refill the board with new letters while leaving the 
// players score as is.
	boardsLeft--;
	words.erase(words.begin(), words.end());	
	FillIn();

}

void Game::Instructions (ostream & outs, istream & ins)
{
// This function will automatically print the instruction  message at the beginning
// of execution and when the user enters 'I' as the column/row identifier 

	system ("clear");
	outs << endl << "Welcome! Get Ready to play " 
	<< title << "!" <<  endl;
	outs << "\nYour ultimate objective is to find as many words as possible";
	outs << " and to get 100 points" << endl;
	system ("sleep 4");
}

void Game::Display (ostream & outs)
{
// This function will display the current status of the game in an ASCII format.

	system ("clear");
	int r, c;
	outs << endl << title << endl;
	outs << endl;
	outs << "     ";
	for (c = 0; c < numRC; c++)
		outs << "   " << char(c + 'A') << "  ";
	outs << endl;
	outs << "     ";
	for (c = 0; c < numRC; c++)
		outs << "+-----";
	outs << "+" << endl;
	for (r = 1; r <= numRC; r++)
	{
		outs << setw(3) << r << "  |";
		for (c = 1; c <= numRC; c++)
		{	
			grid [r][c].Display (outs);
			outs << " |";
		}
		outs << setw(3) << r << endl;
	        outs << "     ";
		for (c = 0; c < numRC; c++)
		{
			outs << "+-----";
		}
	
	outs << "+" << endl;
	}
	outs << "     ";
	for (c = 0; c < numRC; c++)
		outs << "   " << char(c + 'A') << "  ";
	outs << endl;
	FindWords(cout);
	outs << "\n\nWords found: " << words.size() << endl;
	int i = 0;
	while (i < words.size())
	{

		if (i % 7 == 0) // this loop will print only 5 words found per line
			{
				cout << "\n";
			}
			outs << words[i]<< " ";
			i++;
	}
	cout << endl;
	int score = words.size() * 10;
	cout << "\nScore: " << score  << "                    " << "Boards left: " << boardsLeft << endl;
		
}			


void Game::FillIn ()
{
// This function will fill in the board with random letters

	int start = 7;
	for (int r = 1; r <= numRC; r++)
		for (int c = 1; c <= numRC; c++)
		{
			grid[r][c].what = rand() % 26 + 1 ; ++start;
		}
}

bool Game::Click (char row, char col, ostream & outs)
{
// This function will check if the players click is valid

	outs << "Click at: " << col << row << endl;
	int r = row - '0';
	int c = col - 'a' + 1;
	if (r < 1 || r > numRC || c < 1 || c > numRC)
		return false;
	if (!firstClickDone)
		return FirstClick (r, c, outs);
	return SecondClick (r, c, outs);
}

bool Game::FirstClick (int row, int col, ostream & outs)
{
// This function will save the location of the user's click
	clickedRow1 = row;
	clickedCol1 = col;
	firstClickDone = true;
	return true;	
}

bool Game::SecondClick (int row, int col, ostream & outs)
{
// This function will move the tiles and update the game
	clickedRow2 = row;
	clickedCol2 = col;
	firstClickDone = false;
	words.clear();
	GameSquare temp = grid[clickedRow1][clickedCol1];
	grid[clickedRow1][clickedCol1] = grid[clickedRow2][clickedCol2];
	grid[clickedRow2][clickedCol2] = temp;
	FindWords(cout);
	return true;

}

void Game::Message (game_states state, ostream & outs)
{
// This function will display a message when the state of the game is changed (Winner, Loser, or Quitter)

	string message;
	switch (state)
	{
		case WINNER:
			message = "YOU ROCK AT THIS GAME!"; break;
		case LOSER: 
			message = "YOU SUCk AT THIS GAME!"; break;
		case QUITTER:
			message = "YOU QUITTER!"; break;
	}
	if (score == 100)
        	state = WINNER;
        if (boardsLeft == 0)
                state = LOSER;
	outs << "\nScore: " << score << endl;
	outs << message << endl;
}

game_states Game::Done () 
{
// This function will return true if the game has been completed and false if
// it has not.
	if (boardsLeft < 0)
		return LOSER;
	if (words.size() >= 5)
		return WINNER;
	return GO;
}

bool IsWord (string maybe)
{

// This function will check to see if all the words found on the board are real,
// legal words. It will return false if it is not and true if it is.
	
	int first = 0;
	int last = NUMWORDS-1;
	while ((last - first)>= 0)
	{
		int middle = (first + last) / 2;
		if (words[middle] == maybe)
			return true;
		if (maybe < words[middle])
			last = middle-1;
		else
			first = middle+1;
	}

	return false;
}



int Game::FindWords (ostream & outs)	
{
// This function will find all legal words in the current board and display them. 
// It will look for words that are only in the same column, row, or on a diagnol.
        string one = "";
        string two = "";
	int count = 0;
        int r;
        int c;
	// vertical
	for (c = 1; c <= numRC; c++)
	{	
		for (r  = 1; r <= numRC; r++)
                {
                        // forwards
			one += letters[grid[r][c].what];
                        // backwards
			two = letters[grid[r][c].what]+two;
		}
		count += FindWordsInString(one);
		count += FindWordsInString(two);              
		one = "";
		two = "";
	}
	// horizontal
	for (r = 1; r <= numRC; r++)
	{
		for (c  = 1; c <= numRC; c++)
		{
			one += letters[grid[r][c].what];//forwards
			two = letters[grid[r][c].what]+two;//backwards	
		}
		count+= FindWordsInString(one);
		count+= FindWordsInString(two);
		one = "";
		two = "";
	}
	// diagnol left to right bottom
	for (r = 1; r <= numRC; r++)
	{
        	int r2 = r;                
		for (c = 1; c <= numRC && r2 <= numRC; c++)
		{
			
			one += letters[grid[r2][c].what]; //forwards
			two = letters[grid[r2][c].what]+two; //backwards
       			r2++;	
		}
		count+= FindWordsInString(one);
		count+= FindWordsInString(two);
		one = "";
		two = "";
	}
	// diagnol left to right top	
        for (c = 1; c <= numRC; c++)
        {
                int c2 = c;
                for (r = 1; r <= numRC && c2 <= numRC; r++)
                {

                        one += letters[grid[r][c2].what]; //forwards
			two  = letters[grid[r][c2].what]+two;//backwards
                        c2++;
                }
		count+= FindWordsInString(one);
		count+= FindWordsInString(two);
                one = "";
                two = "";	
	} 
}

int Game::FindWordsInString (const string & line)
{
// This function checks the substrings for real, legal words. 
        int count = 0;
	string ss = "";
	for (int start = 0; start < line.length(); start++)
        {
                for (int len = 3; len < line.length(); len++)
                {        
                        string ss = line.substr(start, len);
                        if (IsWord(ss) && IsDuplicate(ss))
                        {
				words.push_back(ss);
	         	}
        	      	count++;
		}                       
        } 
	return count;
}

bool Game::IsDuplicate(string maybe)
{
// This function checks to make sure duplicates are no duplicate words.
	for (int i = 0; i < words.size(); i++)
        {
        	if (words[i] == maybe)
                {
			return false ;
                }

	}
	return true;
}
