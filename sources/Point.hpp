#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>

using namespace std;
namespace ariel{};

class Point {
private:
    double pt_x;
    double pt_y;

public:
    Point();
    Point(double pt_x, double pt_y);
    double getX() const;
    double getY() const;
    double distance(const Point &pt_other) const;
    Point moveTowards(const Point src, const Point dest, double dist);
    std::string print() const;
};
#endif  