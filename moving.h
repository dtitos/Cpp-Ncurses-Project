#ifndef MOVING_INCLUDED
#define MOVING_INCLUDED
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <vector>
#include <iostream>
#include <stdlib.h>

using namespace std;

class Moving{  
	//attributes
	protected:
		char icon;
		int y;
		int x;
		bool isPotterDead;
		int holdItem; //1=Diamond 2=Pergamin
	public:
		//Constructor
		Moving();
		void randInit(vector<vector<char>>&);
		//Setters
		void setIcon(char);
		void setisPotterDead(bool);
		//Getters
		int getx();
		int gety();
		bool getiisPotterDead();
		//Moving Player
		virtual bool move(int,vector<vector<char>>&);
		virtual void move(vector<vector<char>>&, int, int);
		void solveMazeUtil(vector<vector<char>>&,int , int, int, int , int **);
		//Other
};

#endif