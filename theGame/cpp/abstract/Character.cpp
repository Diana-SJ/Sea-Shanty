//
// Created by SkyDJul on 21.12.2021.
//

#include "../../headers/abstract/Character.h"
#include <ctime>
using namespace std;

const float Character::SHIP_HIT = 10.0;
const float Character::CHARACTER_HIT = 20.0;

const string Character::NAMES[] = { "Alenka",   "Victor",   "Milana",
                                    "Lyosha",   "Dzhahar",  "Igoryok",
                                    "Viktor",   "Polina",   "Mashka",
                                    "Mishka",   "Vladik",   "Kazantip",
                                    "Sofia",    "Marina",   "Pavelo" }; //15

Character::Character() : IHealable() {
    this->hp = 100;
    srand(time(NULL));
    this->name = NAMES[rand() % 15];
}

Character::Character(Ship* ship) : Character() {
    this->ship = ship;
}

string Character::getName() {
    return this->name;
}

Character::GameClass Character::getGameClass() {
    return this->gameClass;
}

string Character::toString() {
    string str;
    str = this->getName() + " [";
    switch (this->getGameClass()) {
        case Character::soldier:
            str += "Soldier";
            break;
        case Character::engineer:
            str += "Engineer";
            break;
        case Character::doctor:
            str += "Doctor";
            break;
        case Character::pirate:
            str += "Pirate";
            break;
        default:
            break;
    }
    str += "]";
    return str;
}