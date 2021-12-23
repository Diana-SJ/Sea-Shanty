//
// Created by SkyDJul on 22.12.2021.
//

#include "../../headers/models/Ship.h"
#include "../../headers/abstract/Character.h"
#include <ctime>
#include <cstdlib>

Ship::Ship() : IHealable() {

}

void Ship::addHp(int hp) {
    this->hp += hp;
    if (this->hp > 100) this->hp = 100;
}

int Ship::damage(int strength) {
    srand(time(nullptr));

    int damage = strength * Character::SHIP_HIT + rand() % 10;
    this->hp -= damage;
    return damage;
}