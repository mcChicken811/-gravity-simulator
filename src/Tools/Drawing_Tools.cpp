#define _USE_MATH_DEFINES

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Header Files/Universe_constants.h>

#include <Objects/Vector.cpp>
#include <Objects/Color.cpp>
#include <cmath>

#pragma once

inline void drawTriangle(Vec2 vec0, Vec2 vec1, Vec2 vec2)
{

    glBegin(GL_TRIANGLES);

    glVertex2f(vec0.x, vec0.y);
    glVertex2f(vec1.x, vec1.y);
    glVertex2f(vec2.x, vec2.y);

    glEnd();
}

inline void drawCircle(Vec2 origin, float radius, Color color, int polygon_count)
{

    glBegin(GL_POLYGON);
    glColor3f(color.r, color.g, color.b);

    for (int i = 0; i < polygon_count; i++)
    {
        glVertex2f(origin.x + radius * sin(2 * PI * i / float(polygon_count)), origin.y + radius * cos(2 * PI * i / float(polygon_count)));
    }

    glEnd();

}

static inline void drawTriangle2022(Vec2 vec0, Vec2 vec1, Vec2 vec2)
{

    float positions[6] = {
        vec0.x, vec0.y,
        vec1.x, vec1.y,
        vec2.x, vec2.y
    };

    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}