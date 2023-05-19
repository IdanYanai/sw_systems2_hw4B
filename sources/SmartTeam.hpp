#include <iostream>
#include <vector>

using namespace std;

#include "Character.hpp"

namespace ariel {
    class SmartTeam {
        private:
            vector<Character> allies;

        public:
            SmartTeam() {}
            ~SmartTeam() {}

            void add(Character* toAdd) {}
            int stillAlive() {}

            void attack(SmartTeam* other);
            void print();

    };
}