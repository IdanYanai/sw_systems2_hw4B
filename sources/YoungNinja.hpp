#pragma once

#include "Ninja.hpp"

const int young_hp = 100;
const int young_speed = 14;

namespace ariel {
    class YoungNinja : public Ninja{
        public:
            YoungNinja(string name, Point location)
             : Ninja(std::move(name), location, young_hp, young_speed) {}
    };
}