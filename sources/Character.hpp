#pragma once

#include <iostream>
#include <sstream>

using namespace std;

#include "Point.hpp"

namespace ariel {
    class Character {
        private:
            Point location;
            int hitPoints;
            string name;

        public:
            // Character() : location(Point(0,0)), hitPoints(0), name("Bob") {}
            Character(string name, Point location, int hitpoints)
             : location(location), hitPoints(hitpoints), name(move(name)) {}
             
            virtual ~Character() {}

            // copy constructor
            Character(const Character& someone) : hitPoints(someone.getHP()){
                Point someonesLocation = someone.getLocation();
                this->location = Point(someonesLocation.getX(), someonesLocation.getY());
                this->name = someone.getName();
            }

            // assignment operator
            Character& operator=(const Character& other) {return *this;}

            // move assignment operator
            Character& operator=(Character&& other) noexcept {return *this;}

            // move constructor
            Character(Character&& someone) noexcept : hitPoints(someone.getHP()) {}


            bool isAlive() const { return (this->hitPoints > 0);}
            double distance(Character* enemy) { return this->location.distance(enemy->getLocation());}
            void hit(int damage) { this->hitPoints -= damage;}
            string getName() const { return this->name;}
            Point getLocation() const { return this->location;}
            void setLocation(Point newLocation) {this->location = newLocation;}
            int getHP() const { return this->hitPoints;}
            string print() { 
                stringstream sstream;
                sstream << this->name << ", " << this->hitPoints << ", " << this->location;
                return sstream.str();
            }
            
    };
}