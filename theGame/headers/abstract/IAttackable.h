//
// Created by SkyDJul on 22.12.2021.
//

#ifndef THEGAME_IATTACKABLE_H
#define THEGAME_IATTACKABLE_H

class IAttackable {

    public:
        const float DEFENCE_COEFFICIENT = 0.33;

        virtual void attack(IAttackable*) = 0;
        virtual void defence(IAttackable*) = 0;
        virtual void subtractHp(int) = 0;

    protected:
        float strength;
};


#endif //THEGAME_IATTACKABLE_H
