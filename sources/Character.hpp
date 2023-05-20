#pragma once

#include <iostream>
#include <sstream>

using namespace std;

#include "Point.hpp"

namespace ariel {
    class Character {
        protected:
            Point location;
            int hitPoints;
            string name;

        public:
            Character() : location(Point(0,0)), hitPoints(10), name("Bob") {}
            Character(string name, Point location, int hitpoints)
             : location(location), hitPoints(hitpoints), name(move(name)) {}
            virtual ~Character() {}

            bool isAlive() const { return (this->hitPoints > 0);}
            int distance(Character* enemy) { return this->location.distance(enemy->getLocation());}
            void hit(int damage) { this->hitPoints -= damage;}
            string getName() const { return this->name;}
            Point getLocation() const { return this->location;}
            string print() { 
                stringstream ss;
                ss << this->name << ", " << this->hitPoints << ", " << this->location;
                return ss.str();
            }
            
    };
}