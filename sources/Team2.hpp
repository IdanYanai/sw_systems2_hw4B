#include <iostream>
#include <vector>

using namespace std;

#include "Character.hpp"

namespace ariel {
    class Team2 {
        private:
            vector<Character> allies;

        public:
            Team2() {}
            ~Team2() {}

            void add(Character* toAdd) {}
            int stillAlive() {}

            void attack(Team2* other);
            void print();

    };
}