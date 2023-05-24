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
    string name;
    Point location;
    int hit;
    bool Tmember=false;
    bool Tleader=false;
    //int priority_enemy = 0;

public:
    //Character();
    Character(const string& name, const Point& location, int hit);
    Character(const string& name, const Point& location);
    virtual ~Character() = default;
    std::string getName();
    const Point& getLocation() const;
    int getHits() const;
    void setLocation(Point location);
    void setHits(int num);
    bool isAlive() const;
    double distance(Character* other);
    void hits(int num);
    //virtual string print() = 0;
    string print();
    

    bool TeamMember();
    void setTeamMember();
    bool TeamLeader();
    void setTeamLeader();



    Character (Character&); // Copy Constructor.
    Character(Character&& ) noexcept; // Move Constructor.
    Character& operator = (const Character&); // Copy assignment operator.
    Character& operator = (Character&&) noexcept; // Move assignment operator.


};
#endif 