#include "Cowboy.hpp"
#include <iostream>

Cowboy::Cowboy(string name, Point location) : Character(name, location, 110), bullets(6){
}

int Cowboy::getBullets(){
    return this->bullets;
}

void Cowboy::shoot(Character* target) {
    if (target == nullptr) {
        throw std::invalid_argument("Invalid target");
    }
    if (!isAlive()) {
        throw std::runtime_error("Dead cowboys can't shoot");
    }
    if (!hasBullets()) {
        return;
    }
    if (target == this) {
        throw std::runtime_error("You can't shoot yourself");
    }
    if (!target->isAlive()) {
        throw std::runtime_error("Can't attack dead characters");
    }

    target->hit(10);
    decreaseBullets();
}

bool Cowboy::hasBullets(){
    return bullets > 0;
}

void Cowboy::reload(){
        if(this->isAlive()){
        this->bullets = 6;
        }else{
            throw std::runtime_error("The cowboy is dead");
        }
    }