//
// Created by sarosi on 2023.07.29
//

#include "Triangle.h"
#include <algorithm>

Triangle::Triangle(Point *a, Point *b, Point *c) {
    points[0] = a;
    points[1] = b;
    points[2] = c;

    for (int i = 0; i < 3; ++i) {
        lines[i] = Line{points[i], points[(i + 1) % 3]};
    }
    calculateCircumcircle();

}

void Triangle::calculateCircumcircle() {

    Point translatedB = *(points[1]) - *(points[0]);
    Point translatedC = *(points[2]) - *(points[0]);
    float inverseD = 1 / (2 * (translatedB.x * translatedC.y - translatedB.y * translatedC.x));
    float bSumPow2 = translatedB.x * translatedB.x + translatedB.y * translatedB.y;
    float cSumPow2 = translatedC.x * translatedC.x + translatedC.y * translatedC.y;
    float circumcircleCenterX = inverseD * (translatedC.y * bSumPow2 - translatedB.y * cSumPow2);
    float circumcircleCenterY = inverseD * (translatedB.x * cSumPow2 - translatedC.x * bSumPow2);
    circumcircleCenter = Point{circumcircleCenterX, circumcircleCenterY} + *(points[0]);
    circumcircleRadius = circumcircleCenter.distance(*(points[0]));


}

bool Triangle::containsPoint(const Point *otherPoint) const {
    return std::ranges::any_of(points,
                               [&](const auto &point) {
                                   if (point == otherPoint)
                                       return true;
                                   return false;
                               });
}

bool Triangle::containsPoint(const Point &otherPoint) const {
    return std::ranges::any_of(points,
                               [&](auto const &point) {
                                   if (*point == otherPoint)
                                       return true;
                                   return false;
                               });
}

bool Triangle::containsLine(const Line &otherLine) const {
    return std::ranges::any_of(lines,
                               [&](auto const &line) {
                                   if (line == otherLine)
                                       return true;
                                   return false;
                               });
}

bool Triangle::isCircumcircleContainsPoint(const Point &point) const {
    return circumcircleCenter.distance(point) < circumcircleRadius;
}

bool Triangle::isCircumcircleContainsPoint(const Point *point) const {
    return circumcircleCenter.distance(point) < circumcircleRadius;
}

Triangle::Triangle(Line *line, Point *point): Triangle(line->begin,line->end,point) {

}
