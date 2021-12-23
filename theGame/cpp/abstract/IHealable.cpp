//
// Created by SkyDJul on 22.12.2021.
//

#include "../../headers/abstract/IHealable.h"

IHealable::IHealable() {
    this->hp = 100;
}

int IHealable::getHp() {
    return  this->hp;
}