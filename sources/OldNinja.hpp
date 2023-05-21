#pragma once

#include "Ninja.hpp"

const int old_hp = 150;
const int old_speed = 8;

namespace ariel {
    class OldNinja : public Ninja{
        public:
            OldNinja(string name, Point location)
             : Ninja(std::move(name), location, old_hp, old_speed) {}
    };
}