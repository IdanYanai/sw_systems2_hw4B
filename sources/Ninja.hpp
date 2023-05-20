#pragma once

using namespace std;

#include "Character.hpp"

namespace ariel {
    class Ninja : public Character{
        protected:
            int speed;

        public:
            Ninja(string name, Point location, int hitpoints, int speed) 
            : Character(name, location, hitpoints), speed(speed) {} 

            void move(Character* enemy) { this->location = Point::moveTowards(this->location, enemy->getLocation(), this->getSpeed());}
            void slash(Character* enemy) {
                if(this->distance(enemy) <= 1) {
                    enemy->hit(40);
                }
            }

            int getSpeed() {return this->speed;}
    };
}