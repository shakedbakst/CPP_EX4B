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
    Cowboy(std::string name, Point location);
    int getBullets();
    void shoot(Character* target);
    bool hasBullets();
    void reload();
};

#endif 