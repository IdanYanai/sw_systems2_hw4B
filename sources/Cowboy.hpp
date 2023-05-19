#include <iostream>
#include <sstream>

using namespace std;

#include "Character.hpp"

namespace ariel {
    class Cowboy : public Character{
        private:
            int bullets;

        public:
            Cowboy(string name, Point location)
             : Character(name, location, 110), bullets(6) {}
            ~Cowboy() {}

            bool hasBullets() { return (this->bullets > 0);}
            void reload() { this->bullets = 6;}
            void shoot(Character* enemy) { enemy->hit(10);}
    };
}