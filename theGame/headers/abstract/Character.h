//
// Created by SkyDJul on 21.12.2021.
//

#ifndef THEGAME_CHARACTER_H
#define THEGAME_CHARACTER_H

#include <iostream>
#include <vector>

class IAttackable;
#include "IAttackable.h"
#include "IHealable.h"
#include "../models/Ship.h"

using namespace std;

class Character: public IAttackable, public IHealable {

    const static string NAMES[];

    public:
        static float const CHARACTER_HIT;
        static float const SHIP_HIT;
        enum GameClass { soldier, doctor, engineer, pirate };
        //Character();

        Character(Ship*);

        string getName();
        GameClass getGameClass();

        string toString();
        virtual void interact(Character*) = 0;

        //virtual void substractHp(int) override = 0;

    protected:
        Character();
        GameClass gameClass;
        Ship* ship;

    private:
        string name;
        //int hp;

        friend class Game;
};



#endif //THEGAME_CHARACTER_H
