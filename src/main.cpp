#include <iostream>

#include "Point.h"
#include "Line.h"
#include "Triangle.h"
#include "DelaunayTriangulator.h"


#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

#define  WINDOW_SIZE_X 1500
#define  WINDOW_SIZE_Y 1000
#define  NUMBER_OF_POINTS 1000


class CinderDelaunayVoronoi: public App
{
    gl::VboMeshRef PointsMesh;
    gl::VboMeshRef TrianglesMesh;
    int vertexCountInTriangleMesh{};
    DelaunayTriangulator triangulator{};


    void updateTriangles()
    {
        std::vector<ci::vec2> vertexes{};
//    std::vector<ci::ColorA> colors{triangulator.triangles.size() * 3, ColorA(0, 1, 0, 1)};
        for (const auto &triangle: triangulator.triangles)
        {
                for (int i = 0; i < 3; i++)
                {
                    vertexes.emplace_back(triangle->points[i]->x, triangle->points[i]->y);
                    vertexes.emplace_back(triangle->points[(i+1)%3]->x, triangle->points[(i+1)%3]->y);
                }
        }
        vertexCountInTriangleMesh=vertexes.size();

        if (vertexCountInTriangleMesh==0){
            return;
        }
        TrianglesMesh->bufferAttrib(geom::POSITION, vertexes);

//    triangles->bufferAttrib(geom::COLOR,colors);
    }


public:
    void setup() override {
        std::vector<vec2> positions;
        std::vector<ColorA> colors;

        for (int i = 0; i < NUMBER_OF_POINTS; ++i) {
            float x = rand() % (WINDOW_SIZE_X - 100) + 50;
            float y = rand() % (WINDOW_SIZE_Y - 100) + 50;
            triangulator.addPoint(new Point{x, y});
            positions.emplace_back(x, y);
        }
        triangulator.superTriangleInit(WINDOW_SIZE_X,WINDOW_SIZE_Y);
        gl::VboMesh::Layout layout1;
        layout1.attrib(geom::POSITION, 2);
        gl::VboMesh::Layout layout2;
        layout2.attrib(geom::POSITION, 2);

        PointsMesh = gl::VboMesh::create(positions.size(), GL_POINTS, { layout1 });
        PointsMesh->bufferAttrib(geom::POSITION, positions);

        TrianglesMesh = gl::VboMesh::create(NUMBER_OF_POINTS*2*6, GL_LINES, { layout2 });

    }

    void update() override {
        triangulator.triangulate();
        updateTriangles();

    }

    void draw() override {
        gl::clear(Color(0, 0, 0));
        ci::gl::color(0, 1, 0);
        gl::draw(PointsMesh);
        if (vertexCountInTriangleMesh==0){
            return;
        }
        ci::gl::color(0, 1, 0);
        gl::draw(TrianglesMesh,0,vertexCountInTriangleMesh);
    }
};



CINDER_APP(CinderDelaunayVoronoi, RendererGl)