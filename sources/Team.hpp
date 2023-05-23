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

const int maxTeamSize = 10;

namespace ariel {
    class Team {
        private:
            vector<Character*> allies;
            Character* leader;

        public:
            Team(Character* leada) : leader(leada) {this->add(leada);}
            virtual ~Team() {
                for(auto & ally : allies) {
                    delete ally;
                }
            }

            // copy constructor
            Team(const Team& someone) : leader(someone.leader), allies(someone.allies) {}

            // assignment operator
            Team& operator=(const Team& other) {if(&other != this) {} return *this;}

            // move assignment operator
            Team& operator=(Team&& other) noexcept {return *this;}

            // move constructor
            Team(Team&& someone) noexcept : leader(someone.getLeader()) {}

            void add(Character* toAdd) { 
                if(allies.size() == maxTeamSize) {
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
                    throw runtime_error("dead team");
                }

                vector<Character*>& enemies = other->getAllies();

                // Check if leader is dead and change to closest ally if true
                if( ! (this->leader->isAlive())) {
                    Character* newLeader = findClosestCharacter(allies, this->leader);
                    this->death(this->leader);
                    this->setLeader(newLeader);
                }

                // Find enemy thats closest to own leader
                Character* victim = findClosestCharacter(enemies, this->leader);

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
                        victim = findClosestCharacter(enemies, this->leader);
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
                        victim = findClosestCharacter(enemies, this->leader);
                    }
                }
            }

            void print() {
                for(int i=0;i<allies.size();i++) {
                    cout << allies[size_t(i)]->print() << "\n";
                }
                cout << "------" << endl;
            }

            Character* getLeader() { return this->leader;}
            void setLeader(Character* newLeada) { this->leader = newLeada;}
            vector<Character*>& getAllies() { return this->allies;}

            void death(Character* someone) {
                auto iterato = find(allies.begin(), allies.end(), someone);
                if(iterato != allies.end()) {
                    allies.erase(iterato);
                }
            }

            static Character* findClosestCharacter(vector<Character*> team, Character* someone) {
                double minDistance = std::numeric_limits<int>::max();
                Character* minCharacter = nullptr;
                for(int i=0;i<team.size();i++) {
                    if(team[size_t(i)] == someone) {
                        continue;
                    }
                    if(team[size_t(i)]->distance(someone) < minDistance) {
                        minDistance = team[size_t(i)]->distance(someone);
                        minCharacter = team[size_t(i)];
                    }
                }
                return minCharacter;
            }
    };
}