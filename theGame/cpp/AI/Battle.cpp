//
// Created by SkyDJul on 22.12.2021.
//

#include <conio.h>
#include "../../headers/AI/Battle.h"
#include "../../headers/UI/UI.h"
#include <ctime>
#include <algorithm>

Battle::Battle(vector<Character*> &allies, Ship* ship, int enemiesCount) {
    this->won = false;
    this->allies = allies;
    this->ship = ship;
    int i;
    for(i = 0; i < enemiesCount; i++) {
        this->enemies.push_back(new Pirate(ship));
    }
}

void Battle::start() {
    UI::setEnemyTeam(this->enemies);

    while (!this->enemies.empty() && !this->allies.empty() && ship->getHp() > 0 ) {
        this->alliesTurn();
        if (ship->getHp() <= 0) break;
        if (enemies.empty()) break;

        this->enemiesTurn();
    }

    if (enemies.empty()) {
        this->won = true;
    }
}

bool Battle::isWon() {
    return this->won;
}

void Battle::alliesTurn() {
    UI::clearScreen();
    UI::printMainBar();

    auto actor = this->pickActor();
    auto target = this->pickTarget();
    actor->interact(target);

    this->enemies.erase(
            std::remove_if(
                    this->enemies.begin(),
                    this->enemies.end(),
                    [](Character* ch) { return ch->getHp() <= 0; } //lambda
            ),
            this->enemies.end()
    );

    this->allies.erase(
            std::remove_if(
                    this->allies.begin(),
                    this->allies.end(),
                    [](Character* ch) { return ch->getHp() <= 0; } //lambda
            ),
            this->allies.end()
    );

//    int i = 0, pos = -1;
//    for(auto & unit : this->enemies) {
//        if (unit->getHp() <= 0) {
//            pos = i;
//            break;
//        }
//        i++;
//    }
//
//    if (pos >= 0) {
//        this->enemies.erase(enemies.begin() + pos);
//    }
//
//    i = 0, pos = -1;
//    for(auto & unit : this->allies) {
//        if (unit->getHp() <= 0) {
//            pos = i;
//            break;
//        }
//        i++;
//    }
//
//    if (pos >= 0) {
//        this->allies.erase(allies.begin() + pos);
//    }
}

void Battle::enemiesTurn() {

    UI::waitForEnemy();

    srand(time(nullptr));
    int ally = rand() % this->allies.size();
    int enemy = rand() % this->enemies.size();

    this->enemies.at(enemy)->attack(this->allies.at(ally));

    this->enemies.erase(
            std::remove_if(
                    this->enemies.begin(),
                    this->enemies.end(),
                    [](Character* ch) { return ch->getHp() <= 0; } //lambda
                    ),
            this->enemies.end()
            );

    this->allies.erase(
            std::remove_if(
                    this->allies.begin(),
                    this->allies.end(),
                    [](Character* ch) { return ch->getHp() <= 0; } //lambda
            ),
            this->allies.end()
    );

//    , pos = -1;
//    for(auto & unit : this->allies) {
//        if (unit->getHp() <= 0) {
//            pos = i;
//            break;
//        }
//        i++;
//    }
//
//    if (pos >= 0) {
//        this->allies.erase(allies.begin() + pos);
//    }
//
//    i = 0, pos = -1;
//    for(auto & unit : this->enemies) {
//        if (unit->getHp() <= 0) {
//            pos = i;
//            break;
//        }
//        i++;
//    }
//
//    if (pos >= 0) {
//        this->enemies.erase(enemies.begin() + pos);
//    }
}

Character * Battle::pickActor() {
    bool correct = false;
    char answer;
    int choice;

    while (!correct) {
        UI::clearScreen();
        UI::printMainBar();
        UI::printEnemyBar();
        cout << "Choose your unit:" << endl;
        int i = 1;
        for (auto &unit : this->allies) {
            //cout << ( i <= 9 ? (int)i : (char)('a' + (i - 10) )) << ". ";
            if (i <= 9) {
                cout << i << ". ";
            } else { cout << (char)('a' + (i - 10) ) << ". "; }
            cout << unit->getName() << " [";
            switch (unit->getGameClass()) {
                case Character::soldier:
                    cout << "Soldier";
                    break;
                case Character::engineer:
                    cout << "Engineer";
                    break;
                case Character::doctor:
                    cout << "Doctor";
                    break;
                default:
                    break;
            }
            cout << "] HP: " << unit->getHp() << "%" << endl;
            i++;
        }
//        answer = getch();
//        choice = (int) answer - (int)'0';
//        if (this->allies.size() < choice) {
//            cout << "[Error] Wrong unit" << endl;
//            UI::requestAnyKey();
//            continue;
//        }
//        correct = true;

        answer = getch();
        if (answer < '1' || answer > '9') {
            choice = (int) (abs(answer - 'a') + 10);
        } else { choice = (int) answer - (int)'0'; }
        //choice = (int) answer - (int)'0';
        if (this->allies.size() < choice) {
            cout << "[Error] Wrong unit" << endl;
            UI::requestAnyKey();
            continue;
        }
        correct = true;
    }

    return this->allies.at(choice - 1);
}

Character * Battle::pickTarget() {
    bool correct = false;
    char answer;
    int choice;

    while (!correct) {
        UI::clearScreen();
        UI::printMainBar();
        UI::printEnemyBar();
        cout << "Choose target:" << endl;
        int i = 1;
        for (auto &unit : this->enemies) {
            if (i <= 9) {
                cout << i << ". ";
            } else { cout << (char)('a' + (i - 10) ) << ". "; }
            cout << unit->getName() << " [Pirate] HP: ";
            cout << unit->getHp() << "%" << endl;
            i++;
        }
        for (auto &unit : this->allies) {
            if (i <= 9) {
                cout << i << ". ";
            } else { cout << (char)('a' + (i - 10) ) << ". "; }
            cout << unit->getName() << " [";
            switch (unit->getGameClass()) {
                case Character::soldier:
                    cout << "Soldier";
                    break;
                case Character::engineer:
                    cout << "Engineer";
                    break;
                case Character::doctor:
                    cout << "Doctor";
                    break;
                default:
                    break;
            }
            cout << "] HP: " << unit->getHp() << "%" << endl;
            i++;
        }
        answer = getch();
        if (answer < '1' || answer > '9') {
            choice = (int) (abs(answer - 'a') + 10);
        } else { choice = (int) answer - (int)'0'; }
        //choice = (int) answer - (int)'0';
        if (this->allies.size() + this->enemies.size() < choice) {
            cout << "[Error] Wrong unit" << endl;
            UI::requestAnyKey();
            continue;
        }
        correct = true;
    }

    if (choice <= this->enemies.size() ) {
        return this->enemies.at(choice - 1);
    } else {
        choice = choice - this->enemies.size();
        return this->allies.at(choice - 1);
    }
}