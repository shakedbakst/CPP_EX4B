#ifndef OLDNINJA_HPP
#define OLDNINJA_HPP

#include "Ninja.hpp"
#include <iostream>

using namespace std;
namespace ariel{};

class OldNinja : public Ninja {
public:
    OldNinja(string name, Point location);
};
#endif