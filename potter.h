#ifndef POTTER_INCLUDED
#define POTTER_INCLUDED
#include <curses.h>

#include "moving.h"

using namespace std;

class Potter:public Moving{
	//attributes
	protected:
		int DiamondsScore; 
		int DiamondsInBoard; 
		bool isPergaminInitialized;
		int PergaminInBoard;
	public:
		//Constructor
		Potter();
		//Func with rules of moving
		bool move(int,vector<vector<char>>&);
		//Func to grab items
		void grabDiamond();
		void grabPergamin();
		//Getters
		int getScore();
		int getDiamondsInBoard();
		//Initialize Pergamin
		void InitializePergamin(vector<vector<char>> &);
};

#endif