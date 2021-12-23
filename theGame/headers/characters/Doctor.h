//
// Created by SkyDJul on 22.12.2021.
//

#ifndef THEGAME_DOCTOR_H
#define THEGAME_DOCTOR_H


#include "../abstract/Character.h"

class Doctor: public Character {
    public:
        static const int PRICE;
        Doctor();
        Doctor(Ship* ship);
        void heal(IHealable*);
        void attack(IAttackable*) override;
        void interact(Character*) override;
        void addHp(int) override;
        void subtractHp(int) override;
        void defence(IAttackable*) override;

    private:
        const float STRENGTH = 0.5;
};


#endif //THEGAME_DOCTOR_H
