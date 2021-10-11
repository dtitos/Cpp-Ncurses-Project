#include "engine.h"

Engine::Engine(){
	setMapName("level1.txt");
} 

void Engine::Run(){
	ReadBanner();
	init();
	Menu();
	exit();
}

//Setters
void Engine::setMapName(string name){
	name = "Maps/" + name;
	this->MapName=name;
}

//Getters
string Engine::getMapName(){
	return MapName;	
}

void Engine::ReadBanner(){
	fstream mybanner("banner.txt");
    char c;
    vector<char> temp;
    banner.clear();

	while(!mybanner.eof()){
		c=mybanner.get();
		if(c!='\n'){
			temp.push_back(c);
		}else{
			banner.push_back(temp);
			temp.clear();
		}
	}

    this->Bannerx = banner.size();
    this->Bannery = banner[0].size();

    mybanner.close();
}

void Engine::readMap(){
    fstream myfile(MapName);
    char c;
    vector<char> temp;
    map.clear();

	while(!myfile.eof()){
		c=myfile.get();
		if(c!='\n'){
			temp.push_back(c);
		}else{
			map.push_back(temp);
			temp.clear();
		}
	}

    for(int i=0;i<map.size();i++){
    	map[i].pop_back();
    }

    this->Mapy = map.size();
    this->Mapx = map[0].size();

    myfile.close();
}

void Engine::Menu(){
	string choices[4]={"Start","Levels","Highscores","Quit"};
	int choice,highlight=0,xMax,yMax;
	int xspacebannerWindow,yspacebannerWindow,xspacemenu,yspacemenu;
	int lposy,lposx,rposx;

	getmaxyx(stdscr,yMax,xMax); // yMax = 43 && xMax = 195

	lposy=yMax/2-(yMax/3+7)/2-3; //Prints the Menu at the Center of Screen (Y)
	lposx=xMax/2-(xMax/2-6)/2; //Prints the Menu at the Center of Screen (X)
	rposx=xMax/2-9-(xMax/2-9)/2;

	//Create window for input
	WINDOW * bannerWindow = newwin(yMax/3+7,xMax/2-6,lposy,lposx); //yMax-10 = 33 && xMax-30 = 165 
	WINDOW * menuWindow = newwin(3,xMax/2-6,yMax-15,lposx);

	box(bannerWindow,0,0);
	box(menuWindow,0,0);
	refresh();

	keypad(menuWindow,true); //to use arrow keys

	mvwprintw(bannerWindow,0,5,"[The Last Challenge]");
	//mvwprintw(menuWindow,2,xMax-62,"[copyRights Dimitris Titos]");

	for(int i=0;i<Bannerx;i++){
		for(int y=0;y<Bannery;y++){
			mvwaddch(bannerWindow,i+1,y+1,banner[i][y]);
		}
	}

	wrefresh(bannerWindow);
	wrefresh(menuWindow);

	while(1){
		mvwprintw(menuWindow,0,rposx,"[Menu]");
		for(int i=0;i<4;i++){
			if(i==highlight){
				wattron(menuWindow,A_REVERSE);
			}
			mvwprintw(menuWindow,1,i*28+2,choices[i].c_str());
			wattroff(menuWindow,A_REVERSE);
		}
		choice=wgetch(menuWindow);

		switch(choice){
			case KEY_LEFT:
				highlight--;
				if(highlight==-1){
					highlight=0;
				}
				break;
			case KEY_RIGHT:
				highlight++;
				if(highlight==4){
					highlight=3;
				}
				break;
			default:
				break;
		}
		if(choice==10){
			break;
		}
	}
	string tmp = choices[highlight];
	if(!tmp.compare("Start")){
		clear();
		delwin(menuWindow);
		delwin(bannerWindow);
		refresh();
	}
	MenuManager(tmp);
}

void Engine::MenuManager(string choice){
	if(!choice.compare("Start")){
		readMap();
		Game();
		exit();
	}else if(!choice.compare("Levels")){
		LevelsBoard();
	}else if(!choice.compare("Highscores")){
		HighscoresBoard();
	}else if(!choice.compare("Quit")){
		exit();
	}
}

int Engine::ReadLevelsList(){
	string tmp= "ls Maps > listOfLevels.txt";
	const char* command=tmp.c_str();
	int i=0;

	system(command);

	fstream listoflevels("listOfLevels.txt");
    string line;

	while(!listoflevels.eof()){
		getline(listoflevels,line);
		this->levels.push_back(line);
		i++;
	}
    listoflevels.close();

    return i;
}

