//
// Created by V1T4L9 on 21.12.2021.
//

#ifndef THEGAME_UI_H
#define THEGAME_UI_H
#include <iostream>
#include "../abstract/Character.h"
#include "../Game.h"

using namespace std;

class UI { // user interface
    public:
        static Game* game;
        static vector<Character*> enemyTeam;
        static void setGame(Game*);
        static void setEnemyTeam(vector<Character*>&);
        static void printMainMenu();
        static void clearScreen();
        static void requestAnyKey();
        static char requestKey();
        static void tellStory();
        static void printEnemyBar();
        static void printEnemyBar(vector<Character*> &);
        static void printMainBar();
        static void waitForEnemy();
        static bool approvedDock();
        static void printPreambula(int);
        static void printMainBar(int, int, vector<Character*> &);
};


#endif //THEGAME_UI_H
