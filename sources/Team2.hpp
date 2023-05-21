#pragma once

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

#include "Character.hpp"
#include "YoungNinja.hpp"
#include "TrainedNinja.hpp"
#include "OldNinja.hpp"
#include "Cowboy.hpp"

namespace ariel {
    class Team2 : public Team{
        public:
            Team2(Character* leada) : Team(leada) {}

            void attack(Team* other) {
                vector<Character*>& enemies = other->getAllies();
                Character* enemyLeader = other->getLeader();
                vector<Character*> allies = this->getAllies();

                // Check if leader is dead and change to closest ally if true
                if( ! (enemyLeader->isAlive())) {
                    int minIndex = findClosestCharacter(enemies, enemyLeader);
                    other->setLeader(minIndex);
                    enemies.erase(enemies.begin() + minIndex);
                }

                // Find enemy thats closest to own leader
                int victimIndex = findClosestCharacter(enemies, allies[size_t(0)]);
                Character* victim = enemies[size_t(victimIndex)];

                // Cowboys attack
                for(int i=0;i<allies.size();i++) {
                    Cowboy* temp = dynamic_cast<Cowboy*>(allies[size_t(i)]);
                    if(temp == nullptr) {
                        continue;
                    }

                    if(temp->hasboolets()) {
                        Cowboy::shoot(victim);
                    }
                    else {
                        temp->reload();
                    }

                    if(!(victim->isAlive())) {
                        cout << victim->print() << " has died" << endl;
                        other->death(victim);
                        victimIndex = findClosestCharacter(enemies, allies[size_t(0)]);
                        victim = enemies[size_t(victimIndex)];
                    }
                }

                // Ninjas attack
                for(int i=0;i<allies.size();i++) {
                    Ninja* temp = dynamic_cast<Ninja*>(allies[size_t(i)]);
                    if(temp == nullptr) {
                        continue;
                    }

                    if(temp->distance(victim) <= 1) {
                        temp->slash(victim);
                    }
                    else {
                        temp->move(victim);
                    }

                    if(!(victim->isAlive())) {
                        cout << victim->print() << " has died" << endl;
                        other->death(victim);
                        victimIndex = findClosestCharacter(enemies, allies[size_t(0)]);
                        victim = enemies[size_t(victimIndex)];
                    }
                }
            }
    };
}