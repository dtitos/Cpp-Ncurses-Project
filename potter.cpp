#include "potter.h"

Potter::Potter():Moving(){
	this->DiamondsScore=0;
	this->DiamondsInBoard=10;
	this->isPergaminInitialized=false;
	this->PergaminInBoard=1;
}

bool Potter::move(int move,vector<vector<char>> &map){
	bool moved=0;

	switch(move){
		case KEY_UP:
			if(map[y-1][x]==' '){
				map[y][x]=' ';
				map[y-1][x]=icon;
				y-=1;
				moved=1;
			}else if(map[y-1][x]=='D'){
				map[y][x]=' ';
				map[y-1][x]=icon;
				y-=1;
				grabDiamond();
				moved=1;
			}else if(map[y-1][x]=='I'){
				map[y][x]=' ';
				map[y-1][x]=icon;
				y-=1;
				grabPergamin();
				moved=1;
			}
			break;
		case KEY_DOWN:
			if(map[y+1][x]==' '){
				map[y][x]=' ';
				map[y+1][x]=icon;
				y+=1;
				moved=1;
			}else if(map[y+1][x]=='D'){
				map[y][x]=' ';
				map[y+1][x]=icon;
				y+=1;
				grabDiamond();
				moved=1;
			}else if(map[y+1][x]=='I'){
				map[y][x]=' ';
				map[y+1][x]=icon;
				y+=1;
				grabPergamin();
				moved=1;
			}
			break;
		case KEY_LEFT:
			if(map[y][x-1]==' '){
				map[y][x]=' ';
				map[y][x-1]=icon;
				x-=1;
				moved=1;
			}else if(map[y][x-1]=='D'){
				map[y][x]=' ';
				map[y][x-1]=icon;
				x-=1;
				grabDiamond();
				moved=1;
			}
			else if(map[y][x-1]=='I'){
				map[y][x]=' ';
				map[y][x-1]=icon;
				x-=1;
				grabPergamin();
				moved=1;
			}
			break;
		case KEY_RIGHT:
			if(map[y][x+1]==' '){
				map[y][x]=' ';
				map[y][x+1]=icon;
				x+=1;
				moved=1;
			}else if(map[y][x+1]=='D'){
				map[y][x]=' ';
				map[y][x+1]=icon;
				x+=1;
				grabDiamond();
				moved=1;
			}else if(map[y][x+1]=='I'){
				map[y][x]=' ';
				map[y][x+1]=icon;
				x+=1;
				grabPergamin();
				moved=1;
			}
			break;
		case ' ':
			moved=1;
	}
	if(DiamondsInBoard==0 && isPergaminInitialized==false){
		InitializePergamin(map);
		isPergaminInitialized=true;
	}
	return moved;
}

void Potter::grabDiamond(){
	DiamondsScore+=10;
	DiamondsInBoard--;
}

void Potter::grabPergamin(){
	DiamondsScore+=100;
	PergaminInBoard--;
}

int Potter::getScore(){
	return DiamondsScore;
}

int Potter::getDiamondsInBoard(){
	return DiamondsInBoard;
}

void Potter::InitializePergamin(vector<vector<char>> &map){
	int posx,posy,i;

	srand(time(NULL));

	do{
		posx=rand()%(map[0].size());
		posy=rand()%(map.size());
	}while(map[posy][posx]!=' ');
	map[posy][posx]='I';
}