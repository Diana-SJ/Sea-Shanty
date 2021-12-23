//
// Created by SkyDJul on 21.12.2021.
//

#include "../headers/Game.h"
#include "../headers/UI/UI.h"
#include "../headers/characters/Soldier.h"
#include "../headers/characters/Doctor.h"
#include "../headers/characters/Engineer.h"
#include "../headers/AI/Battle.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <dirent.h>
#include <direct.h>

using namespace std;

// определения методов класса Game
//тип_результата Класс::метод(аргументы) { тело метода }

int const Game::STAGES_COUNT = 3;

Game::Game() {
    this->kopecks = 1000;
    //this->shipHp = 100;
    this->stage = 1;
    UI::setGame(this);
}

void Game::run() {
    bool answerCorrect = false;
    char answer;
    while(true) {
        while (!answerCorrect) {
            UI::clearScreen();
            UI::printMainMenu();
            answer = UI::requestKey();
            if (answer == '1' || answer == '2' || answer == '3' || answer == 'x') {
                answerCorrect = true;
            } else {
                UI::clearScreen();
                cout << "Wrong action!";
                UI::requestAnyKey();
            }
        }

        switch (answer) {
            case '1':
                UI::clearScreen();
                UI::tellStory();
                this->startGame();
                break;
            case '2':
                UI::clearScreen();
                load();
                break;
            case '3':
                exit(0);
                break;
            case 'x':
                exit(0);
        }
    }
    //UI::requestAnyKey();
}



vector<string> Game::getSaved() {
    vector<string> saveFiles;
    TCHAR* savePath = getSavePath();
    DIR *dir = opendir(savePath);
    if (dir == NULL) {
        _mkdir(savePath);
        dir = opendir(savePath);
        //return;
    }
    struct dirent *entry;

    while ((entry = readdir(dir)) != nullptr) {
        if (entry->d_namlen > 2) {
            saveFiles.push_back(entry->d_name);
        }
    }
    closedir(dir);
    return saveFiles;
}

TCHAR* Game::getSavePath() {
//    TCHAR NPath[MAX_PATH];
//    GetCurrentDirectory(MAX_PATH, NPath);
    //string path = NPath;
    string path = "C:\\theGame\\meta";
    TCHAR* meta_path = 0;
    meta_path = new TCHAR[path.size() + 1];
    copy(path.begin(), path.end(), meta_path);
    meta_path[path.size()] = 0;
    return meta_path;
}

void Game::load() {
    vector<string> savedFiles = getSaved();
    TCHAR *savePath = getSavePath();
    bool correct = false;
    int saveNumber;
    while (!correct){
        UI::clearScreen();

        cout << " -------------------------------[SAVES]---------------------------------" << endl;
        cout << "| Directory: " << savePath << endl;
        cout << "| Existing saves:" << endl;
        savedFiles = getSaved();
        int i = 1;
        for (auto &file : savedFiles) {
            cout << "|\t" << i << ". " << file << endl;
            i++;
        }
        cout << " | \"0\" - back" << endl;
        cout << " -----------------------------------------------------------------------" << endl;

        cout << "Input the number of save: ";
        cin >> saveNumber;

        if (saveNumber > savedFiles.size() || saveNumber < 0) {
            cout << "[Error]: No such save" << endl;
            UI::requestAnyKey();
            continue;
        }

        correct = true;
    }
    if (saveNumber == 0) return;

    this->startGame(savedFiles.at(saveNumber));
}

void Game::save() {
    TCHAR* savePath = getSavePath();
    vector<string> savedFiles = getSaved();
    string saveFile;

    bool enough = false;
    char answer;
    while (!enough) {
        UI::clearScreen();
        UI::printMainBar(this->ship->getHp(), this->kopecks, this->team);
        cout << " -------------------------------[SAVES]---------------------------------" << endl;
        cout << "| Directory: " << savePath << endl;
        cout << "| Existing saves:" << endl;
        savedFiles = getSaved();
        int i = 1;
        for(auto & file : savedFiles) {
            cout << "|\t" << i << ". " << file << endl;
            i++;
        }
        cout << " -----------------------------------------------------------------------" << endl;
        cout << "1. Save" << endl;
        cout << "2. Exit" << endl;

        answer = getch();
        if (answer != '1' && answer != '2') {
            cout << endl << "[Error]: Wrong answer" << endl;
            UI::requestAnyKey();
            continue;
        }

        switch (answer) {
            case '1':
                this->buildSaveFile();
                cout << "[Success]: Saved!";
                UI::requestAnyKey();

                break;
            case '2':
                enough = true;
                break;
            default: break;
        }
    }
}

void Game::buildSaveFile() {
    vector<string> savedFiles = getSaved();
    int saveNumber = 0;
    bool correct = false;
    bool exists = false;
    while (!correct) {
        exists = false;
        for (auto &file : savedFiles) {
            if (file == "theGame" + to_string(saveNumber) + ".tgm") {
                exists = true;
            }
        }
        if(exists) saveNumber++;
        if(!exists) correct = true;
    }
    string newSaveFileName = "theGame" + to_string(saveNumber) + ".tgm";
    std::fstream file;
    file.open("C:\\theGame\\meta\\" + newSaveFileName, fstream::out);
    if (!file) {
        fstream file("C:\\theGame\\meta\\" + newSaveFileName, fstream::out);
        file.close();
        file.open("C:\\theGame\\meta\\" + newSaveFileName, fstream::out);
        UI::requestAnyKey();
        return;
    }
//    file << "Hello";
//    file.open("C:\\theGame\\" + newSaveFileName);

    file << this->stage << "\n";
    file << this->ship->hp<< "\n";
    file << this->kopecks << "\n";
    file << this->team.size() << "\n";
    for(auto & unit : this->team) {
        switch (unit->getGameClass()) {
            case Character::doctor: file << "doctor"<< " "; break;
            case Character::engineer: file << "engineer"<< " "; break;
            case Character::soldier: file << "soldier"<< " "; break;
        }
        file << unit->getName() << " ";
        file << unit->getHp() << " ";
        file << "\n";
    }

    file.close();
}

