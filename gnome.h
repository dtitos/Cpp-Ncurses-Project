#ifndef GNOME_INCLUDED
#define GNOME_INCLUDED
#include <curses.h>

#include "moving.h"

using namespace std;

class Gnome:public Moving{  
	public:
		//Constructor
		Gnome(); 
		void move(vector<vector<char>>&, int, int);
};

#endif