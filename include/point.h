#pragma once

#include <glm/glm.hpp>

class Point
{
public:
    float x, y, z, u, v;
    float nx, ny, nz;
    Point(float x_, float y_, float z_)
        : x(x_), y(y_), z(z_) { u =0; v = 0; nx =0; ny =0; nz =0;}

    Point(float x_, float y_, float z_, float u_, float v_)
        : x(x_), y(y_), z(z_), u(u_), v(v_) { nx =x_; ny =y_; nz =z_;}

    Point(float x_, float y_, float z_, float u_, float v_, float nx_, float ny_, float nz_)
        : x(x_), y(y_), z(z_), u(u_), v(v_), nx(nx_), ny(ny_), nz(nz_) {}
	
};
