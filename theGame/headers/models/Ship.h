//
// Created by SkyDJul on 22.12.2021.
//

#ifndef THEGAME_SHIP_H
#define THEGAME_SHIP_H


#include "../abstract/IHealable.h"

class Ship: public IHealable {
    public:
        Ship();
        void addHp(int) override;
        int damage(int strength);
    //private:

    friend class Game;

};


#endif //THEGAME_SHIP_H
