#include "Point.hpp"
#include <iostream>
#include <cmath>

using namespace std;

Point::Point(){}

Point::Point(double pt_x, double pt_y){
    this -> pt_x = pt_x;
    this -> pt_y= pt_y;
}

double Point::getX()const{
    return this -> pt_x;
}

double Point::getY()const{
    return this -> pt_y;
}

double Point::distance(const Point &pt_other) const {
    return std::hypot(pt_other.getX() - getX(), pt_other.getY() - getY());
}


Point Point::moveTowards(const Point src, const Point dest, double dist){
    if(dist < 0){
        throw std::invalid_argument("Error! distance must be positive!");
    }
    double X_new = dest.getX() - src.getX();
    double Y_new = dest.getY() - src.getY();
    double distance = src.distance(dest);

    if (distance <= dist) {
        return dest;
    }

    double temp = dist / distance;
    double X_newest = src.getX() + X_new * temp;
    double Y_newest = src.getY() + Y_new * temp;

    return Point(X_newest, Y_newest);
}


string Point :: print(){
    string s = "(" + to_string(this ->pt_x) + " , " + to_string(this ->pt_y) + " )";
    return s;    
}
