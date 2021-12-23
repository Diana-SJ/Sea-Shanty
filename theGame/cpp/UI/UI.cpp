//
// Created by SkyDJul on 21.12.2021.
//

#include "../../headers/UI/UI.h"
#include "../../headers/abstract/Character.h"
#include "../../headers/characters/Soldier.h"
#include "../../headers/characters/Engineer.h"
#include "../../headers/characters/Doctor.h"
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <iomanip>
using namespace std;

Game* UI::game;
vector<Character*> UI::enemyTeam;
void UI::setGame(Game * game1) {

    game = game1;
}

void UI::setEnemyTeam(vector<Character *> & enemyTeam1) {
    enemyTeam = enemyTeam1;
}

void UI::printMainMenu() {
    cout << "\t\t\t=================[Traveler Diaries]=================" << endl;
    cout << "\t\t\t| 1. Start a new game                              |" << endl;
    cout << "\t\t\t| 2. Load game                                     |" << endl;
    cout << "\t\t\t| 3. Exit                                          |" << endl;
    cout << "\t\t\t====================================================" << endl;

}

void UI::waitForEnemy() {
    float seconds = 3.0;
    int trigger = 1;
    UI:clearScreen();

    while (seconds > 0) {
        UI::clearScreen();
        UI::printMainBar();
        UI::printEnemyBar();

        cout << "\t\t=====>" << std::fixed << std::setprecision(2) << seconds << "<=====" << endl;
        cout << "\t[Wait] Waiting for enemy turn";
        for(int i = 0; i < trigger; i++) cout << ".";
        trigger = (trigger + 1) % 10;
        cout << endl;
        this_thread::sleep_for(chrono::milliseconds(100) );
        //usleep(10000);
        seconds -= 0.1;
    }

}

char UI::requestKey() {
    return getch(); // просто получает нажатую клавишу
}

void UI::clearScreen() {
    system("CLS");
}

void UI::requestAnyKey() {
    cout << endl << "Press any key to continue..." << endl;
    getch();
}

void UI::tellStory() {
    setlocale(LC_ALL, "");
    cout << " -------------------------------[STORY]---------------------------------" << endl;
    cout << "| XVII century" << endl;
    cout << "| You are gathering a team on a long journey to Bali." << endl;
    cout << "| The route goes through the Indian Ocean, where pirates " << endl;
    cout << "| have been robbing passing ships for the past 100 years.." << endl;
    cout << " -----------------------------------------------------------------------" << endl;
    cout << "| All you have saved up over the last 10 years is 1000 kopecks." << endl;
    cout << "| It's time to choose who to hire for your team." << endl;
    cout << " -----------------------------------------------------------------------" << endl;
    cout << endl;
    requestAnyKey();
    clearScreen();

    cout << " --------------------------------[HELP]---------------------------------" << endl;
    cout << "| Soldiers will help protect the ship when pirates attack." << endl;
    cout << "| Their cost is " << Soldier::PRICE << " kopecks for each." << endl;
    cout << " -----------------------------------------------------------------------" << endl;
    cout << "| Engineers can repair the ship during the battle. " << endl;
    cout << "| You can hire one for " << Engineer::PRICE << " kopecks." << endl;
    cout << " -----------------------------------------------------------------------" << endl;
    cout << "| Doctors know how to heal right during a battle." << endl;
    cout << "| Everyone costs " << Doctor::PRICE << " kopecks (but only for you sweetheart)." << endl;
    cout << " -----------------------------------------------------------------------" << endl;
    cout << endl;
    requestAnyKey();
    clearScreen();

}

