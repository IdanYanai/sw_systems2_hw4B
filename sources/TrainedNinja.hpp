#pragma once

#include "Ninja.hpp"

const int trained_hp = 120;
const int trained_speed = 12;

namespace ariel {
    class TrainedNinja : public Ninja{
        public:
            TrainedNinja(string name, Point location)
             : Ninja(std::move(name), location, trained_hp, trained_speed) {}
    };
}