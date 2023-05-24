#ifndef NINJA_HPP
#define NINJA_HPP

#include "Character.hpp"
#include <iostream>

using namespace std;
namespace ariel{};

class Ninja : public Character {
private:
    int speed;

public:
    Ninja(string name, Point location, int hit, int speed);
    int getSpeed() const;
    void move(Character* target);
    void slash(Character* target);
};
#endif 