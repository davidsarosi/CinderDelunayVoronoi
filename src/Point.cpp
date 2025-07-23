//
// Created by sarosi on 2023.07.29
//

#include "Point.h"

#include <cmath>



Point::Point():x{0}, y{0} {}
Point::Point(float x, float y): x{x}, y{y} {}
Point::Point(int x, int y): x{static_cast<float>(x)}, y{static_cast<float>(y)} {}

float Point::distance(const Point &other) const {
    return sqrtf(powf((this->x-other.x),2)+ powf((this->y-other.y),2));
}

float Point::distance(const Point *other) const {

    return distance(*other);
}

Point Point::operator-(const Point &other) const {

    return Point {this->x-other.x, this->y-other.y};
}

Point Point::operator+(const Point &other) const {
    return Point {this->x+other.x, this->y+other.y};
}






//auto Point::operator-=(const Point &other) const {
//
//    return Point {this->x-other.x, this->y-other.y};
//}
