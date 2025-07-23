//
// Created by sarosi on 2023.07.29
//

#include <algorithm>
#include "DelunayTriangulator.h"


void DelunayTriangulator::addPoint(Point *point)
{
    points.emplace_back(point);
}

void DelunayTriangulator::addPoint(float x, float y)
{
    points.emplace_back(new Point{x, y});
}

void DelunayTriangulator::addPoint(int x, int y)
{
    points.emplace_back(new Point{x, y});
}

bool DelunayTriangulator::triangulate()
{
    if (!insertNewPoint())
        return false;
    findBadTriangles();
    createPolygonalHole();
    eraseBadTriangles();
    fillPolygonalHole();
    return true;

}

void DelunayTriangulator::superTriangleInit(int sizeX, int sizeY)
{

    points.emplace_back(new Point{0, 0});
    points.emplace_back(new Point{sizeX * 2, 0});
    points.emplace_back(new Point{0, sizeY * 2});
    superTriangle = Triangle{points[0], points[1], points[2]};
    triangles.emplace_back(new Triangle{superTriangle});

}

DelunayTriangulator::~DelunayTriangulator()
{
    std::ranges::for_each(points,
                          [](auto const &point)
                          {
                              delete point;
                          });

}


void DelunayTriangulator::findBadTriangles()
{
    badTriangles.clear();
    std::ranges::for_each(
            triangles,
            [&](const auto &triangle)
            {
                if (triangle->isCircumcircleContainsPoint(newlyInsertedPoint))
                {
                    badTriangles.emplace_back(triangle);
                }
            });
}

bool DelunayTriangulator::insertNewPoint()
{
    if (points.empty())
    {
        trimSuperTriangle();
        return false;
    }
    newlyInsertedPoint = points.back();
    points.pop_back();
    return true;
}

void DelunayTriangulator::fillPolygonalHole()
{


    for (auto it = polygonalHoleBoundary.begin(); it != polygonalHoleBoundary.end();)
    {
        if (polygonalHoleBadLines.contains(*it))
        {
            polygonalHoleBoundary.erase(it++);
        } else
        {
            ++it;
        }
    }

    for (const auto &line: polygonalHoleBoundary)
    {
        triangles.emplace_back(new Triangle{line, newlyInsertedPoint});
    }
//    std::ranges::for_each(polygonalHoleBoundary, [&](auto const line)
//    {
//        triangles.emplace_back(Triangle(line, newlyInsertedPoint));
//    });


}


void DelunayTriangulator::createPolygonalHole()
{

    polygonalHoleBoundary.clear();
    polygonalHoleBadLines.clear();

    for (auto &badTriangle: badTriangles)
    {
        for (auto &line: badTriangle->lines)
        {
            auto res = polygonalHoleBoundary.insert(&line);
            if (!res.second)
            {
                polygonalHoleBadLines.insert(*res.first);
            }
        }
    }

}

void DelunayTriangulator::eraseBadTriangles()
{

    std::erase_if(triangles, [&](auto &triangle)
    {

        return std::ranges::any_of(badTriangles, [&](auto &badTriangle) -> bool
        {
            auto res = badTriangle == triangle;
            return res;
        });
    });
}

void DelunayTriangulator::trimSuperTriangle()
{

    for (const auto triangle: triangles)
    {
        for (const auto &superTrianglePoint: superTriangle.points)
        {
            if (triangle->containsPoint(superTrianglePoint))
            {
                badTriangles.emplace_back(triangle);
                break;
            }
        }
    }
    eraseBadTriangles();

}



