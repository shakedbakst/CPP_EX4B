#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Point.hpp"
#include <iostream>
//#include <cmath>
//#include <string>

using namespace std;
namespace ariel{};

class Character {
private:
    std::string name;
    Point location;
    int hit;

public:
    Character();
    Character(std::string name, Point location, int hit);
    Character(std::string name, Point location);
    std::string getName();
    Point getLocation();
    int getHits() const;
    void setLocation(Point& location);
    void setHits(int num);
    bool isAlive();
    double distance(Character& other);
    void hits(int num);
    std::string print();
};
#endif 