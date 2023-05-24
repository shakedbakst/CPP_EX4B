#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "Point.hpp"
#include <iostream>
#include <string>
#include <sstream>


using namespace std;
namespace ariel{};

class Character {
private:
    string name;
    Point location;
    int hit;
    bool Tmember;
    string type;
    //bool Tleader=false;

public:
    Character ();
    Character(string name, Point& location, int hit);
    Character(string name, Point& location);
    virtual ~Character() = default;
    string getName();
    Point getLocation();
    int getHits() const;
    void setLocation(Point location);
    bool isAlive();
    double distance(Character* other)const;
    void hits(int num);
    string print();
    

    bool TeamMember();
    void setTeamMember();

    void setType(string type);
    string getType();


    //bool TeamLeader();
    //void setTeamLeader();



    Character (Character&); // Copy Constructor.
    Character(Character&& ) noexcept; // Move Constructor.
    Character& operator = (const Character&); // Copy assignment operator.
    Character& operator = (Character&&) noexcept; // Move assignment operator.

};
#endif 