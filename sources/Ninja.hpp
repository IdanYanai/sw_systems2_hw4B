#pragma once

#include "Character.hpp"

const int ninja_damage = 40;

namespace ariel {
    class Ninja : public Character{
        private:
            int const speed;

        public:
            Ninja(string name, Point location, int hitpoints, int const speed) 
            : Character(std::move(name), location, hitpoints), speed(speed) {} 

            void move(Character* enemy) { this->setLocation(Point::moveTowards(this->getLocation(), enemy->getLocation(), this->getSpeed()));}
            void slash(Character* enemy) {
                if(this == enemy) {
                    throw runtime_error("no self harm");
                }
                if(!this->isAlive() || !enemy->isAlive()) {
                    throw runtime_error("dead");
                }
                if(this->distance(enemy) <= 1) {
                    enemy->hit(ninja_damage);
                }
            }

            int getSpeed() const {return this->speed;}
    };
}