void UI::printPreambula(int x) {
    switch (x) {
        case 1:
            UI::clearScreen();
            UI::printMainBar();
            cout << " -------------------------------[STORY]---------------------------------" << endl;
            cout << "| You happily set off from the shore." << endl;
            cout << "| After three days of travel, a ship with a pirate flag " << endl;
            cout << "| could be seen in the distance... " << endl;
            cout << " -----------------------------------------------------------------------" << endl;

            UI::requestAnyKey();
            break;
        case 2:
            UI::clearScreen();
            UI::printMainBar();
            cout << " -------------------------------[STORY]---------------------------------" << endl;
            cout << "| Only after finishing the battle, and not a day passed, a huge black " << endl;
            cout << "| ship appeared on the horizon. And, leveling with your ship, took it " << endl;
            cout << "| on board. " << endl;
            cout << "| Two pirates with sabers in their hands looked menacingly at the crew." << endl;
            cout << " -----------------------------------------------------------------------" << endl;
            UI::requestKey();
            UI::clearScreen();
            UI::printMainBar();
            cout << " -------------------------------[STORY]---------------------------------" << endl;
            cout << "\"Dump all your stuff in my hold, you moron." << endl;
            cout << "Just try to shove your paws into the holster, try your luck, weirdo, \"" << endl;
            cout << "he said, bringing the end of the saber straight to the captain's throat." << endl;
            cout << "" << endl;
            cout << "The situation was heated to the limit." << endl;
            cout << " -----------------------------------------------------------------------" << endl;
            UI::requestAnyKey();
            UI::clearScreen();
            UI::printMainBar();
            cout << "Prepare for the battle!";
            UI::requestAnyKey();
            break;
        case 3:
            UI::clearScreen();
            UI::printMainBar();
            cout << " -------------------------------[STORY]---------------------------------" << endl;
            cout << "The last month of the trip went quite calmly." << endl;
            cout << "Not a single soul was in the middle of the endless Indian Ocean. Only " << endl;
            cout << "one thing darkened the mood - the shore of Bali was approaching." << endl;
            cout << " -----------------------------------------------------------------------" << endl;
            UI::requestKey();
            UI::clearScreen();
            UI::printMainBar();
            cout << " -------------------------------[STORY]---------------------------------" << endl;
            cout << "The closer you are to the shore, the more likely you are to meet" << endl;
            cout << "someone not very pleasant." << endl;
            cout << "As it happened." << endl;
            cout << "A ship with three bandits on deck, dressed as Jack Sparrow, was approaching." << endl;
            cout << "Nobody had time to blink an eye when they had already jumped on long ropes" << endl;
            cout << "onto our ship and rushed into the hold." << endl;
            cout << "The rest of the team ran after them, preparing for the fight." << endl;
            cout << " -----------------------------------------------------------------------" << endl;
            UI::requestKey();
            UI::clearScreen();
            UI::printMainBar();
            cout << "Prepare for the battle!";
            UI::requestAnyKey();
            break;

        default: break;
    }
}

bool UI::approvedDock() {
    UI::clearScreen();
    UI::printMainBar();

    bool correct = false;
    char answer;
    while (!correct) {
        UI::clearScreen();
        UI::printMainBar();
        cout << " -------------------------------[STORY]---------------------------------" << endl;
        cout << "The port is visible a couple of miles away." << endl;
        cout << "In the port, you can buy crew members and save the game." << endl;
        cout << "Do we need to dock?" << endl;
        cout << " -----------------------------------------------------------------------" << endl;
        cout << "1. Yea" << endl;
        cout << "2. Nope" << endl;
        answer = getch();
        if (answer != '1' && answer != '2') {
            continue;
        }
        correct = true;
    }

    switch (answer) {
        case '1': return true; break;
        case '2': return false; break;
    }
    return false;
}

void UI::printMainBar() {
    printMainBar(game->ship->getHp(), game->kopecks, game->team);
}

void UI::printEnemyBar() {
    printEnemyBar(enemyTeam);
}

void UI::printEnemyBar(vector<Character*> &team) {
    cout << " -----------------------------------------------------------------------" << endl;
    cout << "| Enemy Team:\t\t\t\t" << endl;
    int i = 0;
    for(auto & unit : team) {
        if (i % 2 == 0) {
            cout << "|\t";
        }
        cout << unit->getName() << " [";
        switch (unit->getGameClass()) {
            case Character::soldier: cout << "Soldier"; break;
            case Character::engineer: cout << "Engineer"; break;
            case Character::doctor: cout << "Doctor"; break;
            case Character::pirate: cout << "Pirate"; break;
        }
        cout << "] HP: " << unit->getHp() << "%";
        if (i % 2 == 0) {
            cout << "\t||\t";
        } else { cout << endl; }
        i++;
    }
    cout << endl;
    cout << " ----------------------------------------------------------------------- " << endl;

}

void UI::printMainBar(int shipHP, int kopecks, vector<Character*> &team) {
    cout << " -----------------------------------------------------------------------" << endl;
    cout << "|" << "Ship HP: " << shipHP << "%\t" << "Kopecks: " << kopecks << "\t" << endl;
    cout << "|-----------------------------------------------------------------------" << endl;
    cout << "| Team:\t\t\t\t" << endl;
    int i = 0;
    for(auto & unit : team) {
        if (i % 2 == 0) {
            cout << "|\t";
        }
        cout << unit->getName() << " [";
        switch (unit->getGameClass()) {
            case Character::soldier: cout << "Soldier"; break;
            case Character::engineer: cout << "Engineer"; break;
            case Character::doctor: cout << "Doctor"; break;
        }
        cout << "] HP: " << unit->getHp() << "%";
        if (i % 2 == 0) {
            cout << "\t||\t";
        } else { cout << endl; }
        i++;
    }
    cout << endl;
    cout << " ----------------------------------------------------------------------- " << endl;

}

//string UI::requestName() {
//    string name;
//    cout << "Input name of the Hero: ";
//    cin >> name;
//    return name;
//}
