//
// Created by sarosi on 2023.07.29
//

#include "Line.h"
#include "Point.h"
#include <unordered_set>

Line::Line(const Point *begin, const Point *end)
{
    if (*begin > *end)
    {
        this->begin = const_cast<Point *>(end);
        this->end = const_cast<Point *>(begin);
    } else
    {
        this->begin = const_cast<Point *>(begin);
        this->end = const_cast<Point *>(end);
    }
}

//float Line::length() const
//{
//    return this->begin->distance(this->end);
//}

size_t PtrLineHash::operator()(const Line *line) const
{
    size_t res = 17;
    res = res * 31 + std::hash<Point *>()(line->begin);
    res = res * 31 + std::hash<Point *>()(line->end);
    return res;
}

bool PtrLineComparator::operator()(const Line *lhs, const Line *rhs) const
{
    return (*lhs) == (*rhs);
}
