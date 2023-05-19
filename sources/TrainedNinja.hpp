using namespace std;

#include "Ninja.hpp"

namespace ariel {
    class TrainedNinja : public Ninja{
        public:
            TrainedNinja(string name, Point location)
             : Ninja(name, location, 120, 12) {}
    };
}