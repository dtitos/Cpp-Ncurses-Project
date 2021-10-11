#ifndef ENGINE_INCLUDED
#define ENGINE_INCLUDED
#define KEY_ENTER 0x157
#include <string>
#include <locale.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <ncurses.h>
#include <cstring>

#include "moving.h"
#include "potter.h"
#include "gnome.h"
#include "traal.h"
#include "HiScore.h"


using namespace std;

class Engine{   
    //attributes   
    protected:             
      	string MapName;
        vector<vector<char>> map;
        int Mapx;
        int Mapy;
        vector<vector<char>> banner;
        int Bannerx;
        int Bannery;
        vector<string> levels;
        Potter potter;
        Gnome gnome;
        Traal traal;
        HiScore hiscores;
    public:
        //Constructor
        Engine();
        //Root Function
        void Run();
        //Ncurses Open-Close
        void init();
        void exit();
        //Setters
      	void setMapName(string name);
      	//Getters
        string getMapName();
        //Functions for Map
      	void readMap();
        int ReadLevelsList();
        //Functions for Menu
        void Menu();
        void ReadBanner();
        void MenuManager(string choice);
        void LevelsBoard();
        void HighscoresBoard();
        //Functions for Game
        void Game();
        void diamondsInit();
        void endOfGame();
};

#endif