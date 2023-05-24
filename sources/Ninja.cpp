#include "Ninja.hpp"
#include <iostream>

Ninja::Ninja(string name, Point location, int hit, int speed): Character(name, location, hit){
    this -> speed  = speed;
}

int Ninja::getSpeed()const{
    return this -> speed;
}

void Ninja::move(Character* enemy) {
    if (!isAlive()) {
        return;
    }

    Point currentLocation = getLocation();
    Point enemyLocation = enemy->getLocation();
    double distance = currentLocation.distance(enemyLocation);
    double moveDistance = speed;

    if (distance < moveDistance) {
        setLocation(enemyLocation);
    } else {
        double dx = enemyLocation.getX() - currentLocation.getX();
        double dy = enemyLocation.getY() - currentLocation.getY();
        double unitDx = dx / distance;
        double unitDy = dy / distance;
        double newLocationX = currentLocation.getX() + unitDx * moveDistance;
        double newLocationY = currentLocation.getY() + unitDy * moveDistance;
        setLocation(Point(newLocationX, newLocationY));
    }
}



void Ninja::slash(Character* other) {
    if (this == other) {
        throw std::runtime_error("ERROR- cannot slash yourself");
    }
    if (!this->isAlive()) {
        throw std::runtime_error("ERROR- dead ninja");
    }
    if (!other->isAlive()) {
        throw std::runtime_error("ERROR- dead characters");
    }
    double distance = this->getLocation().distance(other->getLocation());
    if (distance <= 1) {
        other->hit(40);
    }
}
