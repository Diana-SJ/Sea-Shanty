//
// Created by SkyDJul on 22.12.2021.
//

#ifndef THEGAME_SOLDIER_H
#define THEGAME_SOLDIER_H


#include "../abstract/Character.h"

class Soldier: public Character {
    public:
        static const int PRICE;
        const int GUN_HIT = 40;
        Soldier();
        Soldier(Ship* ship);
        void shoot(IAttackable*);
        void attack(IAttackable*) override;
        void interact(Character*) override;
        void addHp(int) override;
        void subtractHp(int) override;
        void defence(IAttackable*) override;

    private:
        const float STRENGTH = 1.0;
};


#endif //THEGAME_SOLDIER_H
