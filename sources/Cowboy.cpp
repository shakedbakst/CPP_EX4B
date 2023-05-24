#include "Cowboy.hpp"
#include <iostream>

Cowboy::Cowboy(string name, Point location) : Character(name, location, 110), bullets(6){
}

int Cowboy::getBullets(){
    return this->bullets;
}

void Cowboy::shoot(Character* target) {
    if (this == target) {
        throw std::runtime_error("Invalid target");
    }
    if (!isAlive()) {
        throw std::runtime_error("ERROR- the cowboy is dead");
    }
    if (!hasboolets()) {
        return;
    }
    if (!target->isAlive()) {
        throw std::runtime_error("ERROR- dead characters");
    }

    target->hit(10);
    this->bullets-=1;
}

bool Cowboy::hasboolets(){
    return bullets > 0;
}

void Cowboy::reload(){
    if(this->isAlive()){
        this->bullets = 6;
    }else{
        throw std::runtime_error("The cowboy is dead");
    }
}