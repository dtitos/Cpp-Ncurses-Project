#ifndef HISCORE_INCLUDED
#define HISCORE_INCLUDED
#include <fstream>
#include <stdio.h>
#include <string.h>

using namespace std;

class HiScore{  
	//attributes
	protected:
		char username[5][10];
		int score[5];
		char tmpusername[10];
		int tmpscore;
	public:
		//Constructor
		HiScore();
		HiScore operator<<(const char*);
		void operator<<(int);
		void calctopscores();
		void readfile();
		void rewritefile();
		char* getscores(int);
		void tmpwrite();
		void sorthiscores();
};

#endif