//
// Created by SkyDJul on 22.12.2021.
//

#ifndef THEGAME_ENGINEER_H
#define THEGAME_ENGINEER_H


#include "../abstract/Character.h"

class Engineer: public Character {
    public:
        static const int PRICE;
        Engineer();
        Engineer(Ship* ship);
        void repair();
        void attack(IAttackable*) override;
        void interact(Character*) override;
        void addHp(int) override;
        void subtractHp(int) override;
        void defence(IAttackable*) override;

    private:
        const float STRENGTH = 0.75;
};


#endif //THEGAME_ENGINEER_H
