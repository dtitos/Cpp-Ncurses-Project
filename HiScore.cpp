#include "HiScore.h"

HiScore::HiScore(){

}

HiScore HiScore::operator<<(const char* username){
	readfile();
    strcpy(tmpusername,username);

    return *this;
}

void HiScore::operator<<(int score){
    tmpscore=score;
    calctopscores();
}

void HiScore::readfile(){
	ifstream myFile ("highscores.bin", ios::in | ios::binary);
	for(int i=0;i<5;i++){
		myFile.read((char*)&username[i],sizeof(username[i]));
		myFile.read((char*)&score[i],sizeof(score[i]));
	}
	myFile.close();
}

void HiScore::calctopscores(){
	int min=score[0],i,pos=-1;

	for(i=0;i<5;i++){
		if(tmpscore>score[i]){
			pos=i;
			min=score[i];
		}
	}
	for(i=0;i<5;i++){
		if(score[i]<min){
			pos=i;
			min=score[i];
		}
	}
	if(pos>=0){
		score[pos]=tmpscore;
		strcpy(username[pos],tmpusername);
		sorthiscores();
		rewritefile();
	}
}

void HiScore::sorthiscores(){
	int i,j,tmp;
	char tmpname[10];

	for(i=0;i<5-1;i++){
		for(j=0;j<5-i-1;j++){
        	if(score[j]<score[j+1]){
        		//swap Scores
            	tmp=score[j];
            	score[j]=score[j+1];
            	score[j+1]=tmp;
            	//swap Names
            	strcpy(tmpname,username[j]);
            	strcpy(username[j],username[j+1]);
            	strcpy(username[j+1],tmpname);
        	}
        }
	}    
}

void HiScore::rewritefile(){
	ofstream HiScorefile("highscores.bin", ios::out | ios::binary);
	for(int i=0;i<5;i++){
		HiScorefile.write((char*)&username[i],sizeof(username[i]));
   	 	HiScorefile.write((char*)&score[i],sizeof(score[i]));
	}
    HiScorefile.close();
}

char* HiScore::getscores(int i){
	char* board;

	sprintf(board,"%s      %d",username[i],score[i]);

	return board;
}

void HiScore::tmpwrite(){

	char user[10]={'N','N','N','N','N','N','N','N','N','N'};
	int s=0;

	ofstream HiScorefile("highscores.bin", ios::out | ios::binary);
	for(int i=0;i<5;i++){
		HiScorefile.write((char*)&user,sizeof(user));
   	 	HiScorefile.write((char*)&s,sizeof(s));
	}
    HiScorefile.close();
}

/* tmpwrite() Results
4e4e 4e4e 4e4e 4e4e 4e4e 0000 0000 4e4e
4e4e 4e4e 4e4e 4e4e 0000 0000 4e4e 4e4e
4e4e 4e4e 4e4e 0000 0000 4e4e 4e4e 4e4e
4e4e 4e4e 0000 0000 4e4e 4e4e 4e4e 4e4e
4e4e 0000 0000
*/