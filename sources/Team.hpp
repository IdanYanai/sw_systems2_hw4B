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
    class Team {
        private:
            vector<Character*> allies;

        public:
            // leader index is always 0
            Team(Character* leada) {this->add(leada);}
            ~Team() {}

            // copy constructor
            Team(const Team& someone) {}

            // assignment operator
            Team& operator=(const Team& other) {return *this;}

            // move assignment operator
            Team& operator=(Team&& other) noexcept {return *this;}

            // move constructor
            Team(Team&& someone) noexcept {}

            void add(Character* toAdd) { 
                if(allies.size() == 10) {
                    throw runtime_error("max team size reached");
                }
                if(toAdd->isInTeam()) {
                    throw runtime_error("Player already in team");
                }
                allies.push_back(toAdd);
                toAdd->addedToTeam();
            }
            int stillAlive() { return int(allies.size());}

            virtual void attack(Team* other) {
                if(other == nullptr) {
                    throw invalid_argument("nullptr");
                }
                if(other->stillAlive() == 0) {
                    return;
                }

                vector<Character*>& enemies = other->getAllies();
                Character* enemyLeader = other->getLeader();

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
                        temp->shoot(victim);
                    }
                    else {
                        temp->reload();
                    }

                    if(!(victim->isAlive())) {
                        other->death(victim);
                        if(other->stillAlive() == 0) {
                            return;
                        }
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
                        other->death(victim);
                        if(other->stillAlive() == 0) {
                            return;
                        }
                        victimIndex = findClosestCharacter(enemies, allies[size_t(0)]);
                        victim = enemies[size_t(victimIndex)];
                    }
                }
            }

            void print() {
                for(int i=0;i<allies.size();i++) {
                    cout << allies[size_t(i)]->print() << "\n";
                }
                cout << "------" << endl;
            }

            Character* getLeader() { return this->allies[size_t(0)];}
            void setLeader(int newLeaderIndex) {
                delete this->allies[size_t(0)];
                this->allies[size_t(0)] = this->allies[size_t(newLeaderIndex)];
                this->allies.erase(allies.begin() + newLeaderIndex);
            }
            vector<Character*>& getAllies() { return this->allies;}

            void death(Character* someone) {
                auto iterato = find(allies.begin(), allies.end(), someone);
                if(iterato != allies.end()) {
                    allies.erase(iterato);
                }
            }

            static int findClosestCharacter(vector<Character*> team, Character* someone) {
                double minDistance = std::numeric_limits<int>::max();
                int minIndex = 0;
                for(int i=0;i<team.size();i++) {
                    if(team[size_t(i)]->distance(someone) < minDistance) {
                        minDistance = team[size_t(i)]->distance(someone);
                        minIndex = i;
                    }
                }
                return minIndex;
            }
    };
}