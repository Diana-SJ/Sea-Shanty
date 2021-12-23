//
// Created by SkyDJul on 22.12.2021.
//

#ifndef THEGAME_PIRATE_H
#define THEGAME_PIRATE_H


#include "../abstract/Character.h"
#include "../abstract/IAttackable.h"

class Pirate: public Character {
    public:
        Pirate();
        Pirate(Ship* ship);
        void attack(IAttackable*) override;
        void interact(Character*) override;
        void addHp(int) override;
        void subtractHp(int) override;
        void defence(IAttackable*) override;

    private:
        const float STRENGTH = 0.6;
};


#endif //THEGAME_PIRATE_H
