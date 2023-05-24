#ifndef TRAINEDNINJA_HPP
#define TRAINEDNINJA_HPP

#include "Ninja.hpp"
#include <iostream>

using namespace std;
namespace ariel{};

class TrainedNinja : public Ninja {
public:
    TrainedNinja(string name, Point location);
};
#endif  