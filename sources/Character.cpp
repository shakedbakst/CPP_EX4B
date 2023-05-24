#include "Character.hpp"
#include <iostream>
#include <cmath>

using namespace std;

Character :: Character (){
}

Character::Character(string name, Point& location, int hitPoints):name(name), location(location), hitPoints(hitPoints), Tmember(false){
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
    return this -> hitPoints;
}

void Character::setLocation(Point location){
    this -> location = location;
}

bool Character::isAlive(){
    return hitPoints > 0;
}

double Character::distance(Character* other)const{
    return this->location.distance(other->getLocation());
}

void Character::hit(int num){
    if (num < 0 ){
        throw std::invalid_argument ("Hits must be positive");
    }
    hitPoints = hitPoints-num;
}

string Character::print() {
    stringstream ss;
    ss << "Name: " << name;
    if (hitPoints <= 0) {
        ss << " (Dead)";
    } else {
        ss << ", Hit Points: " << hitPoints;
    }
    ss << ", Location: " << location.print();
    return ss.str();
}



bool Character::TeamMember(){ //istaken
    return Tmember; 
}

void Character::setTeamMember(){ //inteam
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