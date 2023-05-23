#pragma once

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

#include "Team.hpp"
#include "Character.hpp"
#include "YoungNinja.hpp"
#include "TrainedNinja.hpp"
#include "OldNinja.hpp"
#include "Cowboy.hpp"

namespace ariel {
    class SmartTeam : public Team {
        public:
            SmartTeam(Character* leada) : Team(leada) {}

            void attack(Team* other) override {
                if(other == nullptr) {
                    throw invalid_argument("nullptr");
                }
                if(other->stillAlive() == 0) {
                    throw runtime_error("dead team");
                }

                vector<Character*>& enemies = other->getAllies();
                vector<Character*>& allies = this->getAllies();
                Character* leader = this->getLeader();

                // Check if leader is dead and change to closest ally if true
                if( ! (leader->isAlive())) {
                    Character* newLeader = findClosestCharacter(allies, leader);
                    this->death(leader);
                    this->setLeader(newLeader);
                }

                // Find enemy thats closest to own leader
                Character* victim = findClosestCharacter(enemies, leader);

                // attack
                for(int i=0;i<allies.size();i++) {
                    Cowboy* isCowboy = dynamic_cast<Cowboy*>(allies[size_t(i)]);
                    if(isCowboy != nullptr) {
                        if(isCowboy->hasboolets()) {
                            isCowboy->shoot(victim);
                        }
                        else {
                            isCowboy->reload();
                        }
                    }
                    else {
                        Ninja* isNinja = dynamic_cast<Ninja*>(allies[size_t(i)]);
                        if(isNinja->distance(victim) <= 1) {
                            isNinja->slash(victim);
                        }
                        else {
                            isNinja->move(victim);
                        }
                    }

                    if(!(victim->isAlive())) {
                        other->death(victim);
                        if(other->stillAlive() == 0) {
                            return;
                        }
                        victim = findClosestCharacter(enemies, leader);

                    }
                }
            }
    };
}