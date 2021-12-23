//
// Created by SkyDJul on 22.12.2021.
//

#include "../../headers/characters/Doctor.h"
#include "../../headers/UI/UI.h"
#include <ctime>
#include <conio.h>
int const Doctor::PRICE = 250;
void Doctor::heal(IHealable* patient) {
    srand(time(nullptr));
    int hp = 22 + ( rand() % 11 - 5 );
    patient->addHp(hp);
    UI::clearScreen();
    UI::printMainBar();
    UI::printEnemyBar();
    cout << endl;
    cout << this->toString() << " healed" << endl;
    cout << "Unit health: + " << hp << " hp" << endl;
    UI::requestAnyKey();
}

Doctor::Doctor() : Character(){
    this->gameClass = doctor;
    this->strength = STRENGTH;
}

Doctor::Doctor(Ship* ship) : Character(ship) {
    this->gameClass = doctor;
    this->strength = STRENGTH;
}

void Doctor::attack(IAttackable * enemy) {
    srand(time(nullptr));
    int hit = this->strength * Character::CHARACTER_HIT + (float)( rand() % 11 - 5 );

    enemy->subtractHp(hit);

    int selfHp = this->hp;
    enemy->defence(this);

    int shipDamage = this->ship->damage(this->strength);

    UI::clearScreen();
    UI::printMainBar();
    UI::printEnemyBar();
    cout << endl;
    cout << this->toString() << " attacked: " << endl;
    cout << "Damage given: " << hit << " hp" << endl;
    cout << "Damage received: " << selfHp - this->hp << " hp" << endl;
    cout << "Ship damage: " << shipDamage << "%" << endl;
    UI::requestAnyKey();
}

void Doctor::interact(Character* enemy) {
    bool correct = false;
    char answer;
    while (!correct) {
        UI::clearScreen();
        UI::printMainBar();
        UI::printEnemyBar();
        cout << "Choose what to do with the target: " << endl;
        cout << "1. Attack" << endl;
        cout << "2. Heal" << endl;
        answer = getch();
        if (answer != '1' && answer != '2') {
            continue;
        }
        correct = true;
    }

    switch (answer) {
        case '1': this->attack(enemy); break;
        case '2': this->heal(enemy); break;
    }
}

void Doctor::addHp(int hp) {
    this->hp += hp;
    if (this->hp > 100) this->hp = 100;
}

void Doctor::subtractHp(int hp) {
    this->hp -= hp;
    if (this->hp < 0) this->hp = 0;
}

void Doctor::defence(IAttackable * enemy) {
    int hit = this->strength * Character::CHARACTER_HIT * IAttackable::DEFENCE_COEFFICIENT + (float)( rand() % 6 );
    enemy->subtractHp(hit);
}