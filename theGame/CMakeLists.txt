cmake_minimum_required(VERSION 3.17)
project(theGame)

set(CMAKE_CXX_STANDARD 14)

add_executable(theGame main.cpp cpp/UI/UI.cpp headers/UI/UI.h cpp/abstract/Character.cpp headers/abstract/Character.h cpp/characters/Engineer.cpp headers/characters/Engineer.h cpp/characters/Doctor.cpp headers/characters/Doctor.h cpp/characters/Soldier.cpp headers/characters/Soldier.h cpp/models/Ship.cpp headers/models/Ship.h cpp/AI/Battle.cpp cpp/Game.cpp headers/Game.h headers/AI/Battle.h cpp/abstract/IAttackable.cpp headers/abstract/IAttackable.h cpp/AI/Pirate.cpp headers/AI/Pirate.h cpp/abstract/IHealable.cpp headers/abstract/IHealable.h)