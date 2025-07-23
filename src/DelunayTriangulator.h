//
// Created by sarosi on 2023.07.29..
//

#pragma once


#include <vector>
#include "Triangle.h"
#include <unordered_set>

class Point;

class DelunayTriangulator {

    std::vector<Point*> points;
    Point* newlyInsertedPoint{};
    Triangle superTriangle;
    std::vector<Triangle *> badTriangles;
    std::unordered_set<Line *, PtrLineHash, PtrLineComparator> polygonalHoleBadLines;
    std::unordered_set<Line *, PtrLineHash, PtrLineComparator> polygonalHoleBoundary;
    bool insertNewPoint();
    void findBadTriangles();
    void createPolygonalHole();
    void eraseBadTriangles();
    void fillPolygonalHole();
    void trimSuperTriangle();
public:

    std::vector<Triangle*> triangles;
    DelunayTriangulator()=default;
    ~DelunayTriangulator();
    void addPoint(Point*);
    void addPoint(float,float);
    void addPoint(int,int);
    bool triangulate();
    void superTriangleInit(int,int);



};
