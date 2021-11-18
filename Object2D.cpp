#include "Object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateCircle(const std::string& name,glm::vec3 center, float radius, glm::vec3 color, bool fill)
{
    std::vector<VertexFormat> vertices;
    int nr = 300;
    float pas = (radius * 4) / nr;
    float x = -radius, y = 0;
    vertices.push_back(VertexFormat(center, color));
    for (int i = 0; i < nr / 2; i++)
        vertices.push_back(VertexFormat(center + glm::vec3((x += pas), sqrt(radius * radius - x * x), 0), color));
    for (int i = 0; i < nr / 2; i++)
        vertices.push_back(VertexFormat(center + glm::vec3((x -= pas), -sqrt(radius * radius - x * x), 0), color));

    Mesh* circle = new Mesh(name);
    std::vector<unsigned int> indices;

    for (int i = 1; i < nr; i++) {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }
    indices.push_back(0);
    indices.push_back(nr-1);
    indices.push_back(1);

    if (!fill) {
        //circle->SetDrawMode(GL_LINE_LOOP);
        circle->SetDrawMode(GL_TRIANGLES);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        //indices.push_back(0);
        //indices.push_back(2);
    }
    circle->InitFromData(vertices, indices);
    return circle;
}

Mesh* object2D::CreateTriangle(const std::string& name, glm::vec3 center, float length, glm::vec3 color, bool fill)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(-length / 2, -length / 2, 0), color),
        VertexFormat(center + glm::vec3(-length / 2, length / 2, 0), color),
        VertexFormat(center + glm::vec3(length/2, 0, 0), color)
    };

    Mesh* triangle = new Mesh(name);
    std::vector<unsigned int> indices = {0, 1, 2};
    if (!fill) {
        triangle->SetDrawMode(GL_LINE_LOOP);
    }
    triangle->InitFromData(vertices, indices);
    return triangle;
}