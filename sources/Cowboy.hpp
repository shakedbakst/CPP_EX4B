#ifndef COWBOY_HPP
#define COWBOY_HPP

#include "Character.hpp"
#include <iostream>

using namespace std;
namespace ariel{};

class Cowboy : public Character {
private:
    int bullets;

public:
    Cowboy(string name, Point location);
    int getBullets();
    void shoot(Character* target);
    bool hasboolets();
    void reload();
};

#endif 