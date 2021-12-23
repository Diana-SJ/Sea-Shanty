//
// Created by SkyDJul on 22.12.2021.
//

#include "../../headers/characters/Engineer.h"
#include "../../headers/UI/UI.h"
#include <ctime>
#include <conio.h>
int const Engineer::PRICE = 200;
Engineer::Engineer() : Character() {
    this->gameClass = engineer;
    this->strength = STRENGTH;
}

Engineer::Engineer(Ship* ship) : Character(ship) {
    this->gameClass = engineer;
    this->strength = STRENGTH;
}
void Engineer::repair() {
    srand(time(nullptr));
    int shipHp = 22 + ( rand() % 11 - 5 );
    this->ship->addHp(shipHp);
    UI::clearScreen();
    UI::printMainBar();
    UI::printEnemyBar();
    cout << endl;
    cout << this->toString() << " repaired the ship" << endl;
    cout << "Ship health: + " << shipHp << "%" << endl;
    UI::requestAnyKey();
}

void Engineer::attack(IAttackable * enemy) {

    srand(time(nullptr));
    int hit = this->strength * Character::CHARACTER_HIT + (float)( rand() % 6 );

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
void Engineer::interact(Character* enemy) {
    bool correct = false;
    char answer;
    while (!correct) {
        UI::clearScreen();
        UI::printMainBar();
        UI::printEnemyBar();
        cout << "Choose what to do with the target: " << endl;
        cout << "1. Attack" << endl;
        cout << "2. Steal the hat and close the hole in the ship with it." << endl;
        answer = getch();
        if (answer != '1' && answer != '2') {
            continue;
        }
        correct = true;
    }

    switch (answer) {
        case '1': this->attack(enemy); break;
        case '2': this->repair(); break;
    }
}

void Engineer::addHp(int hp) {
    this->hp += hp;
    if (this->hp > 100) this->hp = 100;
}

void Engineer::subtractHp(int hp) {
    this->hp -= hp;
    if (this->hp < 0) this->hp = 0;
}

void Engineer::defence(IAttackable * enemy) {
    int hit = this->strength * Character::CHARACTER_HIT * IAttackable::DEFENCE_COEFFICIENT + (float)( rand() % 11 - 5 );
    enemy->subtractHp(hit);
}