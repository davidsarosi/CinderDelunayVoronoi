//
// Created by sarosi on 2023.07.29
//

#pragma once
#include <compare>

class Point {
public:
    float x;
    float y;

    Point();
    Point(float,float);
    Point(int,int);

    [[nodiscard]] float distance(const Point* other) const;
    [[nodiscard]] float distance(const Point& other) const;

    auto operator<=>(const Point&) const = default;
    Point operator-(const Point&) const;
    Point operator+(const Point&) const;



};
