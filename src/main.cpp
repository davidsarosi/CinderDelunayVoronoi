#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

#include "Point.h"
#include "Line.h"
#include "Triangle.h"
#include "DelunayTriangulator.h"

#define  WINDOW_SIZE_X 1500
#define  WINDOW_SIZE_Y 1000
#define  NUMBER_OF_TRIANGLES 2000

void updateTriangles(DelunayTriangulator& triangulator, sf::VertexArray& triangles)
{
    triangles.clear();
    for (const auto &triangle: triangulator.triangles)
    {
        for (int i=0;i<3;i++)
        {
            auto vertexBegin = sf::Vertex{sf::Vector2f{triangle->points[i%3]->x, triangle->points[i%3]->y}};
            auto vertexEnd = sf::Vertex{sf::Vector2f{triangle->points[(i+1)%3]->x, triangle->points[(i+1)%3]->y}};
            vertexBegin.color=sf::Color::Green;
            vertexEnd.color=sf::Color::Green;
            triangles.append(vertexBegin);
            triangles.append(vertexEnd);
        }
    }
}

int main()
{

    DelunayTriangulator triangulator{};
    triangulator.superTriangleInit(WINDOW_SIZE_X, WINDOW_SIZE_Y);

    sf::VertexArray points{sf::Points, 0};
    for (int i = 0; i < NUMBER_OF_TRIANGLES; i++)
    {
        float x=rand() % (WINDOW_SIZE_X-100)+50;
        float y=rand() % (WINDOW_SIZE_Y-100)+50;
        triangulator.addPoint(new Point{x, y});
        auto vertex = sf::Vertex{sf::Vector2f{x, y}};
        vertex.color=sf::Color::Green;
        points.append(vertex);
    }

    sf::VertexArray triangles{sf::Lines, 0};

    triangulator.triangulate();
    updateTriangles(triangulator,triangles);


    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y), "ImGui + SFML = <3");
    window.setFramerateLimit(60);
    if (!ImGui::SFML::Init(window))
        return 0;

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);


    sf::Clock deltaClock;
    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        //ImGui::ShowDemoWindow();

//        ImGui::Begin("Hello, world!");
//        ImGui::Button("Look at this pretty button");
//        ImGui::End();

        triangulator.triangulate();
        updateTriangles(triangulator,triangles);

        window.clear();
        window.draw(triangles);
//        window.draw(shape);
        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();
}