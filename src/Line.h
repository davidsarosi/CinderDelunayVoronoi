//
// Created by sarosi on 2023.07.29
//

#pragma once

#include <compare>
#include <typeindex>
#include <cstddef>


class Point;

class Line {


public:
    Point* begin;
    Point* end;

    Line()=default;
    Line(const Point*, const Point*);

//    [[nodiscard]]float length() const;
    auto operator<=>(const Line&) const=default;



};

struct PtrLineHash
{
    size_t operator()(const Line* line) const;

};

struct PtrLineComparator
{
    bool operator()(const Line* lhs, const Line* rhs) const;

};