#pragma once

#include <iostream>
#include <sstream>

#include "Character.hpp"

const int cowboy_hp = 110;
const int mag_size = 6;
const int cowboy_damage = 10;

namespace ariel {
    class Cowboy : public Character{
        private:
            int bullets;

        public:
            Cowboy(string name, Point location)
             : Character(std::move(name), location, cowboy_hp), bullets(mag_size) {}

            bool hasboolets() const { return (this->bullets > 0);}

            void reload() { 
                if(this->isAlive()) {
                    throw runtime_error("dead cowboy can not reload");
                }
                this->bullets = mag_size;
            }

            void shoot(Character* enemy) {
                if(this == enemy) {
                    throw runtime_error("no self harm");
                }
                if(!this->isAlive() || !enemy->isAlive()) {
                    throw runtime_error("dead");
                }
                if(this->hasboolets()) {
                    enemy->hit(cowboy_damage);
                    this->bullets -= 1;
                }
            }
    };
}