//
// Created by SkyDJul on 22.12.2021.
//

#ifndef THEGAME_BATTLE_H
#define THEGAME_BATTLE_H

#include <vector>
#include "Pirate.h"

class Battle {
    public:
        Battle(vector<Character*> &, Ship*, int);
        void start();
        bool isWon();

    private:
        bool won;
        Ship* ship;
        vector<Character*> allies;
        vector<Character*> enemies;

        void alliesTurn();
        void enemiesTurn();
        Character* pickActor();
        Character* pickTarget();
};


#endif //THEGAME_BATTLE_H
