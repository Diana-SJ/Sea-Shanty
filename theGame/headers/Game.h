//
// Created by SkyDJul on 21.12.2021.
//

#ifndef THEGAME_GAME_H
#define THEGAME_GAME_H
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "abstract/Character.h"

class Game {
    public:
        static int const STAGES_COUNT;

        Game();
        void run();

    private:
        int stage;
        int kopecks;
        //int shipHp;
        vector<Character*> team;
        Ship* ship;

        void save();
        void load();
        void startGame();
        void startGame(string saveFilePath);
        void dock();
        void startTeamHiring();
        void runStory();
        void runStory(bool);
        void buildSaveFile();
        TCHAR* getSavePath();
        vector<string> getSaved();
        friend class UI;
};


#endif //THEGAME_GAME_H
