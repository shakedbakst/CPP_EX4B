#include "Character.hpp"
#include <iostream>
#include <cmath>

using namespace std;


Character::Character(){}

Character::Character(string name, Point location, int hit):name(name), location(location), hit(hit){
}

Character::Character(string name, Point location):name(name), location(location){
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

void Character::setLocation(Point &location){
    this -> location = location;
}

bool Character::isAlive(){
    return hit > 0;
}

double Character::distance(Character& other){
    return this->location.distance(other.getLocation());
}

void Character::hits(int num){
    if (num < 0 ){
        throw std::invalid_argument ("Hits must be positive");
    }
    hit = hit-num;
}

string Character::print() {
    string description = "Name: ";
    description += this->name;

    if (hitp <= 0) {
        description += " (" + this->name + ")";
    } else {
        description += ", Hit point: " + to_string(hitp);
    }

    description += ", Location: " + this->location.print();
    description += ", Lives left: " + to_string(this->alivePoints);

    return description;
}


//functionsss