#include <iostream>
#include <vector>

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
            Character* leader;

        public:
            Team(Character* leada) : leader(leada) {}
            ~Team() {}

            void add(Character* toAdd) { allies.push_back(toAdd);}
            int stillAlive() { return allies.size();}

            void attack(Team* other) {
                vector<Character*> enemies = other->getAllies();
                Character* enemyLeader = other->getLeader();

                // Check if leader is dead and change to closest ally if true
                if( ! (enemyLeader->isAlive())) {
                    int minIndex = findClosestCharacter(enemies, enemyLeader);
                    other->setLeader(enemies[minIndex]);
                    enemies.erase(enemies.begin() + minIndex);
                }

                // Find enemy thats closest to own leader
                int victimIndex = findClosestCharacter(enemies, this->leader);
                Character* victim = enemies[victimIndex];

                // Cowboys attack
                for(int i=0;i<allies.size();i++) {
                    Cowboy* temp = dynamic_cast<Cowboy*>(allies[i]);
                    if(temp != nullptr) {
                        if(temp->hasBullets()) {
                            temp->shoot(victim);
                        }
                        else {
                            temp->reload();
                        }
                    }
                }

                // Ninjas attack
                for(int i=0;i<allies.size();i++) {
                    Ninja* temp = dynamic_cast<Ninja*>(allies[i]);
                    if(temp != nullptr) {
                        if(temp->distance(victim) <= 1) {
                            temp->slash(victim);
                        }
                        else {
                            temp->move(victim);
                        }
                    }
                }



            }

            void print() {
                for(int i=0;i<allies.size();i++)
                    cout << allies[i]->print() << " ";
                cout << endl;
            }

            Character* getLeader() { return this->leader;}
            void setLeader(Character* newone) { this->leader = newone;}
            vector<Character*> getAllies() { return this->allies;}

            static int findClosestCharacter(vector<Character*> team, Character* someone) {
                int minDistance = 9999;
                int minIndex = 0;
                for(int i=0;i<team.size();i++) {
                    if(team[i]->distance(someone) < minDistance) {
                        minDistance = team[i]->distance(someone);
                        minIndex = i;
                    }
                }
                return minIndex;
            }

    };
}