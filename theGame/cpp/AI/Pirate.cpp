//
// Created by SkyDJul on 22.12.2021.
//

#include "../../headers/AI/Pirate.h"
#include "../../headers/UI/UI.h"
#include <ctime>
void Pirate::attack(IAttackable * enemy) {
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

Pirate::Pirate() : Character() {
    this->gameClass = pirate;
    this->strength = STRENGTH;
}

Pirate::Pirate(Ship* ship) : Character(ship){
    this->gameClass = pirate;
    this->strength = STRENGTH;
}

void Pirate::interact(Character*) {

}

void Pirate::defence(IAttackable * enemy) {
    int hit = this->strength * Character::CHARACTER_HIT * IAttackable::DEFENCE_COEFFICIENT + (float)( rand() % 6 );
    enemy->subtractHp(hit);
}

void Pirate::addHp(int hp) {
    this->hp += hp;
    if (this->hp > 100) this->hp = 100;
}

void Pirate::subtractHp(int hp) {
    this->hp -= hp;
    if (this->hp < 0) this->hp = 0;
}