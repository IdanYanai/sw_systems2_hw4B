using namespace std;

#include "Ninja.hpp"

namespace ariel {
    class OldNinja : public Ninja{
        public:
            OldNinja(string name, Point location)
             : Ninja(name, location, 150, 8) {}
    };
}