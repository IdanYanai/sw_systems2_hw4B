using namespace std;

#include "Ninja.hpp"

namespace ariel {
    class YoungNinja : public Ninja{
        public:
            YoungNinja(string name, Point location)
             : Ninja(name, location, 100, 14) {}
    };
}