#ifndef TRAAL_INCLUDED
#define TRAAL_INCLUDED
#include <curses.h>

#include "moving.h"

using namespace std;

class Traal:public Moving{  
	public:
		//Constructor
		Traal();   
		void move(vector<vector<char>>&, int, int);
};

#endif