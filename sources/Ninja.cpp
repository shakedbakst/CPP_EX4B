#include "Ninja.hpp"
#include <iostream>

Ninja::Ninja(string name, Point location, int hit, int speed): Character(name, location, hit){
    this -> speed  = speed;
}

int Ninja::getSpeed()const{
    return this -> speed;
}

void Ninja::move(Character* target) {
    if (target == nullptr) {
        throw std::invalid_argument("Invalid target");
    }
    if (!isAlive()) {
        throw std::runtime_error("Dead ninjas can't move");
    }
    
    double distance = getLocation().distance(target->getLocation());
    double moveDistance = speed;

    if (distance <= moveDistance) {
        setLocation(target->getLocation());
    }
    else {
        double ratio = moveDistance / distance;
        double newX = getLocation().getX() + (target->getLocation().getX() - getLocation().getX()) * ratio;
        double newY = getLocation().getY() + (target->getLocation().getY() - getLocation().getY()) * ratio;
        setLocation(Point(newX, newY));
    }
}

void Ninja::slash(Character* target) {
    if (target == nullptr) {
        throw std::invalid_argument("Invalid target");
    }
    if (!isAlive()) {
        throw std::runtime_error("Dead ninjas can't slash");
    }

    double distance = getLocation().distance(target->getLocation());

    if (distance <= 1.0) {
        if (target->isAlive()) {
            target->hits(40);
        }
        else {
            throw std::runtime_error("Can't attack dead characters");
        }
    }
    else {
        throw std::runtime_error("Target is not within slashing range");
    }
}

