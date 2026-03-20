#pragma once

#include <glm/glm.hpp>

class Point
{
public:
    float x, y, z, u, v;
    Point(float x_, float y_, float z_)
        : x(x_), y(y_), z(z_) { u =0; v = 0;}

    Point(float x_, float y_, float z_, float u_, float v_)
        : x(x_), y(y_), z(z_), u(u_), v(v_) {}
	
};
