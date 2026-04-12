#pragma once

#include <glm/glm.hpp>

class Vertex
{
public:
    float position_index, u, v;
    float nx, ny, nz;
    
    Vertex(size_t _position_index)
        : position_index(_position_index) { u =0; v = 0; nx =0; ny =0; nz =0;}

    Vertex(size_t _position_index, float u_, float v_)
        : position_index(_position_index), u(u_), v(v_) { nx =0; ny =0; nz =0;}

    Vertex(size_t _position_index, float u_, float v_, float nx_, float ny_, float nz_)
        : position_index(_position_index), u(u_), v(v_), nx(nx_), ny(ny_), nz(nz_) {}
	
};