void Game::startGame(string saveFilePath) {

    ifstream file;
    file.open("C:\\theGame\\meta\\" + saveFilePath);
    if (!file.is_open() || file.fail()) {
        cout << "[Error]: Unable to load save" << endl;
        UI::requestAnyKey();
        return;
    }
    int teamSize;
    string unitType;

    file >> this->stage;
    this->ship = new Ship();
    file >> this->ship->hp;

    file >> this->kopecks;
    file >> teamSize;
    Character* character;
    int i;
    for(i = 0; i < teamSize; i++) {
        file >> unitType;
        if (unitType == "doctor") {
            character = new Doctor(this->ship);
        } else if (unitType == "engineer") {
            character = new Engineer(this->ship);
        } else {
            character = new Soldier(this->ship);
        }
        this->team.push_back(character);
        file >> character->name;
        file >> character->hp;
    }

    file.close();

    this->runStory(true);
}

void Game::startGame() {
    this->ship = new Ship();
    this->startTeamHiring();
    this->runStory();
}



void Game::startTeamHiring() {
    UI::printMainBar(this->ship->getHp(), this->kopecks, this->team);
    //UI::requestAnyKey();

    char answer;
    //bool correct = false;
    bool enough = false;
    do {
        UI::clearScreen();
        UI::printMainBar(this->ship->getHp(), this->kopecks, this->team);
        cout << " --------------------------------[DOCK]---------------------------------" << endl;
        cout << "| Here you can buy crew members and save the game" << endl;
        cout << " -----------------------------------------------------------------------" << endl;
        cout << endl << "Hire people for your team: " << endl;
        cout << "1. Soldier\t[" << Soldier::PRICE << "]" << endl;
        cout << "2. Doctor\t[" << Doctor::PRICE << "]" << endl;
        cout << "3. Engineer\t[" << Engineer::PRICE << "]" << endl;
        cout << "4. Save" << endl;
        cout << "5. Leave dock" << endl;

        answer = getch();
        switch (answer) {
            case '1':
                if (this->kopecks < Soldier::PRICE) {
                    cout << endl << "Not enough money!";
                    UI::requestAnyKey();
                    continue;
                }
                this->kopecks -= Soldier::PRICE;
                this->team.push_back(new Soldier(this->ship));
                UI::clearScreen();
                UI::printMainBar(this->ship->getHp(), this->kopecks, this->team);
                cout << endl << "[Sucess]: Bought!" << endl;
                UI::requestAnyKey();
                break;
            case '2':
                if (this->kopecks < Doctor::PRICE) {
                    cout << endl << "Not enough money!";
                    UI::requestAnyKey();
                    continue;
                }
                this->kopecks -= Doctor::PRICE;
                this->team.push_back(new Doctor(this->ship));
                UI::clearScreen();
                UI::printMainBar(this->ship->getHp(), this->kopecks, this->team);
                cout << endl << "[Sucess]: Bought!" << endl;
                UI::requestAnyKey();
                break;
            case '3':
                if (this->kopecks < Engineer::PRICE) {
                    cout << endl << "Not enough money!";
                    UI::requestAnyKey();
                    continue;
                }
                this->kopecks -= Engineer::PRICE;
                this->team.push_back(new Engineer(this->ship));
                UI::clearScreen();
                UI::printMainBar(this->ship->getHp(), this->kopecks, this->team);
                cout << endl << "[Sucess]: Bought!" << endl;
                UI::requestAnyKey();
                break;
            case '4':
                this->save(); break;
            case '5':
                enough = true;
                break;
        }

    } while (!enough);
}

void Game::dock() {
    this->startTeamHiring();
}
void Game::runStory() {
    this->runStory(false);
}
void Game::runStory(bool isLoaded) {
    Battle* battle;
    bool win = true;
    do {

        if (isLoaded ||     this->stage > 1
                        &&  this->stage <= Game::STAGES_COUNT
                        &&  UI::approvedDock()) {
            this->dock();
        }
        UI::clearScreen();
        UI::printMainBar();
        battle = new Battle(this->team, this->ship, this->stage);
        UI::printPreambula(this->stage);
        battle->start();

        if (battle->isWon()) {
            UI::clearScreen();
            UI::printMainBar();
            cout << "You won this battle!" << endl;
            UI::requestAnyKey();
        } else {
            UI::clearScreen();
            cout << "[Loosing]: Game over!" << endl;
            if (this->ship->getHp() <= 0) {
                cout << "[Loosing]: Your ship has broken" << endl;
            }
            UI::requestAnyKey();
            win = false;
            break;
        }

        this->stage++;
    } while (this->stage <= Game::STAGES_COUNT);

    if (win) {
        cout << "[Victory]: You win the game! RESPECT+" << endl;
        cout << "[Victory]: Congratulations!";
        UI::requestAnyKey();
    }

}

