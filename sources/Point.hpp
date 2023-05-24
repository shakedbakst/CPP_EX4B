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
    static Point moveTowards(Point src, Point dest, double dist);
    string print();
};
#endif  