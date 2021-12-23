//
// Created by SkyDJul on 22.12.2021.
//

#include <conio.h>
#include <ctime>
#include "../../headers/characters/Soldier.h"
#include "../../headers/UI/UI.h"
int const Soldier::PRICE = 150;
Soldier::Soldier() : Character() {
   this->gameClass = soldier;
   this->strength = STRENGTH;
}
Soldier::Soldier(Ship* ship) : Character(ship) {
    this->gameClass = soldier;
    this->strength = STRENGTH;
}

void Soldier::attack(IAttackable *enemy) {
    //во время атаки отнимаем хп у противника (коэф. силы собственной * силу человека в целом)
    // ну и +- 5 хп
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

void Soldier::defence(IAttackable * enemy) {
    int hit = this->strength * Character::CHARACTER_HIT * IAttackable::DEFENCE_COEFFICIENT + (float)( rand() % 11 - 5 );
    enemy->subtractHp(hit);
}

void Soldier::shoot(IAttackable *enemy) {
    // стреляет с 80% вероятностью успеха
    srand(time(nullptr));
    int chance = rand() % 100 + 1;
    bool hit = false;
    if (chance > 20) {
        enemy->subtractHp(GUN_HIT);
        hit = true;
    }
    int shipDamage = this->ship->damage(this->strength);
    UI::clearScreen();
    UI::printMainBar();
    UI::printEnemyBar();
    cout << endl;
    cout << this->toString() << " shoot: " << endl;
    cout << "Damage given: " << GUN_HIT << " hp" << endl;
    cout << "Damage received: 0 hp" << endl;
    cout << "Ship damage: " << shipDamage << "%" << endl;
    UI::requestAnyKey();
}

void Soldier::interact(Character* enemy) {
    bool correct = false;
    char answer;
    while (!correct) {
        UI::clearScreen();
        UI::printMainBar();
        UI::printEnemyBar();
        cout << "Choose what to do with the target: " << endl;
        cout << "1. Attack" << endl;
        cout << "2. Shoot" << endl;
        answer = getch();
        if (answer != '1' && answer != '2') {
            continue;
        }
        correct = true;
    }

    switch (answer) {
        case '1': this->attack(enemy); break;
        case '2': this->shoot(enemy); break;
    }
}

void Soldier::addHp(int hp) {
    this->hp += hp;
    if (this->hp > 100) this->hp = 100;
}

void Soldier::subtractHp(int hp) {
    this->hp -= hp;
    if (this->hp < 0) this->hp = 0;
}

