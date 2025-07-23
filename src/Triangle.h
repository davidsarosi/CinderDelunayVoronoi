//
// Created by sarosi on 2023.07.29..
//

#pragma once


#include <vector>
#include <array>
#include "Line.h"
#include "Point.h"

class Point;

class Triangle {
    void calculateCircumcircle();


public:
    std::array<Point*,3> points{};
    std::array<Line,3> lines{};
    Point circumcircleCenter;
    float circumcircleRadius{};

    Triangle()=default;
    Triangle(Point*,Point*,Point*);
    Triangle(Line*,Point*);
    [[nodiscard]] bool containsPoint(const Point*) const;
    [[nodiscard]] bool containsPoint(const Point&) const;
    [[nodiscard]] bool containsLine(const Line&) const;
    [[nodiscard]] bool isCircumcircleContainsPoint(const Point&) const;
    [[nodiscard]] bool isCircumcircleContainsPoint(const Point*) const;
    auto operator<=>(const Triangle&) const = default;



};




