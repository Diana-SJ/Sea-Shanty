//
// Created by SkyDJul on 22.12.2021.
//

#ifndef THEGAME_IHEALABLE_H
#define THEGAME_IHEALABLE_H


class IHealable {
    public:
        IHealable();
        int getHp();
        virtual void addHp(int) = 0;
    protected:
        int hp;
};


#endif //THEGAME_IHEALABLE_H