void Engine::Game(){
	int ch;
	int yMax,xMax;
	bool moved=0;

	getmaxyx(stdscr,yMax,xMax);
	WINDOW * game = newwin(Mapy+2,Mapx+4,yMax/2-(Mapy/2),xMax/2-(Mapx/2)); 
	box(game,0,0);

	wrefresh(game);
	keypad(game,true);
	mvwprintw(game,0,2,"[The Last Challenge]");

	potter.setIcon('P');
	gnome.setIcon('G');
	traal.setIcon('T');

	potter.randInit(map);
	gnome.randInit(map);
	traal.randInit(map);

	diamondsInit();

	do{
		for(int i=0;i<Mapy;i++) {
		    for(int j=0;j<=Mapx;j++) {
		    	if(map[i][j]=='*'){
		    		mvwprintw(game,i+1,j+2,"\u2588");
		    	}else if(map[i][j]=='D'){
		    		mvwprintw(game,i+1,j+2,"\u25C6");
		    	}else{
		    		mvwaddch(game,i+1,j+2,map[i][j]);
		    	}
		    }
		}
		mvwprintw(game,Mapy+1,2,"Score: %d",potter.getScore());
		wrefresh(game);
		do{
			ch=wgetch(game);
			moved=potter.move(ch,map);
		}while((ch!=27 && ch!=32 && ch!=KEY_UP && ch!=KEY_DOWN && ch!=KEY_LEFT && ch!=KEY_RIGHT && ch!=' ') || moved!=1);
		gnome.move(map,potter.getx(),potter.gety());
		traal.move(map,potter.getx(),potter.gety());
		if(gnome.getiisPotterDead()==1 || traal.getiisPotterDead()==1 || potter.getScore()==200){
			break;
		}
	}while(ch!=27);
	clear();
	delwin(game);
	refresh();
	endOfGame();
}

void Engine::endOfGame(){
	int yMax,xMax,potterscore=0;
	char title[40],desc[50],name[10],tmp;

	getmaxyx(stdscr,yMax,xMax);
	WINDOW * results = newwin(6,50,yMax/2-3,xMax/2-(50/2)); 

	potterscore = potter.getScore();

	box(results,0,0);
	wrefresh(results);
	mvwprintw(results,0,2,"[End of Game]");

	if(gnome.getiisPotterDead()==1 || traal.getiisPotterDead()==1){
		strcpy(title,"Game Over!");
		if(gnome.getiisPotterDead()==1){
			strcpy(desc,"You died from Gnome with");
		}else{
			strcpy(desc,"You died from Traal with");
		}
	}else if(potterscore==200){
		strcpy(title,"Congratulations!");
		strcpy(desc,"You won with");
	}

	mvwprintw(results,1,50/2-strlen(title)/2,title);
	mvwprintw(results,2,50/2-strlen(desc)/2-5,"%s %d points",desc,potterscore);
	mvwprintw(results,4,1,"Give your name: ");
	wrefresh(results);

	for(int i=0;i<10;i++){
		tmp=wgetch(results);
		if(tmp==10){
			name[i]='\0';
			break;
		}
		name[i]=tmp;
		mvwaddch(results,4,17+i,name[i]);
		wrefresh(results);
	}

	clear();
	delwin(results);
	refresh();
	hiscores << name << potterscore;
}

void Engine::diamondsInit(){
	int posx,posy,i;

	srand(time(NULL));

	for(i=0;i<potter.getDiamondsInBoard();i++){
		do{
			posx=rand()%(Mapx);
			posy=rand()%(Mapy);
		}while(map[posy][posx]!=' ');
		map[posy][posx]='D';
	}
}

void Engine::LevelsBoard(){
	int yMax,xMax,highlight=0,levelselect,i=0;

	getmaxyx(stdscr,yMax,xMax);
	WINDOW * levelswindow = newwin(yMax/2,xMax/18+4,yMax/4-2,143); 
	box(levelswindow,0,0);

	wrefresh(levelswindow);
	keypad(levelswindow,true); 

	int listSize = ReadLevelsList();

	while(1){
		mvwprintw(levelswindow,0,1,"[Levels]");
		for(i=0;i<listSize;i++){
			if(i==highlight){
				wattron(levelswindow,A_REVERSE);
			}
			mvwprintw(levelswindow,i+1,2,levels[i].c_str());
			wattroff(levelswindow,A_REVERSE);
		}
		levelselect=wgetch(levelswindow);

		switch(levelselect){
			case KEY_UP:
				highlight--;
				if(highlight==-1){
					highlight=0;
				}
				break;
			case KEY_DOWN:
				highlight++;
				if(highlight==listSize-1){
					highlight=listSize-2;
				}
				break;
			default:
				break;
		}
		if(levelselect==10){
			break;
		}
	}

	string SelectedMap = levels[highlight];
	setMapName(SelectedMap);

	wborder(levelswindow, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '); // Erase frame around the window
	wrefresh(levelswindow); // Refresh it (to leave it blank)
	delwin(levelswindow); // and delete
	clear();
	
	Menu();
}	

void Engine::HighscoresBoard(){
	int yMax,xMax;
	char ch;
	getmaxyx(stdscr,yMax,xMax);
	WINDOW * Highscoreswindow = newwin(yMax/2,xMax/9,yMax/4-2,143); 
	box(Highscoreswindow,0,0);

	wrefresh(Highscoreswindow);
	hiscores.readfile();
	
	while(1){
		mvwprintw(Highscoreswindow,0,1,"[Highscores]");
		for(int i=0;i<5;i++){
			mvwprintw(Highscoreswindow,i+1,2,hiscores.getscores(i));
		}
		mvwprintw(Highscoreswindow,19,2,"Press Esc to Exit");
		wrefresh(Highscoreswindow);

  		if((ch = wgetch(Highscoreswindow)) == 27){
  			break;
    	}
	}

	wborder(Highscoreswindow, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '); // Erase frame around the window
	wrefresh(Highscoreswindow); // Refresh it (to leave it blank)
	delwin(Highscoreswindow); // and delete
	clear();

	Menu();
}

void Engine::init(){
	setlocale(LC_ALL, "");
	initscr();
	start_color();
	noecho();
	curs_set(0);
}

void Engine::exit(){
	endwin();
}