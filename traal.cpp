#include "traal.h"

Traal::Traal():Moving(){

}

void Traal::move(vector<vector<char>> &map, int potterx, int pottery){
	int **solve=new int *[map.size()];
	int i,movex,movey;
	bool flagend=false;
	char itemicon=' ';

	for(i=0;i<map.size();i++)
		solve[i]=new int [map[0].size()];

	for(i=0;i<map.size();i++) {
		for(int j=0;j<map[0].size();j++) {
			if(map[i][j]=='*'){
				solve[i][j]=0;
			}else{
				solve[i][j]=-3;
			}
		}
	}

	solveMazeUtil(map, x, y, potterx, pottery, solve);

	//Checks if Potter is in 1 Cell Distance
	if(solve[y-1][x]==-1){
		map[y-1][x]=icon;
		map[y][x]=' ';
		flagend=true;
	}else if(solve[y+1][x]==-1){
		map[y+1][x]=icon;
		map[y][x]=' ';
		flagend=true;
	}else if(solve[y][x-1]==-1){
		map[y][x-1]=icon;
		map[y][x]=' ';
		flagend=true;
	}else if(solve[y][x+1]==-1){
		map[y][x+1]=icon;
		map[y][x]=' ';
		flagend=true;
	}

	if(flagend==true){
		setisPotterDead(true);
	}

	if(flagend==false){
		//Initialization of 1st Valid move
		if(solve[y-1][x]>0){
			movex=x; //Up
			movey=y-1;
		}else if(solve[y+1][x]>0){
			movex=x; //Down
			movey=y+1;
		}else if(solve[y][x-1]>0){
			movex=x-1; //Left
			movey=y;
		}else if(solve[y][x+1]>0){
			movex=x+1; //Right
			movey=y;
		}

		//Finds the faster way to Potter
		if((solve[y+1][x]>0) && (solve[y+1][x]<solve[movey][movex])){
			movex=x; //Down
			movey=y+1;
		}
		if((solve[y][x-1]>0) && (solve[y][x-1]<solve[movey][movex])){
			movex=x-1; //Left
			movey=y;
		}
		if((solve[y][x+1]>0) && (solve[y][x+1]<solve[movey][movex])){
			movex=x+1; //Right
			movey=y;
		}

		if(map[movey][movex]=='G'){
			(void)0;
		}else{
			if(holdItem==1){
				holdItem-=1;
				itemicon='D';
			}else if(holdItem==2){
				map[movey][movex]=icon;
				holdItem-=2;
				itemicon='I';
			}

			if(map[movey][movex]=='D'){
				holdItem+=1;
				map[movey][movex]=icon;
				map[y][x]=itemicon;
			}else if(map[movey][movex]=='I'){
				holdItem+=2;
				map[movey][movex]=icon;
				map[y][x]=itemicon;
			}else{
				map[movey][movex]=icon;
				map[y][x]=itemicon;
			}
			y=movey;
			x=movex;
		}
	}		

    for(int i=0;i<map.size();i++)
		delete[] solve[i];

	delete[] solve;
}