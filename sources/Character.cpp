#include "Character.hpp"
#include "Point.hpp"
#include <iostream>
#include <cmath>

using namespace std;

Character :: Character (){
}

Character::Character(string name, Point& location, int hit):name(name), location(location), hit(hit){
}

Character::Character(string name, Point& location):name(name), location(location){
}

string Character::getName(){
    return this -> name;
}

Point Character::getLocation(){
    return this -> location;
}

int Character::getHits()const{
    return this -> hit;
}

void Character::setLocation(Point location){
    this -> location = location;
}

bool Character::isAlive(){
    return hit > 0;
}

double Character::distance(Character* other)const{
    return this->location.distance(other->getLocation());
}

void Character::hits(int num){
    if (num < 0 ){
        throw std::invalid_argument ("Hits must be positive");
    }
    hit = hit-num;
}

string Character::print() {
    stringstream ss;
    ss << "Name: " << name;
    if (hit <= 0) {
        ss << " (Dead)";
    } else {
        ss << ", Hit Points: " << hit;
    }
    ss << ", Location: " << location.print();
    return ss.str();
}



bool Character::TeamMember(){
    return Tmember; 
}

void Character::setTeamMember(){
    Tmember = true;
}

void Character :: setType(string type){
    this ->type = type;
}

string Character :: getType(){
    return this-> type;
}

/*bool Character::TeamLeader(){
    return Tleader; 
}

void Character::setTeamLeader(){
    Tleader = true;
}*/