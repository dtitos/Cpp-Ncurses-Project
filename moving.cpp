#include "moving.h"
#include "potter.h"
#include "gnome.h"
#include "traal.h"

Moving::Moving(){
	this->isPotterDead=false;
	this->holdItem=0;
}

void Moving::randInit(vector<vector<char>> &map){
	int posx,posy;

	srand(time(NULL));

	do{
		posx=rand()%(map[0].size());
		posy=rand()%(map.size());
	}while(map[posy][posx]!=' ');
	map[posy][posx]=icon;
	this->x=posx;
	this->y=posy;
}

void Moving::setIcon(char icon){
	this-> icon = icon;
}

void Moving::setisPotterDead(bool isPotterDead){
	this-> isPotterDead=isPotterDead;
}

bool Moving::move(int move,vector<vector<char>>&){
	return 1;
}

void Moving::move(vector<vector<char>>&, int ,int){

}

int Moving::getx(){
	return x;
}

int Moving::gety(){
	return y;
}

bool Moving::getiisPotterDead(){
	return isPotterDead;
}

void Moving::solveMazeUtil(vector<vector<char>> &map,int monsterx, int monstery, int potterx, int pottery, int **solve){
	bool found=false;
	int tmp=1;

	solve[pottery][potterx]=-1;
	solve[monstery][monsterx]=-2;

	//Up
	if(solve[pottery-1][potterx]==-2){
		found=true;
	}else if(solve[pottery-1][potterx]!=0){
		solve[pottery-1][potterx]=1;
	}

	//Down
	if(solve[pottery+1][potterx]==-2){
		found=true;
	}else if(solve[pottery+1][potterx]!=0){
		solve[pottery+1][potterx]=1;
	}

	//Left
	if(solve[pottery][potterx-1]==-2){
		found=true;
	}else if(solve[pottery][potterx-1]!=0){
		solve[pottery][potterx-1]=1;
	}

	//Right
	if(solve[pottery][potterx+1]==-2){
		found=true;
	}else if(solve[pottery][potterx+1]!=0){
		solve[pottery][potterx+1]=1;
	}

	while(!found){
		for(int i=0;i<map.size();i++){
			for(int j=0;j<map[0].size();j++){
				if(solve[i][j]==tmp){
					if(solve[i-1][j]==-2){
						found=true;
					}else if(solve[i-1][j]==-3){
						solve[i-1][j]=tmp+1;
					}

					if(solve[i+1][j]==-2){
						found=true;
					}else if(solve[i+1][j]==-3){
						solve[i+1][j]=tmp+1;
					}

					if(solve[i][j-1]==-2){
						found=true;
					}else if(solve[i][j-1]==-3){
						solve[i][j-1]=tmp+1;
					}

					if(solve[i][j+1]==-2){
						found=true;
					}else if(solve[i][j+1]==-3){
						solve[i][j+1]=tmp+1;
					}
				}
			}
		}
		tmp++;
	}
}